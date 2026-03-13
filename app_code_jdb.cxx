#include <server_connection.h>
#include <KAsk.h>
#include <KAlert.h>
#include <date_new.h>
#include <system.h>
#include <stdarg.h>
#include <sysdef.h>
#include <memory1.h>
#include <date_new.h>
#include <cxxdata.h>
#include <datatype.h>
#include <KInput.h>
#include <RowTable.h>
#include <Fl_Table_Row.H>
#include <KIM_Window.h>
#include "../sle2.0/view/JDB.h"
#include "../cserver/bank.c1"
#include "../../cserver/apptrans.h"
#include "../../cserver/init.h"
#include "../../cserver/validation.h"
#include "../../cserver/errormsg.h"
#include "../sle2.0/global_para.h"
#include "../sle2.0/qualify.h"
#include <MasterQuery.h>


int MAX_SIZE = 0;

ShortInt JDB::result_handler(KEntry *e, struct server_buffer *sbf)
{
	display::result_msg(e->get_window(), sbf);
	return ERROR;
}

void JDB::free_bfs()
{
	if (pbfs) {
	for(int i = 0; i< count; i++)
		if (pbfs [i])
			free(pbfs [i]);
		free(pbfs);
		pbfs = NULL;
	}
	if (bfs) {
		for(int i = 0; i < count; i++)
			if (bfs [i])
				free(bfs [i]);
		free(bfs);
		bfs = NULL;
	}
	if (ellist) {
		free(ellist);
		ellist = NULL;
	}
}

void JDB::free_handler(void *data)
{
	KEntry *e = (KEntry *)data;
	JDB *wnd = (JDB*)e->get_window();
	if (wnd->input)
		for(int i = 0; i < wnd->count; i++)
			if(wnd->input [i])
				wnd->input [i]->hide();
	wnd->free_bfs();
	wnd->prev_btn->deactivate();
	wnd->next_btn->deactivate();
	wnd->f_btn->deactivate();
	wnd->l_btn->deactivate();
	wnd->rtype = ' ';
}

ShortInt JDB::clear(KEntry *e)
{
	JDB *wnd = (JDB*)e->get_window();
	MAX_SIZE = 0;
	if(get_mainthread_id() == pthread_self()){
		wnd->free_handler(e);
	}
	else
		Fl::awake(wnd->free_handler, (void*)e);
	return OK;
}

ShortInt JDB::jinlist(ShortInt el)
{
	for (int i = 0 ; i<count; i++) {
		if (this->ellist [i] == el)
			return i;
	}
	return -1;
}

ShortInt iskeyElement(ShortInt el, ShortInt keyno, ShortInt f)
{
	for(int j = 0; index_ele [f] [keyno-1] [j] != 0; j++) {
		if (el == index_ele [f] [keyno-1] [j])
			return OK;
	}
	return ERROR;
}

