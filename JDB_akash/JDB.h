/*
 * File:   JDB.h
 * Author: root
 *
 * Created on November 16, 2013, 12:41 PM
 */

#ifndef JDB_H
#define JDB_H

#include <KInput.h>
#include <KLabel.h>
#include <KChoice.h>
#include <Fl/Fl_Button.H>
#include <FL/Fl_Browser.H>
#include <EntryPart.h>
#include <KChoice.h>
#include <FL/Fl_Input.h>
#include <FL/Fl_Text_Buffer.h>
#include <FL/Fl_Text_Editor.h>
#include "Bank_Window.h"
#include "Fl_Tree.H"
#include <KIM_Scroll.h>
#include <FL/Fl_Scroll.h>
#include <KIM_Tabs.h>
#include <kgrid.h>
#include <KIM_Button.h>
#include <Resolution.h>
#include "../../cserver/jcrawler.h"

class JResultset
{
	ShortInt count;
	ShortInt nresult;
	Fl_Group **jgroup;
	char **glabel;
	void *parent;
	kgrid **jres_table;
	public :
		JResultset();
		JResultset(void*);
		void jinit_res();
		void jres_tab(char *jtablename, COL_PROPERTY*);
		void jresult(ShortInt count, char *ptr);
		~JResultset();
};

class JDB : public KIM_Window {
	Fl_Tree *tree;
	Fl_Browser *out, *key, *in;
	char *ansbuff;
	ShortInt modified_index;
	KChoice *query_;
	void **bfs;
	void **pbfs;
	ShortInt *ellist;
	ShortInt count;
	ShortInt keyno;
	ShortInt fno;
	ShortInt key_ele_cnt;
	KChoice *ftble_;
	Fl_Input *out1;
	KInput **input;
	KIM_Button *btn [10];
	KIM_Scroll *ep_;
	bool isestablish;
	Fl_Group *group1, *group2;
	Fl_Input *choice;
	KIM_Button *next_btn, *prev_btn, *f_btn, *l_btn;
	ShortInt total_tables;
	char rtype;
	char keybfs [4096];
	ShortInt keybfssize;
	ShortInt kelno;
	Fl_Text_Buffer *txtbf;
	Fl_Text_Editor *query_fld_;
	KIM_Button *exe_btn_, *clr_qur_, *clr_all_;
	int tab_counter_;
	char **tbl_label_;
	friend class JResultset;
	JResultset *jres;
public:
	KIM_Tabs *res_tab;
	class JResultset jresultset;
	JDB(KEntry *entry, int X, int Y, int W, int H, const char *title);
	virtual ~JDB();
	static void jdb_cb(Fl_Widget *widget, void *data);
	static ShortInt result_handler(KEntry *, struct server_buffer *);
	static ShortInt save(KEntry *);
	static ShortInt find(KEntry*);
	static ShortInt clear(KEntry *);
	ShortInt find1(KEntry *);
	static ShortInt del(KEntry *);
	static void set_values_handle(void*);
	void set_value();
	ShortInt jinlist(ShortInt el);
	static void establish_fields(void *data);
	static void free_handler(void *data);
	static ShortInt validate(KEntry *, ShortInt);
	static void TreeCallback(Fl_Widget *w, void *data);
	static void next_cb(Fl_Widget *, void *);
	static void prev_cb(Fl_Widget *, void *);
	static void first_cb(Fl_Widget *, void *);
	static void last_cb(Fl_Widget *, void *);
	static ShortInt establish_buff(KEntry *, ShortInt, char *, ShortInt);
	static void exe_query(Fl_Widget*, void *);
	static void clr_query(Fl_Widget*, void *);
	static void clear_all(Fl_Widget*, void *);
	void execute_desc(char *name, char *ptr);
	void free_bfs();
	void make_keybfs();
	ShortInt fill_jdb_buffer(KEntry *, ShortInt, char *);
private:

};
#endif /* JDB_H */