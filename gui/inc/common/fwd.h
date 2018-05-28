#pragma once

#include <windows.h>
#include <assert.h>
#include <memory>
#include <functional>
#include <map>
#include <vector>
#include <stdexcept>
using namespace std;
#include "last_err.h"
#include "unsigned.h"

#include "call_before_main.h"


#define NS_GUI_BEGIN namespace gui {
#define NS_GUI_END }

NS_GUI_BEGIN

//struct default_ {
//	template<typename _t>
//	operator _t() { return _t(); }
//	operator string() { return string(); }
//};

//struct void_ {};

//struct new_t;

//template<typename t> struct tag {};

//struct window_base;

//template<typename window>
//struct wnd ;

struct wnd32;
typedef shared_ptr<wnd32> wnd_ptr;

class non_copyable {
protected:
    non_copyable() {}
    ~non_copyable() {}
private:
    non_copyable(const non_copyable&);
    non_copyable& operator=(const non_copyable&);
};


NS_GUI_END

