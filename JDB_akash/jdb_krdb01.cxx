#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysdef.h>
#include <cxxdata.h>
#include <cal_ndec.h>
#include <date_new.h>
#include <datatype.h>
#include <memory1.h>
#include "bank.c1"
#include "apptrans.h"
#include <krdb.h>
#include "errormsg.h"
#include "krdb_tran.h"
#include "jcrawler.h"

ShortInt jdb_parse(char *query, char *buf)
{
	ShortInt ret = 0, tbl_no = -1, size = 0, *count;
	JCrawler *db = new JCrawler();

	init_mem(buf, BUFFSIZE - 1, ' ');
	db->set_query(query);
	if((ret = db->isvalid_dml()) != OK) {
		*(ShortInt *)buf = ret;
		size = sizeof(ShortInt);
		return size;
	}
	if((ret = db->parse()) != OK) {
		*(ShortInt *)buf = db->get_table();
		size = sizeof(ShortInt);
		return size;
	}
	switch(db->get_dml_index()) {

		case JCMD_DESC:
			db->execute();
			*(ShortInt *)buf = OK;
			size = sizeof(ShortInt);
			tbl_no = db->get_table();
			*(ShortInt *)(buf + size) = strlen(dbfiles[tbl_no]);
			size += sizeof(ShortInt);
			mov_mem(dbfiles[tbl_no], buf + size, strlen(dbfiles[tbl_no]));
			size += strlen(dbfiles[tbl_no]);
			count = (ShortInt *)(buf + size);
			size += sizeof(ShortInt);
			*count = 0;
			for(int j = 0; file_ele [tbl_no] [j] != 0; j++) {
				*(ShortInt *)(buf + size) = strlen(denames[file_ele[tbl_no][j]]);
				size += sizeof(ShortInt);
				mov_mem(denames[file_ele[tbl_no][j]], buf + size, strlen(denames[file_ele[tbl_no][j]]));
				size += strlen(denames[file_ele[tbl_no][j]]);
				*(buf + size) = eltype [file_ele [tbl_no] [j]];
				size += 1;
				*(ShortInt *)(buf + size) = ellen [file_ele [tbl_no] [j]];
				size += sizeof(ShortInt);
				*(ShortInt *)(buf + size) = strlen(elmask[file_ele[tbl_no][j]]);
				size += sizeof(ShortInt);
				mov_mem(elmask[file_ele[tbl_no][j]], buf + size, strlen(elmask[file_ele[tbl_no][j]]));
				size += strlen(elmask[file_ele[tbl_no][j]]);
				*(ShortInt *)(buf + size) = strlen(eldisp[file_ele[tbl_no][j]]);
				size += sizeof(ShortInt);
				mov_mem(eldisp[file_ele[tbl_no][j]], buf + size, strlen(eldisp[file_ele[tbl_no][j]]));
				size += strlen(eldisp[file_ele[tbl_no][j]]);
				(*count)++;
			}
			break;

		case JCMD_SELECT:
				db->execute();
			break;

		case JCMD_UPDATE:
			break;

		case JCMD_DELETE:
			break;
	}
	return size;
}

