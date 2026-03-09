#include <stdio.h>
#include <stdlib.h>
#include <ipc.h>
#include <string.h>
#include <cxxdata.h>
#include <memory1.h>
#include <csvr_ipc.h>
#include <date_new.h>
#include "apptrans.h"
#include "bank.c1"
#include "init.h"
#include "errormsg.h"
#include "datatype.h"
#include "validation.h"
#include "macro.h"
#include "comman.h"
#include "const.h"
#include "Exception_Log.h"

static ShortInt count;
static ShortInt cnt = 0;
static ShortInt *err;
static ShortInt fno;
static ShortInt kno;
static ShortInt op;
ShortInt jellist[100];
static char buf[BUFFSIZE] = "\0";
static char key[MXKEYLEN];
char kbf [100];
static void add_res(ShortInt el, ShortInt macro)
{
	err[count++] = el;
	err[count++] = macro;
}


ShortInt set_value(char *ptrbf, char *buffer,ShortInt i, ShortInt size)
{
	if (is_string(eltype [i]) ||
		eltype[i] == 'D') {
		mov_mem((char *)ptrbf + size, buffer + size, ellen[i]);
		return  ellen[i];
	}
	else {
		if (eltype[i] == 'x') {
			*(unsigned int *)(buffer + size) = *(unsigned int*)(ptrbf + size);
			return sizeof (unsigned int);
		}
		else if (eltype[i] == 'U') {
			*(unsigned int *)(buffer + size) = *(unsigned int*)(ptrbf + size);
			return sizeof (unsigned int);
		}
		else if (eltype[i] == 'I') {
			*(int *)(buffer + size) = *(int*)(ptrbf + size);
			return sizeof (int);
		}
		else {
			*(ShortInt*)(buffer + size)= *(ShortInt*)(ptrbf + size);
			return sizeof (ShortInt);
		}
	}
}

static ShortInt get_jdb(struct request_buffer *reqbuff, char *values)
{
	ShortInt size = 0;
	char kbf [100];

	char *ptrbf = reqbuff->buffer;
	op = *(ShortInt *)ptrbf;
	ptrbf += sizeof (ShortInt);
	fno = *(ShortInt *)ptrbf;
	ptrbf += sizeof(ShortInt);
	kno = *(ShortInt *)ptrbf;
	ptrbf += sizeof(ShortInt);
	values = (char *)malloc(databasexx::rlen(fno));

	for(int j = 0; kno != -1 && index_ele [fno] [kno-1] [j] != 0; j++) {
		test_key_buffer(kbf, index_ele [fno] [kno-1] [j], ptrbf);
		mov_mem(kbf, key + size, ellen [index_ele [fno] [kno-1] [j]]);
 		size += ellen [index_ele [fno] [kno-1] [j]];
		ptrbf += ellen [index_ele [fno] [kno-1] [j]];
	}

	if(op == RTN_SCR) {
		cnt = *(ShortInt *)ptrbf;
		ptrbf += sizeof(ShortInt);
		size = 0;
		if(kno == -1 ? org->fseqrcd(fno, buf) == OK :
			org->find_rcd(fno, kno, key, buf) == OK) {
			for(int i = 0 ; i < cnt ; i++) {
				jellist[i] = *(ShortInt *)ptrbf;
				ptrbf += sizeof(ShortInt);
				ShortInt size1 = set_value(ptrbf, values + size, jellist[i], 0);
				ptrbf += size1;
				set_value((values + size), (buf + epos_file(jellist[i], fno)), jellist[i], 0);
				size += size1;
				if ((org->relate_rcd(fno, buf)) == ERROR) {
					add_res(jellist[i], NT_RLT);
					return ERROR;
				}
			}
			return OK;
		}
		else
			add_res(ERROR, NT_FND);	
			return ERROR;
	}
	return OK;
}

static ShortInt validate_jdb(struct request_buffer *reqbuff, char *values)
{
	return OK;
}

static ShortInt update_jdb(struct request_buffer *reqbuff, char *values)
{
	char oldbuf[BUFFSIZE] = "\0", actno [15];
	if(kno != -1 ? org->find_rcd(fno, kno, key, oldbuf) == OK :
		 org->fseqrcd(fno, oldbuf) == OK)
	{
			init_mem(actno, ellen [ACTNO], ' ');
			add_Exclog_record(org, fno, (char*)&cursys_ldate, EXC_JDB,
				 reqbuff->reqhd.branch_id, reqbuff->reqhd.user_id,
 				 reqbuff->reqhd.user_id, actno, oldbuf, buf);
			org->rtn_rcd(fno, buf);
			err[count++] = CLG_MDFY;
			return OK;
	}
// 	org->rtn_rcd(fno, buf);
	//err[count++] = CLG_MDFY;
	return OK;
}

static ShortInt del_jdb(struct request_buffer *reqbuff, char *values)
{
	if(kno == -1 ? org->fseqrcd(fno, buf) == OK :
		org->find_rcd(fno, kno, key, buf) == OK) {
		if (org->unrelate_rcd(fno, buf, NULL, 0) == OK) {
			org->del_rcd(fno);
			err[count++] = TDS_YEAR_DEL;
			return OK;
		}
		else
			add_res(ERROR, CATA_NDEL);
	}
	else
		add_res(ERROR, NT_FND);
		return ERROR;
}

void jdb_req_handler(struct request_buffer *reqbuff)
{
	char *value = NULL; 
	struct result_buffer resbuf;
	ShortInt ret; 
	count = 0;
	init_mem(buf, BUFFSIZE - 1, ' ');
	assign_result_header2(&resbuf.reshd, &reqbuff->reqhd);
	err = (ShortInt*) (resbuf.buffer + 2 * sizeof (ShortInt));

	ret = get_jdb(reqbuff, value);
	if(ret == OK)
		ret = validate_jdb(reqbuff, value);
	if(ret == OK) {
		switch(op) {
			case RTN_SCR :
				ret = update_jdb(reqbuff, value);
				break;
			case DEL_SCR :
				ret = del_jdb(reqbuff, key);
				break;
		}
	}
	*(ShortInt *) resbuf.buffer = ret;
	*(ShortInt *) (resbuf.buffer + sizeof (ShortInt)) = count;
	if (ret != OK)
		resbuf.reshd.result_size = 2 * count * sizeof (ShortInt) + 2 * sizeof (ShortInt);
	else {
			ShortInt ksize = 0;
			int key_no = kno - 1;
			char *key = reqbuff->buffer + 3* sizeof(ShortInt);
			resbuf.reshd.result_size = count * sizeof (ShortInt) + 2 * sizeof (ShortInt);
			ShortInt *size_ptr = (ShortInt*)(resbuf.buffer + resbuf.reshd.result_size);
			*size_ptr = 0 ;
			resbuf.reshd.result_size += sizeof (ShortInt);
			if(kno != -1) {
				for(int i = 0; index_ele[fno][key_no][i] != 0; i++) {
					ShortInt ele = index_ele[fno][key_no][i];
					*(ShortInt*) (resbuf.buffer + resbuf.reshd.result_size) = ele;
					resbuf.reshd.result_size += sizeof (ShortInt);
					ShortInt size1 = set_value(key + ksize, resbuf.buffer + resbuf.reshd.result_size, ele, 0);
					ksize += size1;
					resbuf.reshd.result_size += size1;
					(*size_ptr)++;
				}
			}
	}
		result_write(&resbuf, FALSE);
}