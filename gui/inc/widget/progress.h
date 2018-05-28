#pragma once

#include "../core/wnd_base.h"
#include "../common/common_ctrl.h"

NS_GUI_BEGIN


namespace initor {
	struct progress : base<progress> {
		progress() {
			add_style(PBS_SMOOTH).size(20, 10);
		}
	};
}

struct progress;

template<>
struct wnd_traits<progress> {
	typedef initor::progress initor_t;
};

// button
struct progress : wnd_base<> {
	typedef wnd_base<> super_t;

	property::rw<int> min;
	property::rw<int> max;
	property::rw<int> pos;
	property::w<int> step;
	property::w<int> bar_color;
	property::w<int> bg_color;

	progress() {
		INIT_P_RW(progress, min);
		INIT_P_RW(progress, max);
		INIT_P_RW(progress, pos);
		INIT_P_W(progress, step);
		INIT_P_W(progress, bar_color);
		INIT_P_W(progress, bg_color);
		
	}
	string class_name() {
		return "msctls_progress32";
	}
	void range(int min_, int max_) {
		send_message(hwnd_, PBM_SETRANGE32, min_, max_);
	}

	int get_min() const { 
		PBRANGE r;
		send_message(hwnd_, PBM_GETRANGE, true, &r);
		return r.iLow;
	}
	void set_min(const int & val) {
		range( val, get_max());
	}
	int get_max() const { 
		PBRANGE r;
		send_message(hwnd_, PBM_GETRANGE, false, &r);
		return r.iHigh;
	}
	void set_max(const int & val) {
		range(get_min(), val);
	}
	int get_pos() const { 
		return send_message(hwnd_, PBM_GETPOS);
	}
	void set_pos(const int& val) {
		send_message(hwnd_, PBM_SETPOS, val);
	}
	void set_step(const int& val) {
		send_message(hwnd_, PBM_SETSTEP, val);
	}
	void set_bar_color(const int& col) {
		send_message(hwnd_, PBM_SETBARCOLOR, 0, col);
	}
	void set_bg_color(const int& val) {
		send_message(hwnd_, PBM_SETBKCOLOR, 0, val);
	}

	void step_it() {
		send_message(hwnd_, PBM_STEPIT);
	}
};


NS_GUI_END
