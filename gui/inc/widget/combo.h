#pragma once

#include "../core/wnd_base.h"
#include "../core/custom_msg.h"
#include "../common/common_ctrl.h"

NS_GUI_BEGIN

// http://msdn.microsoft.com/en-us/library/windows/desktop/bb775792(v=vs.85).aspx


// reflect WM_COMMAND
void reflect_combo_msg() {
	msg_reflector::reg(WM_COMMAND, [](wnd_msg& msg) {
		if(msg.wp_.hiword() == CBN_SELCHANGE) {
			send_message(msg.lp_, COMBO_SEL_CHANGE);
		}
	});
}
CALL_BEFORE_MAIN(reflect_combo_msg);


namespace event {
	struct combo : base {

		virtual void process_msg(wnd_msg& msg) {
			event::base::process_msg(msg);

			switch(msg.type_) {
				case COMBO_SEL_CHANGE: sel_change(); break;
			}
		}
		signal<void()> sel_change;
	};

}


namespace initor {
	struct combo : base<combo> {
		combo() {
			// combo's height is "the height of dropdown list"
			size(10, 200).add_style(CBS_DROPDOWNLIST | CBS_HASSTRINGS | CBS_AUTOHSCROLL | WS_VSCROLL | WS_HSCROLL);
		}
	};
}

struct combo;

template<>
struct wnd_traits<combo> {
	typedef initor::combo initor_t;
};

struct combo : widget_base<event::combo> {
	typedef widget_base<event::combo> super_t;

	property::r<int> item_count;
	property::rw<int> sel;
	property::r<string, int> item_text;

	combo() {
		INIT_P_R(combo, item_count);
		INIT_P_RW(combo, sel);
		bind_property(item_text, bind(&combo::get_item_text, this, placeholders::_1));
	}
	string class_name() {
		return "ComboBox";
	}

	combo& add_item() { 
		return *this;
	}
	template<typename first_t, typename...rest_t>
	combo& add_item(const first_t& first, const rest_t&... rest) { 
        send_message(hwnd_, CB_ADDSTRING, 0, first.c_str());
		return add_item(rest...);
	}
	
	int get_item_count() const { 
        return send_message(hwnd_, CB_GETCOUNT);
    }
    int get_sel() const { 
        return send_message(hwnd_, CB_GETCURSEL);
    }
    void set_sel(const int& val) {
        send_message(hwnd_, CB_SETCURSEL, val);
    }
    string get_item_text(int val) const {
        int len = send_message(hwnd_, CB_GETLBTEXTLEN, val);
        string result;
        result.resize(len + 10 /*just in case*/);
        int new_size = send_message(hwnd_, CB_GETLBTEXT, val, &*result.begin() );
        result.resize( new_size >= 0 ? new_size : 0);
        return result;
    }

};


NS_GUI_END
