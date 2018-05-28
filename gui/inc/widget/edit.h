#pragma once

#include "widget_base.h"

NS_GUI_BEGIN

namespace initor {
	// derived by rich_edit
	template<typename derive_t>
	struct edit_base : base<derive_t> {
		attr<bool, derive_t> read_only;
		attr<bool, derive_t> password_type;
		attr<char, derive_t> password_char;

		edit_base() {
			read_only.bind_owner(this);
			password_type.bind_owner(this);
			password_char.bind_owner(this);

			this->add_style(WS_BORDER).size(100, 22);
		}
	};

	struct edit : edit_base<edit> {};
}

struct edit;

template<>
struct wnd_traits<edit> {
	typedef initor::edit initor_t;
};

struct edit : widget_base<event::base> {
	typedef widget_base<event::base> super_t;

	property::rw<bool> read_only;
	property::rw<char> password_char;

	string class_name() {
		return "edit";
	}
	edit() {
		INIT_P_RW(edit, read_only)
		INIT_P_RW(edit, password_char)
	}
	virtual void create() {
		initor::edit* i = (initor::edit*)creator_.get();

		i->password_type() ? i->add_style(ES_PASSWORD) : i->remove_style(ES_PASSWORD);

		super_t::create();

		read_only = i->read_only();
		if(i->password_char()) {
			password_char = i->password_char();
		}
	}

    bool get_read_only() { 
		return (GetWindowLong(hwnd_, GWL_STYLE) & ES_READONLY) != 0;
    }
    void set_read_only(const bool& val) {
		send_message(hwnd_, EM_SETREADONLY, val);
    }

    char get_password_char() { 
		return send_message(hwnd_, EM_GETPASSWORDCHAR);
    }
    void set_password_char(const char& val) {
		send_message(hwnd_, EM_SETPASSWORDCHAR, val);
    }

	
	
};


NS_GUI_END

