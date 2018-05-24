#pragma once

#include "./layout_base.h"

#include "../common/types.h"


NS_GUI_BEGIN

namespace layout {

	struct grid : base {

		virtual void apply(const wnd_ptr& p, const vector<wnd_ptr>& ch) {
		}
	};
}

NS_GUI_END
