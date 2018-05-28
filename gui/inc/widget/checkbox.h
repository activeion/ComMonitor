#pragma once

#include "./button.h"

NS_GUI_BEGIN

// reflect WM_COMMAND
// #define WM_CHECK WM_USER+1

// void reflect_button_msg() {
// 	msg_reflector::reg(WM_COMMAND, [](wnd_msg& msg) {
// 		if(msg.wp == BN_CLICKED) {
// 			send_message(msg.lp, WM_CLICK);
// 		}
// 	});
// }
// call_before_main(reflect_button_msg);


// events
// namespace event {
// 	struct button : event::base {
// 
// 		virtual void process_msg(wnd_msg& msg) {
// 			event::base::process_msg(msg);
// 
// 			switch(msg.type) {
// 				case WM_CLICK: click(); break;
// 			}
// 		}
// 		event_handler<> click;
// 	};
// }

namespace initor {
	struct checkbox : base<checkbox> {
		checkbox() {
			add_style(BS_AUTOCHECKBOX);
		}
	};
}
struct checkbox;

template<>
struct wnd_traits<checkbox> {
	typedef initor::checkbox initor_t;
};

// button
struct checkbox : button {
	typedef button super_t;

	property::rw<bool> checked;

	checkbox() {
		INIT_P_RW(checkbox, checked);
	}

	bool get_checked() {
		return send_message(hwnd_, BM_GETCHECK) == BST_CHECKED;
	}
	void set_checked(bool check) {
		send_message(hwnd_, BM_SETCHECK, check);

	}
};


NS_GUI_END