void JDB::establish_fields(void *data)
{
	KEntry *e = (KEntry *)data;
	bool isselect;
	JDB *wnd = (JDB*)e->get_window();
	
	int x = screen_x(150), y = screen_y(150);

	wnd->free_bfs();
	if(wnd->input) {
		for(int i = 0; i < wnd->count; i++) {
			wnd->input [i]->parent()->remove(wnd->input [i]);
			delete wnd->input [i];
		}
		free(wnd->input);
		wnd->input = NULL;
	}

	wnd->count = 0;
	wnd->key_ele_cnt = 0;
	if(wnd->key->size()) {
		for(int j = 0; index_ele [wnd->fno] [wnd->keyno-1] [j] != 0; j++) {
			wnd->ellist = (ShortInt*)realloc(wnd->ellist,
					sizeof (ShortInt) *(++wnd->count));
			wnd->key_ele_cnt++;
			wnd->ellist [wnd->count - 1] = index_ele [wnd->fno] [wnd->keyno-1] [j];
		}
	}
	isselect = false;
	for(int i = 3; i < wnd->out->size(); i++) {
		if (wnd->out->selected(i) && (i - 4) >= 0) {
			isselect = true;
			//if (wnd->jinlist (file_ele[wnd->fno][i-4]) == ERROR) {
			if (iskeyElement(file_ele[wnd->fno][i-4], wnd->keyno, wnd->fno) != OK) {
				wnd->ellist = (ShortInt*)realloc(wnd->ellist, sizeof (ShortInt) *(++wnd->count));
				wnd->ellist [wnd->count -1] = file_ele [wnd->fno][i-4];
			}
			//}
		}
	}
	if (!isselect) {
		for (int i = 0; file_ele[wnd->fno][i] != 0; i++) {
			//if (wnd->jinlist (file_ele[wnd->fno][i]) == ERROR) {
			if (iskeyElement(file_ele[wnd->fno][i], wnd->keyno, wnd->fno) != OK) {
				wnd->ellist = (ShortInt*)realloc(wnd->ellist, sizeof (ShortInt) *(++wnd->count));
				wnd->ellist [wnd->count -1] = file_ele [wnd->fno][i];
			}
			//}
		}
	}
	wnd->bfs = (void **)malloc(wnd->count * sizeof(void*));
	wnd->pbfs = (void **)malloc(wnd->count * sizeof(void*));

	wnd->input  = (KInput**)malloc(wnd->count* sizeof (KInput*));
	for(int i = 0; i < wnd->count; i++) {
		wnd->bfs [i] = (char *)malloc(ellen [wnd->ellist [i]] + 1);
		wnd->pbfs [i] = (char *)malloc(ellen [wnd->ellist [i]] + 1);
		wnd->input [i] = new KInput(e, x + screen_x(470), y + screen_y(10), wnd->ellist [i],
			 denames[wnd->ellist [i]], (char *)wnd->bfs[i], FALSE, TRUE);
		if(wnd->key->size()) {
			if(i < wnd->key_ele_cnt)
				wnd->input [i]->protect(true);
			if(i == wnd->key_ele_cnt)
				wnd->input [i]->take_focus();
		}
		wnd->ep_->add(wnd->input [i]);
		y += screen_y(30);
	}
	if(wnd->key->size()) 
		if(wnd->count != wnd->key_ele_cnt)
			wnd->input[wnd->key_ele_cnt]->take_focus();
	else
		wnd->input[0]->take_focus();
	wnd->isestablish = true;
}

ShortInt JDB::find1(KEntry *e)
{
	char *ptr, buffer [BUFFSIZE];
	unsigned int size;
	databasexx *db = e->get_database();

	if (fno == -1) {
		KAlert::show_message(this, "Please Select File",
						"Error", (KMDI_ALERT)KMDI_ERROR, 360, 160);
		return ERROR;
	}
	if (key->size() && keyno == -1) {
		KAlert::show_message(this, "Please Select Key",
						"Error", (KMDI_ALERT)KMDI_ERROR, 360, 160);
		return ERROR;
	}

	ptr = buffer;
	*(ShortInt*)ptr = FND_JDB;
	size = sizeof (ShortInt);
	*(ptr + size) = rtype;
	size += sizeof (char);
	*(ShortInt*)(ptr + size) =  fno;
	size += sizeof (ShortInt);
	*(ShortInt*)(ptr + size) =  keyno;
	size += sizeof (ShortInt);
	*(ShortInt*)(ptr + size) =  kelno;
	size += sizeof (ShortInt);
	*(ShortInt*)(ptr + size) = keybfssize;
	size += sizeof (ShortInt);
	mov_mem(keybfs, ptr + size, keybfssize);
	size += keybfssize;
	*(ShortInt*)(ptr + size) = count;
	size += sizeof (ShortInt);
	for (int i = 0; i < count; i++) {
		*(ShortInt*)(ptr + size) = ellist [i];
		size += sizeof (ShortInt);
	}
	ansbuff = db->get_usrrcd(buffer, size);
	ptr = ansbuff;
	entry->user_data(NULL);
	if (*(ShortInt*) ptr != OK) {
			if (rtype == 'F')
				KAlert::show_message(this, errormsg[NT_FND],
						"Error", (KMDI_ALERT)KMDI_ERROR, 360, 160);
			else
				if (rtype == 'N' || rtype == 'L')
					KAlert::show_message(this, "Last Record",
						"Error", (KMDI_ALERT)KMDI_ERROR, 360, 160);
				else
					if (rtype == 'P' || rtype == 'I')
						KAlert::show_message(this, "First Record",
							"Error", (KMDI_ALERT)KMDI_ERROR, 360, 160);
			return ERROR;
	}
	rtype = 'F';
	if (get_mainthread_id()== pthread_self())
		set_value();
	else
		Fl::awake(set_values_handle, (void *)this);
	return OK;
}

