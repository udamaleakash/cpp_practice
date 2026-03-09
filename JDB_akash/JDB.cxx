
/*
 * File:   JDB.cxx
 * Author: root
 *
 * Created on November 16, 2013, 12:41 PM
 */

#include <KIM_Window.h>
#include <screen.h>
#include <KIM_Tabs.h>
#include <theme.h>
#include "PostingHeader.h"
#include "../../cserver/bank.c1"
#include "../global_para.h"
#include "JDB.h"


KIM_Window *jdb_wnd(KEntry *entry)
{
	Fl_Group::current(NULL);
	JDB *wnd = new JDB(entry, screen_x(40), screen_y(60), screen_x(950), screen_y(675), "JDB");
	entry->clear = JDB::clear;
	entry->save = JDB::save;
	entry->find = JDB::find;
	entry->del = JDB::del;
	entry->validate = JDB::validate;
	entry->set_parent_wnd(kimdesktop);
	wnd->callback(windowCloseCallback, entry);
	wnd->end();
	wnd->redraw();
	kimdesktop->add(wnd);
	wnd->show();
	Fl_Group::current(NULL);
	return wnd;
}

void JDB::jdb_cb(Fl_Widget *widget, void *data)
{
	Fl_Menu_Bar *menu = (Fl_Menu_Bar *)widget;
	menu->user_data(data);
	int i;

	KEntry *entry = KEntry::create_entry(0, "", svrfl, menu, jdb_wnd);
	entry->set_parent_wnd(kimdesktop);
	entry->get_update();
}

