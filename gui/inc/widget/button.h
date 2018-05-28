#pragma once

#include "../core/wnd_base.h"
#include "../core/custom_msg.h"

NS_GUI_BEGIN

// reflect WM_COMMAND
void reflect_button_msg() {
	msg_reflector::reg(WM_COMMAND, [](wnd_msg& msg) {
		if(msg.wp_ == BN_CLICKED) {
			send_message(msg.lp_, BTN_CLICK);
		}
	});
}
CALL_BEFORE_MAIN(reflect_button_msg);

namespace initor {
	struct button : base<button> {
		// attr<bool, button> auto_size;
		// use BCM_GETIDEALSIZE message

		button() {
			size(70, 24);
		}
		button(const string& txt) {
			text(txt).size(70, 24);
		}
	};
}

struct button;

template<>
struct wnd_traits<button> {
	typedef initor::button initor_t;
};

// events
namespace event {
	struct button : base {

		virtual void process_msg(wnd_msg& msg) {
			event::base::process_msg(msg);

			switch(msg.type_) {
				case BTN_CLICK: click(); break;
			}
		}
		signal<void()> click;
	};
}


// button
struct button : wnd_base<event::button> {
	string class_name() {
		return "button";
	}
	void click() {
        send_message(hwnd_, BTN_CLICK);
	}
};


NS_GUI_END