char **lable = {NULL};
ShortInt elist[100];

ShortInt JDB::find(KEntry* e)
{
	int count = 0;
	JDB *wnd = (JDB*)e->get_window();
	KAsk *input_wnd = new KAsk(wnd, ASK_INTPUT);
	wnd->keyno = -1;
	wnd->fno = -1;

	wnd->isestablish = false;
	Fl_Tree_Item *item = (Fl_Tree_Item*)wnd->tree->item_clicked();
    if (item) {
		for(int c = 0; dbfiles [c] != 0; c++) {
			if (strcmp(dbfiles [c], item->label()) == 0) {
				wnd->fno = c;
				break;
			}
		}
	}
	for(int i = 1; i<= wnd->key->size(); i++) {
		if (wnd->key->selected(i)) {
			wnd->keyno = i;
			count++;
		}
	}
	if (count > 1) {
		KAlert::show_message(wnd, "Multiple Key Selection Not Allowed",
						"Error", (KMDI_ALERT)KMDI_ERROR);
		return ERROR;
	}
	if (wnd->fno == -1) {
		KAlert::show_message(wnd, "Please Select File",
						"Error", (KMDI_ALERT)KMDI_ERROR, 360, 160);
		return ERROR;
	}
	if (wnd->key->size() && wnd->keyno == -1) {
		KAlert::show_message(wnd, "Please Select Key",
						"Error", (KMDI_ALERT)KMDI_ERROR, 360, 160);
		return ERROR;
	}
	wnd->kelno = 0;
	int h = 110;
	lable = (char **)malloc(100*sizeof (char*));

	if(wnd->key->size()) {
		for (wnd->kelno = 0; index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno] != 0; wnd->kelno++) {
			elist[wnd->kelno] = index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno];
			int len = strlen(denames [index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]]) + 4;
			lable [wnd->kelno] = (char *)malloc(len);
			strcpy(lable [wnd->kelno], denames [index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]]);
			strcat(lable [wnd->kelno], ":");
			h += 20;
		}
	}
	elist[wnd->kelno] = -1;
	input_wnd->ellist(elist, lable);
	input_wnd->size( wnd->w()/3, screen_y(200), screen_x(300), screen_y(270));
	input_wnd->title("Find");

	if(get_mainthread_id() == pthread_self()){
		wnd->establish_fields(e);
	}
	else
		Fl::awake(wnd->establish_fields, (void*)e);
	while(!wnd->isestablish)
		usleep(10);
	wnd->keybfssize = 0;
	if(!wnd->key->size()) {
		delete input_wnd;
		input_wnd = NULL;
		return wnd->find1(e);
	}
	char kbf [100], kbf1 [100];
	if (input_wnd->show()) {
		for (wnd->kelno = 0; index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno] != 0; wnd->kelno++) {
			//if (is_string(eltype [index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]]) ||
 			//	eltype[index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]] == 'D') {
 				kinput_elcpy(kbf, input_wnd->getValue(wnd->kelno), index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]);
				test_key_buffer(kbf1, index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno], kbf);
				mov_mem(kbf1, wnd->keybfs + wnd->keybfssize, ellen [index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]]);
				wnd->keybfssize += ellen [index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]];
// 			}
// 			else {
// 				ShortInt id = atoi(input_wnd->getValue(wnd->kelno));
// 				test_key_buffer(kbf1, index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno], (char *)&id);
// 				mov_mem(kbf1, wnd->keybfs + wnd->keybfssize, ellen [index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]]);
// 				wnd->keybfssize += sizeof (ShortInt);
//  			}
		}
		return wnd->find1(e);
	}
	delete input_wnd;
	input_wnd = NULL;
	return ERROR;
}

