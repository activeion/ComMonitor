#pragma once
#include "../common/fwd.h"

NS_GUI_BEGIN

struct send_message {
	LRESULT ret_val;

	template<typename wparam_t = uint, typename lparam_t = long>
	send_message(HWND h, uint msg, wparam_t wp = 0, lparam_t lp = 0) {
		ret_val = SendMessage(h, msg, (WPARAM)wp, (LPARAM)lp);
	}
	// convert to any type
	template<typename any_t>
	operator any_t() { 
		return (any_t)ret_val;
	}
	// support syntax like if(send_message(...) == BST_CHECKED) 
	template<typename any_t>
	bool operator==(const any_t& val) {
		return val == (any_t)ret_val;
	}
};

template<typename value_t>
struct param {
	value_t value;

	param(value_t v) : value(v) {}

	template<typename _t>
	operator _t() {
		return (_t)value;
	}
	ushort hiword() {
		return HIWORD(value);
	}
	ushort loword() {
		return LOWORD(value);
	}
	// template<typename _t>
	// bool operator==(_t v) {
	bool operator==(value_t v) {
		return value == v;
	}
};

struct wnd_msg {
	// target, source
	uint type;

	param<uint> wp;
	param<long> lp;
	
	// bool stopped;
	bool killed;
	long result;

	wnd_msg(uint type, uint wp, long lp)
		: killed(false)
		// , stopped(false)
		, result(0)
		, type(type)
		, wp(wp)
		, lp(lp) {}

	void kill() {
		killed = true;
	}

};

NS_GUI_END
