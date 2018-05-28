#pragma once

#include "../core/wnd_base.h"

NS_GUI_BEGIN

namespace type {
	namespace label {
		enum label_align {
			left = SS_LEFT,
			right = SS_RIGHT,
			center = SS_CENTER,
			vcenter = SS_CENTERIMAGE,
			lcenter = left | vcenter,
			rcenter = right | vcenter
		};
		enum seperator_type {
			horiz = SS_ETCHEDHORZ,
			vert = SS_ETCHEDVERT
		};
	}
}

namespace initor {
	struct label : base<label> {
		attr<HBITMAP, label> bitmap;
		label() {
			bitmap.bind_owner(this);
			text_align(type::label::vcenter | type::label::center);
		}
		label(const string& _text, int al = type::label::vcenter | type::label::center) {
			bitmap.bind_owner(this);
			text_align(al).text(_text);
		}
		label& text_align(int al) {
			add_style(al);
			return *this;
		}
		label& seperator(type::label::seperator_type sp) {
			add_style(sp);
			return *this;
		}
	};
}

struct label;

template<>
struct wnd_traits<label> {
	typedef initor::label initor_t;
};

struct label : widget_base<> {
	typedef widget_base<> super_t;

	// label() {}
	// label(const string& text) {
	// }
	string class_name() {
		return "STATIC";
	}
	void create() {
        initor::label* i = (initor::label*)creator_.get();

		super_t::create();

		if(i->bitmap()) {
			set_bitmap(i->bitmap());
		}
	}
	void set_bitmap(HBITMAP hbmp, bool delete_old = true) {
        HBITMAP old = send_message(hwnd_, STM_GETIMAGE, IMAGE_BITMAP);
		style = style | (SS_BITMAP | SS_CENTERIMAGE);
        send_message(hwnd_, STM_SETIMAGE, IMAGE_BITMAP, hbmp);
		if(delete_old && old) {
			::DeleteObject(old);
		}
	}
};

#define h_seperator wnd<label>(new_<label>().seperator(type::label::horiz))
#define v_seperator wnd<label>(new_<label>().seperator(type::label::vert))


NS_GUI_END
