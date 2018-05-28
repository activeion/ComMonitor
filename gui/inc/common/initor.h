#pragma once

#include "./fwd.h"

#include "../layout/layout_base.h"

NS_GUI_BEGIN

namespace initor {

	template<typename value_t, typename ret_t>
	struct attr {
        value_t val_;

        ret_t* ret_;
        attr() : val_(value_t()) {}

		template<typename any_t>
		void bind_owner(any_t* o) {
            ret_ = (ret_t*)o;
		}

		value_t operator()() {
            return val_;
		}
		template<typename...ctor_args_t>
		ret_t& operator()(const ctor_args_t&...arg) {
			value_t v(arg...);
            val_ = v;
            return *ret_;
		}
	};

    class abstract : non_copyable {};

	template<typename derive_t>
	struct base : abstract, std::enable_shared_from_this<derive_t> {
		attr<string, derive_t> text;
		attr<gui::pos, derive_t> pos;
		attr<gui::size, derive_t> size;
		attr<long, derive_t> style;
		attr<long, derive_t> ex_style;
		attr<shared_ptr<layout::base>, derive_t> layout;

		base() {
			text.bind_owner(this);
			pos.bind_owner(this);
			size.bind_owner(this);
			style.bind_owner(this); style(WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN);
			ex_style.bind_owner(this);
			layout.bind_owner(this);
		}
		
		derive_t& visible(bool f = true) {
			return f ? add_style(WS_VISIBLE) : remove_style(WS_VISIBLE);
		}
		derive_t& disable(bool f = true) {
			return f ? add_style(WS_DISABLED) : remove_style(WS_DISABLED);
		}
		derive_t& add_style(long st) {
			style(style() | st);
			return (derive_t&)*this;
		}
		derive_t& remove_style(long st) {
			style(style() & ~st);
			return (derive_t&)*this;
		}
	};

	struct wnd : base<wnd> {};
}// namespace initor

typedef shared_ptr<initor::abstract> initor_ptr;

template<typename wnd_t>
struct wnd_traits {
	typedef initor::wnd initor_t;
};


initor::wnd& new_() {
	return *new initor::wnd;
}

template<typename wnd_t, typename... ctor_args_t>
typename wnd_traits<wnd_t>::initor_t& new_(ctor_args_t... args) {
	return *new typename wnd_traits<wnd_t>::initor_t(args...);
}



NS_GUI_END
