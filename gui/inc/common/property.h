#pragma once

#include "fwd.h"
#include <functional>
#include <string>
using namespace std;

NS_GUI_BEGIN

namespace property {

	// helpers only used for property with args
	template<typename r_t, typename value_t, typename...arg_t>
	struct r_helper {
		r_t* _r;
		function<value_t()> getter;

		r_helper(r_t* _r, arg_t...arg) : _r(_r), getter(bind(_r->getter, arg...)) {
		}
		operator value_t() {
			return getter();
		}
	};
	template<typename w_t, typename value_t, typename...arg_t>
	struct w_helper {
		w_t* _w;
		function<void(const value_t&)> setter;

		w_helper(w_t* _w, arg_t...arg) : _w(_w), setter(bind(_w->setter, arg..., placeholders::_1)) {
		}
		void operator=(const value_t& new_val) {
			setter(new_val);
		}
	};
	template<typename rw_t, typename value_t, typename...arg_t>
	struct rw_helper : r_helper<rw_t, value_t, arg_t...>, w_helper<rw_t, value_t, arg_t...> {
		rw_helper(rw_t* _rw, arg_t...arg) 
			: r_helper<rw_t, value_t, arg_t...>(_rw, arg...)
			, w_helper<rw_t, value_t, arg_t...>(_rw, arg...) {
		}
		using w_helper<rw_t, value_t, arg_t...>::operator=;
	};


	template<typename value_t, typename...arg_t>
	struct r {
		typedef r<value_t, arg_t...> self_t;
		function<value_t(arg_t...)> getter;

		r_helper<self_t, value_t, arg_t...> operator()(arg_t...arg) {
			return r_helper<self_t, value_t, arg_t...>(this, arg...);
		}
	};
	template<typename value_t>
	struct r<value_t> {
		function<value_t()> getter;
		operator value_t() {
			return getter();
		}
	};

	template<typename value_t, typename...arg_t>
	struct w {
		typedef w<value_t, arg_t...> self_t;
		function<void(arg_t...arg, const value_t&)> setter;
		w_helper<self_t, value_t, arg_t...> operator()(arg_t...arg) {
			return w_helper<self_t, value_t, arg_t...>(this, arg...);
		}
	};
	template<typename value_t>
	struct w<value_t> {
		function<void(const value_t&)> setter;
		void operator=(const value_t& new_val) {
			setter(new_val);
		}
	};

	template<typename value_t, typename...arg_t>
	struct rw : r<value_t, arg_t...>, w<value_t, arg_t...> {
		typedef rw<value_t, arg_t...> self_t;
   		rw_helper<self_t, value_t, arg_t...> operator()(arg_t...arg) {
			return rw_helper<self_t, value_t, arg_t...>(this, arg...);
		}
	};
	template<typename value_t>
	struct rw<value_t> : r<value_t>, w<value_t> {
		using w<value_t>::operator=;
	};



	// bind_property
	template<typename value_t, typename...arg_t, typename getter_t> // r
	void bind_property(r<value_t, arg_t...>& p, getter_t getter) {
		p.getter = getter;
	}
	template<typename value_t, typename...arg_t, typename setter_t>
	void bind_property(w<value_t, arg_t...>& p, setter_t setter) { // w
		p.setter = setter;
	}
	template<typename value_t, typename...arg_t, typename getter_t, typename setter_t> // rw
	void bind_property(rw<value_t, arg_t...>& p, getter_t getter, setter_t setter) {
		p.getter = getter;
		p.setter = setter;
	}
	
#define INIT_P_RW(cls, attr) \
		bind_property(attr, bind(&cls::get_##attr, this), bind(&cls::set_##attr, this, placeholders::_1));
#define INIT_P_R(cls, attr) \
		bind_property(attr, bind(&cls::get_##attr, this));
#define INIT_P_W(cls, attr) \
		bind_property(attr, bind(&cls::set_##attr, this, placeholders::_1));
}

NS_GUI_END
