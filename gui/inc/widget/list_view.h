#pragma once

#include "../core/wnd_base.h"

#include "../common/common_ctrl.h"

NS_GUI_BEGIN

enum lv_item_state {
	//! item has focus
	focused = 0x0001,
	//! selected. Appearance of a selected item depends on whether it has the focus 
	selected = 0x0002,
	//! marked for a cut-and-paste operation
	cut = 0x0004,
	//! it's highlighted as a drag-and-drop target.
	drop_highlight= 0x0008,
	glow = 0x00010,
	activating = 0x00020,
	//! mask to retrieve the item's overlay image idx
	overlay_mask = 0x000F00
};

struct lv_col {
	int width;
	string text;

	lv_col(const string& text = "", int width = 80) : text(text), width(width) {}
};

struct lv_item {
	int state; // lv_item_state
	int image_index;
	int indent;
	string text;

	lv_item(const string& text, int state, int image_index, int indent)
		: text(text), state(state), image_index(image_index), indent(indent) {}

	lv_item(const string& text) : text(text), state(0), image_index(0), indent(0) {}
};


namespace initor {
	struct list_view : base<list_view> {
		list_view() {
			add_style(LVS_REPORT | LVS_SHOWSELALWAYS | WS_BORDER);
		}
	};
}

struct list_view;

template<>
struct wnd_traits<list_view> {
	typedef initor::list_view initor_t;
};


struct list_view : wnd_base<event::base> {
	typedef wnd_base super;

	property::rw<int> item_count;
	property::rw<lv_item, int, int> item;
	property::rw<lv_col, int> col;
	property::r<int> col_count;
	property::r<int> sel_count;
	property::rw<int> sel;

	virtual void create() {
		super::create();
		full_row_select();
	}
	list_view() {
		INIT_P_RW(list_view, item_count);
		INIT_P_RW(list_view, sel);
		INIT_P_R(list_view, sel_count);
		INIT_P_R(list_view, col_count);

		bind_property(col,
					  bind(&list_view::get_col, this, placeholders::_1),
					  bind(&list_view::set_col, this, placeholders::_1, placeholders::_2));
		bind_property(item, 
					  bind(&list_view::get_item, this, placeholders::_1, placeholders::_2), 
					  bind(&list_view::set_item, this, placeholders::_1, placeholders::_2, placeholders::_3));
	}

	string class_name() {
		return "syslistview32";
	}
	void ensure_visible(int row, bool partially_ok = false) {
		send_message(hwnd, LVM_ENSUREVISIBLE, row, partially_ok);
	}


	int get_sel() {
		return send_message(hwnd, LVM_GETSELECTIONMARK);
	}
	void set_sel(int row) {
		ensure_visible(row);

		LVITEM item = {0};
		item.mask = LVIF_STATE;
		item.state = item.stateMask = LVIS_SELECTED;
		SendMessage(hwnd, LVM_SETITEMSTATE, row, (LPARAM)&item);
	}
	int get_sel_count() {
        return send_message(hwnd, LVM_GETSELECTEDCOUNT);
	}
	int get_item_count() {
		return send_message(hwnd, LVM_GETITEMCOUNT);
	}
	void set_item_count(int count) {
        send_message(hwnd, LVM_SETITEMCOUNT, count);
	}
	lv_item get_item(int row, int col) {

		LVITEM v = {0};
		char buf[512];
		v.pszText = buf;
		v.cchTextMax = 512;
		v.iItem = row;
		v.iSubItem = col;
		v.mask = LVIF_IMAGE | LVIF_INDENT | LVIF_TEXT | LVIF_STATE;
		send_message(hwnd, LVM_GETITEM, 0, &v);

		return lv_item(v.pszText, v.state, v.iImage, v.iIndent);
	}
	void set_item(int row, int col, const lv_item& i) {
		LVITEM x = {0};

		x.iItem = row;
		x.iSubItem = col;
		x.pszText = (char*)i.text.c_str();
		x.mask = LVIF_IMAGE | LVIF_TEXT | LVIF_STATE ;

		send_message(hwnd, LVM_SETITEM, 0, &x);
	}
	void insert_item(int row) {
		LVITEM x = {0};
		x.iItem = row;
		x.pszText = (char*)"";
		x.mask = LVIF_IMAGE | LVIF_INDENT | LVIF_TEXT | LVIF_STATE ;

		send_message(hwnd, LVM_INSERTITEM, 0, &x);
	}
	void add_row(int count = 1) {
		for(int i=0; i<count; i++)
			insert_item(get_item_count());
	}

// #define LIST_COLUMN_FLAGS LVCF_IMAGE | LVCF_ORDER | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH
#define LIST_COLUMN_FLAGS  LVCF_TEXT | LVCF_WIDTH

	lv_col get_col(int idx) {
		LVCOLUMN c = {0};
        c.mask = LIST_COLUMN_FLAGS;
		send_message(hwnd, LVM_GETCOLUMN, idx, &c);
		return lv_col(c.pszText, c.cx);
	}
	// void set_col(lv_col& col, int idx) {
	void set_col(int idx, const lv_col& col) {
		LVCOLUMN x = {0};
        x.mask = LIST_COLUMN_FLAGS;
		x.pszText = (char*)col.text.c_str();
		x.cx = col.width;

		send_message(hwnd, LVM_SETCOLUMN, idx, &x);
	}
	list_view* insert_col(int idx, const lv_col& col) {
		LVCOLUMN x = {0};
        x.mask = LIST_COLUMN_FLAGS;
		x.pszText = (char*)col.text.c_str();
		x.cx = col.width;
		
		send_message(hwnd, LVM_INSERTCOLUMN, idx, &x);
		return this;
	}
	int get_col_count() {
		HWND header = ListView_GetHeader(hwnd);
		return send_message(header, HDM_GETITEMCOUNT);
	}
	list_view* add_col(const lv_col& col) {
		insert_col(get_col_count(), col);
		return this;
	}
	list_view* add_col(const string& text, int width = 80) {
		insert_col(get_col_count(), lv_col(text, width));
		return this;
	}
	void full_row_select() {
		LRESULT l = send_message(hwnd, LVM_GETEXTENDEDLISTVIEWSTYLE);
		send_message(hwnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, l|LVS_EX_FULLROWSELECT);
	}
	void clear() {
		send_message(hwnd, LVM_DELETEALLITEMS);
	}

};


NS_GUI_END

