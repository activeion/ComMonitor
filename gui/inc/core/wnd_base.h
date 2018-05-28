#pragma once

#include "../common/fwd.h"
#include "../common/property.h"
#include "../common/initor.h"
#include "./thunk.h"
#include "./msg.h"
#include "../layout/layout_base.h"

#include "./event.h"

#include "./wnd.h"
NS_GUI_BEGIN


struct wnd32 : std::enable_shared_from_this<wnd32> {
	typedef wnd32 self_t;

    HWND hwnd_;

    wnd_ptr parent_;

    initor_ptr creator_;

    WNDPROC old_wnd_proc_;

	thunk<self_t, LRESULT(HWND,DWORD,WPARAM,LPARAM)> wnd_thunk;

	property::rw<string> text;
	property::rw<bool> visible;
	property::rw<long> style;
	property::rw<long> ex_style;
	property::rw<bool> enabled;
	property::rw<bool> fixed;
	property::rw<rect_t> rect;
	property::r<rect_t> client_rect;
	property::w<bool> capture;

	wnd32() {
		wnd_thunk.init(this, &self_t::wnd_proc);

		INIT_P_RW(self_t, visible)
		INIT_P_RW(self_t, text)
		INIT_P_RW(self_t, style)
		INIT_P_RW(self_t, ex_style)
		INIT_P_RW(self_t, enabled)
		INIT_P_RW(self_t, rect)
		INIT_P_W(self_t, capture)

		INIT_P_R(self_t, client_rect)
	}
	operator bool() {
        return !!IsWindow(hwnd_);
	}

	// create
	virtual void create() {
        initor::wnd* i = (initor::wnd*)creator_.get();

        hwnd_ = ::CreateWindowEx(
			i->ex_style(),
			class_name().c_str(),
			i->text().c_str(),
			i->style(),
			i->pos().x_,
            i->pos().y_,
			i->size().w_,
			i->size().h_,
            parent_? parent_->hwnd_ : 0,
			0, // hmenu
			0, // hinstance
			0);// create param
        assert(hwnd_ && "CreateWindowEx fail");

		intercept_wnd_proc();
        UpdateWindow(hwnd_);

	}

	void intercept_wnd_proc() {
        old_wnd_proc_ = (WNDPROC)::SetWindowLong(hwnd_, GWL_WNDPROC, wnd_thunk.addr());
	}
	virtual void process_msg(wnd_msg&) {}

	LRESULT wnd_proc(HWND hwnd, DWORD type, WPARAM wp, LPARAM lp) {
		wnd_msg msg(type, wp, lp);
		
		process_msg(msg);

		if(msg.killed_) {
			return msg.result_;
		} else {
            return ::CallWindowProc(old_wnd_proc_, hwnd, type, wp, lp);
		}
	}
	virtual string class_name() {
		throw std::runtime_error("wnd32::class_name should not be called");
	}

	// sdk api

	// visible
	bool get_visible() {
        return !!::IsWindowVisible(hwnd_);
	}
	void set_visible(bool visible) {
        ::ShowWindow(hwnd_, visible ? SW_SHOW : SW_HIDE);
	}

	// text
	string get_text() {
        int len = ::GetWindowTextLength(hwnd_) + 1;
		string t;
		t.resize(len);
        len = ::GetWindowText(hwnd_, &*t.begin(), len);
		t.resize(len);
		return t;
	}
	void set_text(const string& t) {
        ::SetWindowText(hwnd_, t.c_str());
	}

	// enabled
	bool get_enabled() {
        return !!::IsWindowEnabled(hwnd_);
	}
	void set_enabled(bool e) {
        ::EnableWindow(hwnd_, e);
	}
	// rect
	rect_t get_rect() {
		RECT r;
        ::GetWindowRect(hwnd_, &r);
		int w = r.right - r.left;
		int h = r.bottom - r.top;

        if(parent_) {
			POINT p = {r.left, r.top};
            ScreenToClient(parent_->hwnd_, &p);
			r.left = p.x;
			r.top = p.y;
		}
		return rect_t(r.left, r.top, w, h);
	}
	void set_rect(const rect_t& r) {
        ::MoveWindow(hwnd_, r.x(), r.y(), r.width(), r.height(), true);
	}
	// client_rect
	rect_t get_client_rect() {
		RECT r;
        ::GetClientRect(hwnd_, &r);
		return rect_t(r.left, r.top, r.right-r.left, r.bottom-r.top);
	}
	// style
	long get_style() {
        return ::GetWindowLong(hwnd_, GWL_STYLE);
	}
	void set_style(long st) {
        ::SetWindowLong(hwnd_, st, GWL_STYLE);
        ::SetWindowPos(hwnd_, 0,0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);
	}
	long get_ex_style() {
        return ::GetWindowLong(hwnd_, GWL_EXSTYLE);
	}
	void set_ex_style(long st) {
        ::SetWindowLong(hwnd_, st, GWL_EXSTYLE);
        ::SetWindowPos(hwnd_, 0,0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED);
	}
	
	// capture
	void set_capture(bool flag) {
		if(flag) {
            SetCapture(hwnd_);
		} else {
			ReleaseCapture();
		}
	}
	// others
	void bring_to_top() {
        ::BringWindowToTop(hwnd_);
	}
	void flash(bool invert = false) {
        ::FlashWindow(hwnd_, invert);
	}

};


template<typename event_t = event::base>
struct wnd_base : wnd32 {

	event_t event;

	virtual void process_msg(wnd_msg& msg) {
		event.process_msg(msg);
	}
};

NS_GUI_END

