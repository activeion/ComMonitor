#pragma once

#include "./layout_base.h"

#include "../common/types.h"


NS_GUI_BEGIN

namespace layout {

	struct grid : base {
		int row;
		int col;

		int _gap;

		vector<rect> cells;

		grid(int col, int row) : row(row), col(col) {}

		grid& gap(int p) {
			_gap = p;
			return *this;
		}
		grid& add_cell(rect& r) {
			cells.push_back(r);
			return *this;
		}
		virtual void apply(const wnd_ptr& p, const vector<wnd_ptr>& ch) { 

			rect rc_p = p->client_rect;
			rc_p = rc_p;

			int cell_w = (rc_p.width() - (col-1)*_gap) / col;
			int cell_h = (rc_p.height() - (row-1)*_gap) / row;

			for(int i=0, len = min(cells.size(), ch.size()); i<len; i++) {
				rect& c = cells[i];
				const wnd_ptr& w = ch[i];

				rect r(c.x()*(cell_w+_gap) + rc_p.x(), 
					   c.y()*(cell_h+_gap) + rc_p.y(), 
					   c.width()*cell_w + (c.width()-1) * _gap, 
					   c.height()*cell_h + (c.height()-1) * _gap );

				w->rect = r;
			}
		}
	};
}

NS_GUI_END