ShortInt JDB::establish_buff(KEntry *e, ShortInt i, char *buffer, ShortInt size)
{
	JDB *wnd = (JDB*)e->get_window();
	if(eltype[wnd->ellist [i]] == 'W') {
		return 0;
	}
	else if (is_string(eltype [wnd->ellist [i]]) ||
		eltype[wnd->ellist [i]] == 'D') {
		mov_mem((char *)wnd->bfs[i], buffer + size, ellen[wnd->ellist [i]]);
		return  ellen[wnd->ellist [i]];
	}
	else {
		if (eltype[wnd->ellist [i]] == 'x') {
			*(unsigned int *)(buffer + size) = *(unsigned int*)wnd->bfs [i];
			return sizeof (unsigned int);
		}
		else if (eltype[wnd->ellist [i]] == 'U') {
			*(unsigned int *)(buffer + size) = *(unsigned int*)wnd->bfs [i];
			return sizeof (unsigned int);
		}
		if (eltype[wnd->ellist [i]] == 'I') {
			*(int *)(buffer + size) = *(int*)wnd->bfs [i];
			return sizeof (int);
		}
		else {
			*(ShortInt*)(buffer + size)= *(ShortInt*)wnd->bfs [i];
			return sizeof (ShortInt);
			}
		}
}

ShortInt JDB::fill_jdb_buffer(KEntry *e,ShortInt op, char *buffer)
{
	ShortInt size = 0;
	char *ptr = buffer;
	ShortInt *cnt;
	*(ShortInt *)(ptr + size) = fno;
	size += sizeof(ShortInt);
	*(ShortInt *)(ptr + size) = keyno;
	size += sizeof(ShortInt);
	for (int i = 0; i < key_ele_cnt; i++) {
		ShortInt size1 = establish_buff(e, i, ptr, size);
		size += size1;
	}
	if(op == RTN_RCD)
	{
		cnt = (ShortInt *)(ptr + size);
		size += sizeof(ShortInt);
		*cnt = 0;
		for(int i = modified_index ; i <  count; i++) {
			if( eltype[ellist [i]] != 'Z'&&
				strncmp((char *)bfs[i], (char *)pbfs[i], ellen[ellist [i]]) ==  0)
				continue;
			if( eltype[ellist [i]] == 'Z') {
				if(atoll((char *)bfs[i]) == atol((char *)pbfs[i]))
					continue;
			}
			if (eltype[ellist [i]] == 'W')
				continue;
			(*cnt)++;
			*(ShortInt *)(ptr + size) = ellist [i];
			size += sizeof(ShortInt);
			ShortInt size1 = establish_buff(e, i, ptr, size);
			size += size1;
		}
	}
	return size;
}

ShortInt JDB::save(KEntry *e)
{
	char buffer[BUFFSIZE];
	char *ptr;
	int size = 0;
	ptr = buffer;
	 JDB *wnd = (JDB*)e->get_window();
	*(ShortInt *)ptr = (ShortInt)RTN_RCD;
	ptr += sizeof(ShortInt);
	size += sizeof(ShortInt);
	size += wnd->fill_jdb_buffer(e, RTN_RCD, ptr);
	return get_server_connection()->send_packet(e,JDBR, buffer, size);
}

ShortInt JDB::del(KEntry* e)
{
	char buffer[BUFFSIZE];
	char *ptr;
	int size = 0;
	ptr = buffer;
	 JDB *wnd = (JDB*)e->get_window();
	*(ShortInt *)ptr = (ShortInt)DEL_RCD;
	ptr += sizeof(ShortInt);
	size += sizeof(ShortInt);
	size += wnd->fill_jdb_buffer(e, DEL_RCD, ptr);
	return get_server_connection()->send_packet(e, JDBR, buffer, size);
}

ShortInt JDB::validate(KEntry *e, ShortInt flag)
{
	int i;
	JDB *wnd = (JDB*)e->get_window();

	if(wnd->bfs == NULL || wnd->pbfs == NULL)
		return ERROR;

	switch(flag) {
		case RTN_SCR :
			for (i = 0; i < wnd->count; i++) {
				if(eltype[wnd->ellist [i]] != 'Z' &&
				 		strncmp((char *)wnd->bfs[i], (char *)wnd->pbfs[i], ellen[wnd->ellist [i]]) !=  0)
						break;
				if(eltype[wnd->ellist [i]] == 'Z') {
					if(atoll((char *)wnd->bfs[i]) != atoll((char *)wnd->pbfs[i]))
						break;
				}
			}
			if(i == wnd->count) {
				KAlert::show_message(wnd->entry->get_window(), "Nothing Is Modified",
							"Error", (KMDI_ALERT)KMDI_ERROR, 360, 160);
				return ERROR;
			}
			else
				wnd->modified_index = i;
		case DEL_RCD :
				break;
	}
	return OK;
}

