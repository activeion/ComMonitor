#pragma once

#include "wnd_base.h"

NS_GUI_BEGIN


template<typename wnd_t>
struct wnd {

    wnd_ptr impl_;

	operator wnd_ptr() const {
        return impl_;
	}

	typedef typename wnd_traits<wnd_t>::initor_t initor_t;

	// for wnd<button> b;

	template<typename... ctor_args_t>
    wnd(ctor_args_t... args) : impl_(new wnd_t) {
        impl_->creator_ = initor_ptr(&new_<wnd_t>(args...));
	}

	// for wnd<button> = new_<>().xx().yy();
    wnd(initor_t& i) : impl_(new wnd_t) {
        impl_->creator_ = initor_ptr(&i);
	}
	// for wnd<button> b; b = new_<>().xx().yy();
	void operator=(initor_t& i) {
        impl_->creator_ = initor_ptr(&i);
	}

	wnd_t* operator->() {
        return (wnd_t*)impl_.get();
	}
};


NS_GUI_END