JDB::JDB(KEntry *entry, int X, int Y, int W, int H, const char *title) : KIM_Window(entry, X, Y, W, H, title, false, true)
{
	static char s[200];
	int kx = screen_x(10);
	int ky = screen_y(10);
	tab_counter_ = 0;
	tbl_label_ = NULL;

	jres = new JResultset(this);
	keybfssize = 0;
	ansbuff = NULL;
	input = NULL;
	bfs = NULL;
	pbfs = NULL;
	ellist = NULL;
	rtype = ' ';

	for (total_tables = 0; dbfiles[total_tables] != 0; total_tables++);
	total_tables--;

	KIM_Tabs *tab = new KIM_Tabs(kx, ky, W - screen_x(30), screen_y(605));

	group1 = new Fl_Group(kx, ky + screen_y(20), W - screen_x(30), screen_y(570), "Database Details");
	group1->box(box_type[theme.box.kmdibox.nobox]);
	group1->color(color_code[theme.color.wcolor.groupcolor]);
	group1->labelsize(screen_y(12));

	kx += screen_x(10);
	ky += screen_y(30);
	choice = new Fl_Input(kx, ky, screen_x(200), screen_y(25), " ");
	group1->add(choice);

	ky += screen_y(30);

	tree = new Fl_Tree(kx, ky, screen_x(200), screen_y(400), "");
	tree->labelsize(screen_y(12));
	tree->sortorder(FL_TREE_SORT_ASCENDING);

	for (int c = 0; dbfiles[c] != 0; c++)
	{
		sprintf(s, "Tables/%s", dbfiles[c]);
		tree->add(s);
	}
	for (int c = 0; denames[c] != 0; c++)
	{
		sprintf(s, "Elements/%s", denames[c]);
		tree->add(s);
	}
	tree->marginleft(15);
	tree->showroot(0);
	tree->close("Tables");
	tree->close("Elements");
	group1->add(tree);
	tree->callback(TreeCallback, this);

	out = new Fl_Browser(tree->w() + screen_x(30), ky, screen_x(200), screen_y(400), "");
	out->textsize(screen_y(12));
	out->column_char('\t');
	out->type(FL_MULTI_BROWSER);
	out->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	group1->add(out);

	ep_ = new KIM_Scroll(tree->w() + out->w() + screen_x(50), tree->y() - screen_y(15), screen_x(450), screen_y(461));
	ep_->type(Fl_Scroll::BOTH);
	ep_->color(FL_WHITE);
	group1->add(ep_);

	key = new Fl_Browser(tree->x(), tree->h() + screen_y(85), screen_x(400), screen_y(90), "");
	key->textsize(screen_y(12));
	key->column_char('\t');
	key->type(FL_HOLD_BROWSER);
	key->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
	group1->add(key);

	kx = screen_x(460);
	ky = out->h() + screen_x(125);

	f_btn = new KIM_Button(kx, ky, screen_x(70), screen_y(22), "<<", TRUE);
	f_btn->tooltip("First");
	f_btn->labelcolor(FL_WHITE);
	f_btn->callback(JDB::first_cb, (void *)entry);
	group1->add(f_btn);

	kx += f_btn->w() + screen_x(20);

	prev_btn = new KIM_Button(kx, ky, screen_x(50), screen_y(22), "@<", TRUE);
	prev_btn->tooltip("Previous");
	prev_btn->labelcolor(FL_WHITE);
	prev_btn->callback(JDB::prev_cb, (void *)entry);
	group1->add(prev_btn);

	kx += prev_btn->w() + screen_x(20);

	next_btn = new KIM_Button(kx, ky, screen_x(60), screen_y(22), "@>", TRUE);
	next_btn->tooltip("Next");
	next_btn->labelcolor(FL_WHITE);
	next_btn->callback(JDB::next_cb, (void *)entry);
	group1->add(next_btn);

	kx += next_btn->w() + screen_x(20);

	l_btn = new KIM_Button(kx, ky, screen_x(70), screen_y(22), ">>", TRUE);
	l_btn->tooltip("Last");
	l_btn->labelcolor(FL_WHITE);
	l_btn->callback(JDB::last_cb, (void *)entry);
	group1->add(l_btn);

	group1->end(); // -----------------------------------------------------

	group2 = new Fl_Group(group1->x(), group1->y(), W - screen_x(30),screen_y(570), " Query");
	group2->box(box_type[theme.box.kmdibox.nobox]);
	group2->color(color_code[theme.color.wcolor.groupcolor]); /*color(fl_rgb_color(230, 230, 250));*/
	group2->labelsize(screen_y(12));
	group2->hide();

	kx = group1->x();
	ky = group1->y();

	txtbf = new Fl_Text_Buffer();
	query_fld_ = new Fl_Text_Editor(kx + screen_x(5), ky + screen_y(10), W - screen_x(40), screen_y(90), "");
	query_fld_->buffer(txtbf);
	query_fld_->textsize(screen_y(12));
	group2->add(query_fld_);
	group2->end();
	tab->add(group1);
	tab->add(group2);
	tab->end();

	kx = query_fld_->x();
	ky = query_fld_->y() + screen_y(110);
	
	exe_btn_ = new KIM_Button(kx +screen_x(100), ky, screen_x(100), screen_y(22), "Execute Query", TRUE);
	exe_btn_->callback(JDB::exe_query, (void *)entry);
	exe_btn_->shortcut(FL_CTRL + 'e');
	group2->add(exe_btn_);

	clr_qur_ = new KIM_Button(kx +screen_x(250), ky, screen_x(100), screen_y(22), "Clear Query", TRUE);
	clr_qur_->callback(JDB::clr_query, (void *)entry);
	clr_qur_->shortcut(FL_CTRL + 'c');
	group2->add(clr_qur_);

	clr_all_ = new KIM_Button(kx +screen_x(400), ky, screen_x(100), screen_y(22), "Clear All", TRUE);
	clr_all_->callback(JDB::clear_all, (void *)entry);
	clr_all_->shortcut(FL_CTRL + 'a');
	group2->add(clr_all_);

	kx = query_fld_->x();
	ky = exe_btn_->y() + 40;

	res_tab = new KIM_Tabs(kx , screen_y(170), screen_x(910), screen_y(375));
	group2->add(res_tab);

	tab->shortcut(FL_CTRL + 'd', 0);
	tab->shortcut(FL_CTRL + 'q', 1);
	add(tab);
	end();
	show();
	redraw();
}

JResultset::JResultset(void *p)
{
	jinit_res();
	parent = p;
}

JResultset::JResultset()
{
	jinit_res();
}

void JResultset::jinit_res()
{
	parent = NULL;
	jgroup = NULL;
	glabel = NULL;
	jres_table = NULL;
	nresult = 0;
	count = 10;
}