void JDB::TreeCallback(Fl_Widget *w, void *data)
{
	char buf [500];
	char buf1 [500];
	Fl_Tree *tree = (Fl_Tree*)w;
	JDB *wnd = (JDB*)data;

	Fl_Tree_Item *item = (Fl_Tree_Item*)tree->item_clicked();
	if (item) {
		wnd->out->clear();
		wnd->key->clear();
		if(strncmp(item->parent()->label(), "Elements", 7) == 0) {
			for(int c = 0; denames [c] != 0; c++) {
				if (strcmp(denames [c], item->label()) == 0) {
					wnd->out->add(" ");
					sprintf(buf1, "Element : %s", denames [c]);
					wnd->out->add(buf1);
					wnd->out->add(" ");
					sprintf(buf1, "Element Type : %C", eltype [c]);
					wnd->out->add(buf1);
					wnd->out->add(" ");
					sprintf(buf1, "Element Length : %d", ellen [c]);
					wnd->out->add(buf1);
					wnd->out->add(" ");
					sprintf(buf1, "Element Mask : %s", elmask [c]);
					wnd->out->add(buf1);
					wnd->out->add(" ");
					sprintf(buf1, "Element Type : %s", eldisp [c]);
					wnd->out->add(buf1);
				}
			}
		}
		int c = 0;
		if (strncmp(item->parent()->label(), "Tables", 6) == 0) {
			for(c = 0; dbfiles [c] != 0; c++) {
				if (strcmp(dbfiles [c], item->label()) == 0) {
					wnd->out->add(" ");
					sprintf(buf, "file %s", dbfiles[c]);
					wnd->out->add(buf);
					wnd->out->add(" {");
					for(int j = 0; file_ele [c] [j] != 0; j++) {
						sprintf(buf, " \t%s,", denames[file_ele [c] [j]]);
						wnd->out->add(buf);
					}
					wnd->out->add("}");
					break;
				}
			}
			if (c && c < wnd->total_tables)
				for(int k = 0; index_ele [c] [k] != 0; k++) {
					sprintf(buf, "key %s ", dbfiles[c]);
					for (int kno = 0; index_ele [c] [k] [kno] != 0; kno++) {
						if (!kno)
							sprintf(buf1, "%s ", denames[index_ele [c] [k][kno]]);
						else
							sprintf(buf1, ", %s", denames[index_ele [c] [k][kno]]);
						strcat(buf, buf1);
					}
					wnd->key->add(buf);
				}
		}
        tree->select(item);
    }
}

void JDB::set_values_handle(void*d)
{
	JDB *wnd = (JDB*)d;
	wnd->set_value();
}

