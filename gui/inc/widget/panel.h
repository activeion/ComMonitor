#pragma once

#include "../core/container.h"
#include "widget_base.h"

NS_GUI_BEGIN


struct panel : container<event::base> {
	string class_name() {
		return "widget_base";
	}
};


NS_GUI_END

