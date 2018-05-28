#pragma once

#include "panel.h"

NS_GUI_BEGIN

namespace initor {
	struct window : base<window> {
		window() {
			add_style(WS_SYSMENU | WS_MINIMIZEBOX).remove_style(WS_CHILD);
		}
		window& resizable(bool f = true) {
			return f ? add_style(WS_THICKFRAME) : remove_style(WS_THICKFRAME);
		}
	};
}
struct window;

template<>
struct wnd_traits<window> {
	typedef initor::window initor_t;
};

struct window : panel {
	typedef panel super_t;

	virtual void process_msg(wnd_msg& msg) {
		if(msg.type_ == WM_DESTROY) {
			PostQuitMessage(0);
		}
		panel::process_msg(msg);
	}
};


NS_GUI_END
