#pragma once

#include "./layout_base.h"
#include "../widget/splitter.h"
#include "../core/wnd.h"

#include "mutex.h"

NS_GUI_BEGIN
namespace layout {

	struct hsplit : base {

		wnd<hsplitter> sp;
		std::once_flag init_flag;

		hsplit(int offset) {
			sp = new_<hsplitter>().pos(0, offset).add_style(WS_CHILD);
		}

		void create_splitter_once(const wnd_ptr& p) {
			std::call_once(init_flag, [&p, this]() {
				sp->parent_ = p;
				sp->create();
			});
		}

		virtual void apply(const wnd_ptr& p, const vector<wnd_ptr>& ch) { 

			create_splitter_once(p);

			rect rc = p->client_rect;

			int W = rc.width();
			int H = rc.height();

			rect rsp = sp->rect;

			// previous
			rect r0(0, 0, W, rsp.y());
			ch[0]->rect = r0;

			// splitter
			sp->rect = rect(0, rsp.y(), W, rsp.height());
				
			// next
			int y = rsp.y()+rsp.height();
			rect r1(0, y, W, H-y);
			ch[1]->rect = r1;
		}
	};


	struct vsplit : base {
		wnd<vsplitter> sp;
		std::once_flag init_flag;

		vsplit(int offset) {
			sp = new_<vsplitter>().pos(offset, 0);
		}

		void create_splitter_once(wnd_ptr& p) {
			std::call_once(init_flag, [&p, this]() {
				sp->parent_ = p;
				sp->create();
			});
		}
		
		virtual void apply(wnd_ptr& p, vector<wnd_ptr>& ch) { 
			create_splitter_once(p);

			rect rc = p->client_rect;

			int W = rc.width();
			int H = rc.height();

			rect rsp = sp->rect;

			// previous
			rect r0(0, 0, rsp.x(), H);
			ch[0]->rect = r0;

			// splitter
			sp->rect = rect(rsp.x(), 0, rsp.width(), H);
				
			// next
			int x = rsp.x()+rsp.width();
			rect r1(x, 0, W-x, H);
			ch[1]->rect = r1;
		}
	};

}

NS_GUI_END

