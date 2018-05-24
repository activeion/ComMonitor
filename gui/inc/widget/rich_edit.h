#pragma once

#include "widget_base.h"
#include "../common/common_ctrl.h"
#include <richedit.h>

#include "edit.h"

NS_GUI_BEGIN

void init_rich_control() {
	LoadLibrary("riched20.dll");
	// comm_ctrl::init(ICC_RICHEDIT_CLASSES);
};

CALL_BEFORE_MAIN(init_rich_control)

namespace initor {
	struct rich_edit : edit_base<rich_edit> {};
}


struct rich_edit;
template<>
struct wnd_traits<rich_edit> {
	typedef initor::rich_edit initor_t;
};

struct rich_edit : edit {
	// typedef edit super_t;

	string class_name() {
		return RICHEDIT_CLASS;
	}
};


NS_GUI_END