void JDB::set_value()
{
	char *ptr;
	KEntry *e = this->get_entry();
	JDB *wnd =(JDB *) e->get_window();
	ShortInt size = 0 ; 
	ptr = ansbuff;
	
	char buff [200];
	size += sizeof(ShortInt);
	for (int i = 0; i < wnd->count; i++) {
		if (is_string(eltype [wnd->ellist [i]]) ||
			eltype[wnd->ellist [i]] == 'D') {
			memtozstr(ptr + size, (char*)bfs[i], ellen [wnd->ellist [i]]);
			memtozstr(ptr + size, (char*)pbfs[i], ellen [wnd->ellist [i]]);
			size += ellen [wnd->ellist [i]];
			if (eltype[wnd->ellist [i]] == 'D')
				input [i]->set_date((char*)bfs[i]);
			else {
				sprintf(buff, "%*s", ellen [wnd->ellist [i]], (char*)bfs[i]);
				input [i]->value(buff);
			}
		}
		else {
			if (eltype[wnd->ellist [i]] == 'x') {
				*(unsigned int *)bfs [i] = *(unsigned int*)(ptr + size);
				*(unsigned int *)pbfs [i] = *(unsigned int*)(ptr + size);
				size += sizeof (unsigned int);
				sprintf(buff, "%*lu", ellen [wnd->ellist [i]], *(unsigned int *)bfs [i]);
				input [i]->value(buff);
			}
			else if (eltype[wnd->ellist [i]] == 'U') {
				*(unsigned int *)bfs [i] = *(unsigned int*)(ptr + size);
				*(unsigned int *)pbfs [i] = *(unsigned int*)(ptr + size);
				size += sizeof (unsigned int);
				sprintf(buff, "%*lu", ellen [wnd->ellist [i]], *(unsigned int *)bfs [i]);
				input [i]->value(buff);
			} 
			else if (eltype[wnd->ellist [i]] == 'I') {
				*(int *)bfs [i] = *(int*)(ptr + size);
				*(int *)pbfs [i] = *(int*)(ptr + size);
				size += sizeof (int);
				sprintf(buff, "%*ld", ellen [wnd->ellist [i]], *(int *)bfs [i]);
				input [i]->value(buff);
			}
			else {
				*(ShortInt *)bfs [i] = *(ShortInt*)(ptr + size);
				*(ShortInt *)pbfs [i] = *(ShortInt*)(ptr + size);
				size += sizeof (ShortInt);
				sprintf(buff, "%0*d", ellen [wnd->ellist [i]], *(ShortInt*)bfs[i]);
				input [i]->value(buff);
			}
		}
	}
	
	e->set_isexist(1);
	if(wnd->key->size()) {
		if(wnd->count != wnd->key_ele_cnt) {
			wnd->input[wnd->key_ele_cnt]->take_focus();
			wnd->ep_->focus(wnd->input[wnd->key_ele_cnt]);
			Fl::focus(wnd->input[wnd->key_ele_cnt]);
		}
	wnd->prev_btn->activate();
	wnd->next_btn->activate();
	wnd->f_btn->activate();
	wnd->l_btn->activate();
	}
	else {
		wnd->input[0]->take_focus();
		wnd->prev_btn->deactivate();
		wnd->next_btn->deactivate();
		wnd->f_btn->deactivate();
		wnd->l_btn->deactivate();
	}
}

void JDB::make_keybfs()
{
// 	int j = 0;
	KEntry *e = this->get_entry();
	JDB *wnd =(JDB *) e->get_window();
	keybfssize = 0;
	char kbf [100], kbf1 [100];
	wnd->keybfssize = 0;
	for(int i = 0; i< wnd->count; i++)
	{
		for (wnd->kelno = 0; index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno] != 0; wnd->kelno++) {
			if (wnd->ellist [i] == index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]) {
			//	if (is_string(eltype [index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]]) ||
			//		eltype[index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]] == 'D') {
					kinput_elcpy(kbf, wnd->input [i]->value(),
							index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]);
					test_key_buffer(kbf1, index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno], kbf);
					mov_mem(kbf1, wnd->keybfs + wnd->keybfssize,
						ellen [index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]]);
					wnd->keybfssize += ellen [index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]];
// 				}
// 				else {
// 					ShortInt id = atoi((char*)wnd->input [i]->value());
// 					test_key_buffer(kbf1, index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno],
// 						(char *)&id);
// 					mov_mem(kbf1, wnd->keybfs + wnd->keybfssize,
// 						ellen [index_ele [wnd->fno] [wnd->keyno-1] [wnd->kelno]]);
// 					wnd->keybfssize += sizeof (ShortInt);
// 				}
			}
		}
	}
}

void JDB::next_cb(Fl_Widget *w, void *data)
{
	KEntry *e = (KEntry*)data;
	JDB *wnd = (JDB*)e->get_window();
	wnd->make_keybfs();
	wnd->rtype = 'N';
	wnd->find1(e);
}

void JDB::prev_cb(Fl_Widget *w, void *data)
{
	KEntry *e = (KEntry*)data;
	JDB *wnd = (JDB*)e->get_window();
	wnd->make_keybfs();
	wnd->rtype = 'P';
	wnd->find1(e);
}