void fnd_jdb(databasexx *db, struct krdb_client_bf *cltbf)
{
	ShortInt ret = ERROR;
	char buff [BUFFSIZE], buffer [BUFFSIZE1 * 2];
	char *ptr = cltbf->buffer + sizeof (ShortInt);
	ShortInt ty = cltbf->hdr.trantype;
	unsigned short int  size  = 0, size1 = 0;
	char rtype;
	
	rtype = *ptr;
	ptr += sizeof (char);
	if (rtype == 'E') { /** Execute Query */
		ShortInt len = *(ShortInt *)ptr;
		ptr += sizeof(ShortInt);
		memtozstr(ptr, buff, len);
		size = jdb_parse(buff, buffer);
		while (size > BUFFSIZE1) {
			mov_mem(buffer + size1, buff, BUFFSIZE1);
			send_packet(ty, buff, BUFFSIZE1, TRUE);
			size -= BUFFSIZE1;
			size1 += BUFFSIZE1;
		}
		send_packet(ty, buffer + size1, size, FALSE);
	}
	else {
		ShortInt fno = *(ShortInt*)ptr;
		ptr += sizeof (ShortInt);
		ShortInt keyno = *(ShortInt*)ptr;
		ptr += sizeof (ShortInt);
		ShortInt kelno = *(ShortInt*)ptr;
		ptr += sizeof (ShortInt);
		ShortInt keybfssize  = *(ShortInt*)ptr;
		ptr += sizeof (ShortInt);
		*(ShortInt*)buffer = OK;
		size = sizeof (ShortInt);
		if (keyno == -1 ? db->fseqrcd(fno, (void*)buff) == OK :
				db->include_rcd(fno, keyno, ptr, (void*)buff) == OK) {
			ret = OK;
			if(keyno != -1) {
				switch (rtype) {
					case 'L':
							if (db->last_rcd(fno, keyno, (void*)buff) != OK)
							ret =  ERROR;
						break;
					case 'I':
							if (db->first_rcd(fno, keyno, (void*)buff) != OK)
							ret =  ERROR;
						break;
					case 'P':
						if (db->prev_rcd(fno, keyno, (void*)buff) != OK)
							ret = ERROR;
						break;
					case 'N':
						if (db->next_rcd(fno, keyno, (void*)buff) != OK)
							ret =  ERROR;
						break;
				}
				ptr += keybfssize;
			}
			if (ret == OK) {
				
				/*for (int i = 0; index_ele [fno] [keyno-1] [i] != 0; i++) {
					if (is_string(eltype [index_ele [fno] [keyno-1] [i]]) ||
						eltype[index_ele [fno] [keyno-1] [i]] == 'D'){
						ptr +=  ellen [index_ele [fno] [keyno-1] [i]];
					}
					else if(eltype[index_ele [fno] [keyno-1] [i]] == 'x')
						ptr += sizeof (unsigned int);
					else if(eltype[index_ele [fno] [keyno-1] [i]] == 'U')
						ptr += sizeof (unsigned int);
					else if(eltype[index_ele [fno] [keyno-1] [i]] == 'I')
						ptr += sizeof (int);
					else
						ptr += sizeof (ShortInt);
				}*/
				ShortInt count = *(ShortInt*)ptr;
				ptr += sizeof (ShortInt);
				for(int j = 0; j < count; j++) {
					if (is_string(eltype [*(ShortInt*)(ptr + (j*sizeof (ShortInt)))]) ||
						eltype[*(ShortInt*)(ptr + (j*sizeof (ShortInt)))] == 'D') {
						mov_mem((buff + epos_file(*(ShortInt*)(ptr + (j*sizeof (ShortInt))), fno)), buffer + size,
							ellen [*(ShortInt*)(ptr + (j*sizeof (ShortInt)))]);
						size += ellen [*(ShortInt*)(ptr + (j*sizeof (ShortInt)))];
					}
					else {
						if (eltype[*(ShortInt*)(ptr + (j*sizeof (ShortInt)))] == 'x') {
							*(unsigned int*)(buffer + size) = *(unsigned int*)(buff +
								epos_file(*(ShortInt*)(ptr + (j*sizeof (ShortInt))), fno));
							size += sizeof (unsigned int);
						}
						else if (eltype[*(ShortInt*)(ptr + (j*sizeof (ShortInt)))] == 'U') {
							*(unsigned int*)(buffer + size) = *(unsigned int*)(buff +
								epos_file(*(ShortInt*)(ptr + (j*sizeof (ShortInt))), fno));
							size += sizeof (unsigned int);
						}
						else if (eltype[*(ShortInt*)(ptr + (j*sizeof (ShortInt)))] == 'I') {
							*(int*)(buffer + size) = *(int*)(buff +
								epos_file(*(ShortInt*)(ptr + (j*sizeof (ShortInt))), fno));
							size += sizeof (int);
						}
						else {
							*(ShortInt*)(buffer + size) = *(ShortInt*)(buff +
								epos_file(*(ShortInt*)(ptr + (j*sizeof (ShortInt))), fno));
							size += sizeof (ShortInt);
						}
					}
				}
			}
		}
		if (ret == ERROR) {
			*(ShortInt*) buffer = ERROR;
			size = sizeof (ShortInt);
		}
		send_packet(cltbf->hdr.trantype, buffer, size);
	}
}