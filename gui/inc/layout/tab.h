#pragma once

#include "./layout_base.h"

NS_GUI_BEGIN
namespace layout {

	struct tab : base {


		wnd_ptr activated;

		void activate(wnd_ptr& c) {
			if(activated == c) return;
			if(activated) activated->visible = false;
			c->visible = true;
			activated = c;
		}
		virtual void apply(const wnd_ptr& p, const vector<wnd_ptr>& ch) {

			rect r = p->client_rect;
			r.pos_.y_ += 24; // tab header buttons

			for(auto& c : ch) {
				c->rect = r;
			}
		}
	};


}

NS_GUI_END
