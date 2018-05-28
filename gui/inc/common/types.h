#pragma once
#include "fwd.h"

NS_GUI_BEGIN


struct pos {
    int x_;
    int y_;
    pos() : x_(CW_USEDEFAULT), y_(CW_USEDEFAULT) {}
    pos(int x, int y) : x_(x), y_(y) {}
};
struct size {
    int w_;
    int h_;
    size() : w_(CW_USEDEFAULT), h_(CW_USEDEFAULT) {}
    size(int w, int h) : w_(w), h_(h) {}
};

struct rect {

	typedef gui::pos pos_t;
	typedef gui::size size_t;

    pos_t pos_;
    size_t size_;

	rect() {}

	rect(int x, int y, int w, int h) 
        : pos_(pos_t(x, y)), size_(size_t(w, h)) {
	}
	int x() const {
        return pos_.x_;
	}
	int y() const {
        return pos_.y_;
	}
	int width() const {
        return size_.w_;
	}
	int height() const {
        return size_.h_;
	}
	int right() const {
        return pos_.x_ + size_.w_;
	}
	int bottom() const {
        return pos_.y_ + size_.h_;
	}
	rect& offset(pos_t& p) {
        return offset(p.x_, p.y_);
	}
	rect& offset(int dx, int dy) {
        pos_.x_ += dx;
        pos_.y_ += dy;
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

    r.pos_.x_ += p.left;
    r.pos_.y_ += p.top;
    r.size_.w_ -= p.left + p.right;
    r.size_.h_ -= p.top + p.bottom;

	return r;
}
typedef margin padding;

typedef margin margin_t;
typedef padding padding_t;




NS_GUI_END
