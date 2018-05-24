#pragma once

#include "./layout_base.h"


NS_GUI_BEGIN
namespace layout {

	struct fit : base {
		virtual void apply(const wnd_ptr& p, const vector<wnd_ptr>& ch) { 

			rect r = p->client_rect;

			for(auto& c : ch) {
				c->rect = r;
			}
		}
	};

}

NS_GUI_END
