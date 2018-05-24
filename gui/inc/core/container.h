#pragma once

#include "wnd_base.h"
#include "msg_reflection.h"

#include "../layout/layout_base.h"

NS_GUI_BEGIN


template<typename event_t = event::base>
struct container : wnd_base<event_t> {
	typedef wnd_base<event_t> super_t;

	typedef vector<wnd_ptr> children_t;

	children_t children;

	shared_ptr<layout::base> layout;

	virtual void process_msg(wnd_msg& msg) {
		// reflect
		msg_reflector::process_msg(msg);

		if(msg.type == WM_SIZE) {
			this->do_layout();
		}
		super_t::process_msg(msg);
	}

	wnd_ptr add_child() { return this->shared_from_this(); }

	template<typename... rest_t>
	wnd_ptr add_child(wnd_ptr first, rest_t...rest) {
		children.push_back(first);
		first->parent = this->shared_from_this();

		return add_child(rest...);
	}
	void do_layout() {
		if(layout) {
			layout->apply(this->shared_from_this(), children);
		}
	}
	virtual void create() {
		initor::wnd* i = (initor::wnd*)this->creator.get();
		layout = i->layout();
		super_t::create();
		create_children();
		do_layout();
	}
	void create_children() {
		for(auto c : children) {
			c->create();
		}
	}

};

NS_GUI_END