void JDB::first_cb(Fl_Widget *w, void *data)
{
	KEntry *e = (KEntry*)data;
	JDB *wnd = (JDB*)e->get_window();
	wnd->make_keybfs();
	wnd->rtype = 'I';
	wnd->find1(e);
}

void JDB::last_cb(Fl_Widget *w, void *data)
{
	KEntry *e = (KEntry*)data;
	JDB *wnd = (JDB*)e->get_window();
	wnd->make_keybfs();
	wnd->rtype = 'L';
	wnd->find1(e);
}

void JDB::clear_all(Fl_Widget *w, void *data)
{
	KEntry *e = (KEntry *) data;
	JDB *wnd = (JDB *) e->get_window();
	
	wnd->txtbf->text("");
	//wnd->res_tab->clear();
	wnd->redraw();
}

void JDB::clr_query(Fl_Widget *w, void *data)
{
	KEntry *e = (KEntry *) data;
	JDB *wnd = (JDB *) e->get_window();
	wnd->txtbf->text("");
}

void JDB::exe_query(Fl_Widget *w, void *data)
{
	char *str = NULL, *ptr, buffer [BUFFSIZE], rtype = 'E';
	ShortInt ret = 0;
	unsigned int size = 0;

	KEntry *e = (KEntry *) data;
	databasexx *db = e->get_database();
	JDB *wnd = (JDB *) e->get_window();

	JCrawler *jcrawler = new JCrawler();

	str = wnd->txtbf->selection_text();
	if(str == NULL || strlen(str) == 0)
		str = wnd->txtbf->text();

	if(str != NULL && strlen(str) != 0) {
		jcrawler->set_query(str);
		if((ret = jcrawler->isvalid_dml()) != OK) {
			KAlert::show_message(wnd, dml_errormsg[ret], "Error",
				(KMDI_ALERT)KMDI_ERROR);
			return;
		}
		if((ret = jcrawler->parse()) != OK) {
			KAlert::show_message(wnd, dml_errormsg[ret], "Error",
				(KMDI_ALERT)KMDI_ERROR);
			return;
		}
		ptr = buffer;
		*(ShortInt*)ptr = FND_JDB;
		size = sizeof (ShortInt);
		*(ptr + size) = rtype;
		size += sizeof (char);
		*(ShortInt *)(ptr + size) = strlen(str);
		size += sizeof(ShortInt);
		mov_mem(str, ptr + size, strlen(str));
		size += strlen(str);
		wnd->ansbuff = db->get_usrrcd(buffer, size);
		ptr = wnd->ansbuff;
		if(*(ShortInt *)ptr == OK) {
			char label [400];
			ptr += sizeof(ShortInt);
			ShortInt len = *(ShortInt *)ptr;
			ptr += sizeof(ShortInt);
			memtozstr(ptr, label, len);
			ptr += len;
			ShortInt count = *(ShortInt *) ptr;
			ptr += sizeof(ShortInt);
			static COL_PROPERTY col[] = {
				{0, (char) NULL, 25, (KGRID) Fl_OUTPUT, "Element",
					"_________________________", (Fl_Align) FL_ALIGN_LEFT},
				{0, (char) NULL, 0, (KGRID) Fl_OUTPUT, "Type", "_",
					FL_ALIGN_LEFT},
				{0, (char) NULL, 0, (KGRID) Fl_OUTPUT, "Length",
					"_____", (Fl_Align) FL_ALIGN_LEFT},
				{0, (char) NULL, 100, (KGRID) Fl_OUTPUT, "Mask",
					"_________________________________________________________________", (Fl_Align) FL_ALIGN_LEFT},
				{0, (char) NULL, 100, (KGRID) Fl_OUTPUT, "Description",
					"__________________________________________________________________________", (Fl_Align) FL_ALIGN_LEFT},
				{0, 0, 0, (KGRID) 0, 0, 0, (Fl_Align) NULL}
			};
			wnd->jres->jres_tab(label, col);
			wnd->jres->jresult(count, ptr);
		}
		else {
			ret = *(ShortInt *)ptr;
			KAlert::show_message(wnd, dml_errormsg[ret], "Error",
				(KMDI_ALERT)KMDI_ERROR);
			return;
		}
	}
}