JResultset::~JResultset()
{
	printf("JResultset::~JResultset()\r\n");
	if (jgroup)
	{
		for (int i = 0; i < nresult; i++)
		{
			if (jgroup[i])
			{
				jgroup[i]->parent()->remove(jgroup[i]);
				delete jgroup[i];
			}
		}
		free(jgroup);
	}

	if (glabel)
	{
		for (int i = 0; i < nresult; i++)
		{
			if (glabel[i])
			{
				free(glabel[i]);
			}
		}
		free(glabel);
	}
	nresult = 0;
	count = 10;
}

void JResultset::jres_tab(char *jtablename, COL_PROPERTY *col)
{
	JDB *wnd = (JDB *)parent;

	int kx = wnd->query_fld_->x();
	int ky = wnd->exe_btn_->y() + 20;

	++nresult;
	if (!jgroup || nresult >= count)
	{
		count += 10;
		jgroup = (Fl_Group **)realloc(jgroup, sizeof(Fl_Group *) * count);
		glabel = (char **)realloc(glabel, sizeof(char *) * count);
		jres_table = (kgrid **)realloc(jres_table, sizeof(kgrid *) * count);
	}
	glabel[nresult - 1] = (char *)malloc(strlen(jtablename) + 2);
	memtozstr(jtablename, glabel[nresult - 1], strlen(jtablename));
	jgroup[nresult - 1] = new Fl_Group(kx, ky + 40, wnd->query_fld_->w(), screen_y(330), glabel[nresult - 1]);
	jgroup[nresult - 1]->box(FL_THIN_UP_BOX);
	// jgroup[nresult - 1]->color(color_code[theme.color.wcolor.groupcolor]);
	jgroup[nresult - 1]->box(box_type[theme.box.kmdibox.nobox]);
	jgroup[nresult - 1]->labelsize(screen_y(12));
	//->color(fl_rgb_color(230, 230, 250));
	wnd->res_tab->add(jgroup[nresult - 1]);
	wnd->res_tab->value(jgroup[nresult - 1]);
	wnd->redraw();

	jres_table[nresult - 1] = new kgrid(kx + screen_x(5), ky + screen_y(50), screen_x(900), screen_y(310), wnd, 110, col, NULL, NULL,  TRUE);
	jres_table[nresult - 1]->row_header(0);
	jres_table[nresult - 1]->size(screen_x(900), screen_y(310));
	jres_table[nresult - 1]->protect(true);
	jgroup[nresult - 1]->add(jres_table[nresult - 1]);
	jres_table[nresult - 1]->show();
}

void JResultset::jresult(ShortInt count, char *ptr)
{
	ShortInt len;
	char buffer[1024];

	if (count > jres_table[nresult - 1]->rows())
		jres_table[nresult - 1]->rows(jres_table[nresult - 1]->rows() + 100);
	for (int i = 0; i < count; i++)
	{
		len = *(ShortInt *)ptr;
		ptr += sizeof(ShortInt);
		memtozstr(ptr, buffer, len);
		ptr += len;
		jres_table[nresult - 1]->value(buffer, i, 0);

		memtozstr(ptr, buffer, 1);
		ptr += 1;
		jres_table[nresult - 1]->value(buffer, i, 1);

		sprintf(buffer, "%d", *(ShortInt *)ptr);
		ptr += sizeof(ShortInt);
		jres_table[nresult - 1]->value(buffer, i, 2);

		len = *(ShortInt *)ptr;
		ptr += sizeof(ShortInt);
		memtozstr(ptr, buffer, len);
		ptr += len;
		jres_table[nresult - 1]->value(buffer, i, 3);

		len = *(ShortInt *)ptr;
		ptr += sizeof(ShortInt);
		memtozstr(ptr, buffer, len);
		ptr += len;
		jres_table[nresult - 1]->value(buffer, i, 4);
	}
}

JDB::~JDB()
{
	if (jres)
		delete jres;
	if (ansbuff)
		free(ansbuff);
	free_bfs();
	// if(res_tab) {
	// delete txtbf;
	if (tbl_label_)
	{
		for (int i = 0; i < tab_counter_; i++)
			if (tbl_label_[i])
				free(tbl_label_[i]);
		// 			free(tbl_label_);
		tbl_label_ = NULL;
	}
	// res_tab->clear();
	//}
	printf("In JDB::~JDB()\n");
}