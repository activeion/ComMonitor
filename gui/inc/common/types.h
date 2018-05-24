#pragma once
#include "fwd.h"

NS_GUI_BEGIN


struct pos {
	int x;
	int y;
	pos() : x(CW_USEDEFAULT), y(CW_USEDEFAULT) {}
	pos(int x, int y) : x(x), y(y) {}
};
struct size {
	int w;
	int h;
	size() : w(CW_USEDEFAULT), h(CW_USEDEFAULT) {}
	size(int w, int h) : w(w), h(h) {}
};

struct rect {

	typedef gui::pos pos_t;
	typedef gui::size size_t;

	pos_t pos;
	size_t size;

	rect() {}

	rect(int x, int y, int w, int h) 
		: pos(pos_t(x, y)), size(size_t(w, h)) {
	}
	int x() const {
		return pos.x;
	}
	int y() const {
		return pos.y;
	}
	int width() const {
		return size.w;
	}
	int height() const {
		return size.h;
	}
	int right() const {
		return pos.x + size.w;
	}
	int bottom() const {
		return pos.y + size.h;
	}
	rect& offset(pos_t& p) {
		return offset(p.x, p.y);
	}
	rect& offset(int dx, int dy) {
		pos.x += dx;
		pos.y += dy;
		return *this;
	}
	operator RECT() {
		RECT r;
		r.left = x(); r.right = x() + width(); 
		r.top = y(); r.bottom = y() + height();
		return r;
	}
};
typedef rect rect_t;


struct margin {
	int left;
	int right;
	int top;
	int bottom;

	margin() : left(0), right(0), top(0), bottom(0) {}
	margin(int t, int r, int b, int l)
		: left(l), right(r), top(t), bottom(b)
	{}
};

rect exclude_margin(rect& rc, margin& p) {
	rect r = rc;

	r.pos.x += p.left;
	r.pos.y += p.top;
	r.size.w -= p.left + p.right;
	r.size.h -= p.top + p.bottom;

	return r;
}
typedef margin padding;

typedef margin margin_t;
typedef padding padding_t;




NS_GUI_END
