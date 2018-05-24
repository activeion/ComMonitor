#pragma once

#include "../common/fwd.h"
#include "../common/types.h"

#define NS_GUI_LAYOUT_BEGIN namespace layout {
#define NS_GUI_LAYOUT_END }

NS_GUI_BEGIN
NS_GUI_LAYOUT_BEGIN

struct base {
	margin_t margin;
	padding_t padding;

	int hgap;
	int vgap;

	base() : hgap(4), vgap(4) {}
	virtual void apply(const wnd_ptr& parent, const vector<wnd_ptr>& children) = 0;
};


NS_GUI_LAYOUT_END
NS_GUI_END
