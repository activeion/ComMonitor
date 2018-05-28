#pragma once

#include "./widget_base.h"
#include "../core/container.h"

#include "../layout/split.h"
#include "../common/cursor.h"

NS_GUI_BEGIN

namespace initor {
	struct splitter : base<splitter> {
		splitter() {
			size(3, 3);//->ex_style(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
		}
	};
}
struct hsplitter;
struct vsplitter;

template<>
struct wnd_traits<hsplitter> {
	typedef initor::splitter initor_t;
};
template<>
struct wnd_traits<vsplitter> {
	typedef initor::splitter initor_t;
};


struct splitter : widget_base<> {
	typedef widget_base super_t;
	typedef splitter self_t;

	bool is_dragging;
	int click_offset;

	splitter() : is_dragging(false), click_offset(0) {
		event.mouse_down += [this](wnd_msg& msg) { start_drag(msg); };
		event.mouse_up += [this](wnd_msg&) { end_drag(); }; 
		event.mouse_move += [this](wnd_msg&) { set_mouse_type(); };
		event.mouse_move += [this](wnd_msg& msg) { on_move(msg); };

		event.erase_bg += [this](wnd_msg& msg) {
			HDC hdc = msg.wp_;
			
			rect_t r = calculate_draw_size();

			RECT rc = {0,0,10000,10000};
			FillRect(hdc, &rc, (HBRUSH) (COLOR_WINDOW));

			rc = r;
			DrawFocusRect(hdc, &rc);

			msg.result_ = 1; // return non-zero for WM_ERASEBKGND
			msg.kill(); // skip default_wnd_proc
		};
	}

	void start_drag(wnd_msg& msg) {
		click_offset = get_click_offset(msg);
		is_dragging = true;
		capture = true; // SetCapture
	}
	void end_drag() {
		is_dragging = false;
		capture = false; // ReleaseCapture
	}
	virtual void set_mouse_type() =0;
	virtual int get_click_offset(wnd_msg& msg) = 0;
	virtual void on_move(wnd_msg& msg) = 0;
	virtual rect_t calculate_draw_size() = 0;

};
struct vsplitter : splitter {
	virtual void set_mouse_type() {
		cursor::set(cursor::type::size_we);
	}
	virtual int get_click_offset(wnd_msg& msg) {
		return msg.lp_.loword();
	}
	virtual rect_t calculate_draw_size() {
		rect_t _r = this->rect;
		return rect_t(_r.width()/2,
					  _r.height()/2 - 10,
					  2,
					  20);
	}
	virtual void on_move(wnd_msg& msg) {

		if ((msg.wp_ == MK_LBUTTON) && is_dragging) {

			short offset = msg.lp_.loword();

			rect_t rc = this->rect;

			this->rect = rc.offset(offset - click_offset, 0);

			static_cast<container<>*>(parent_.get())->do_layout();
		}
	}
};
struct hsplitter : splitter {
	virtual void set_mouse_type() {
		cursor::set(cursor::type::size_ns);
	}
	virtual int get_click_offset(wnd_msg& msg) {
		return msg.lp_.hiword();
	}
	virtual rect_t calculate_draw_size() {
		rect_t _r = this->rect;
		return rect_t(_r.width()/2 - 10,
					  _r.height()/2,
					  20,
					  2);
	}
	virtual void on_move(wnd_msg& msg) {

		if ((msg.wp_ == MK_LBUTTON) && is_dragging) {

			short offset = msg.lp_.hiword();

			rect_t rc = this->rect;

			this->rect = rc.offset(0, offset - click_offset);

			static_cast<container<>*>(parent_.get())->do_layout();
		}
	}
};

#define h_splitter(offset) wnd<hsplitter>(new_<hsplitter>().pos(0, offset))
#define v_splitter(offset) wnd<vsplitter>(new_<vsplitter>().pos(offset, 0))


NS_GUI_END

