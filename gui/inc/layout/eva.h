#pragma once

#include "./layout_base.h"

#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

NS_GUI_BEGIN
NS_GUI_LAYOUT_BEGIN


struct eva : base {
	typedef eva self_t;

	enum direction { HORIZ, VERT };

	// cell
	struct cell {
		virtual bool extendable(direction dir) = 0;
		virtual bool is_wnd() { return false; };
	};
	typedef vector<cell*> cells;
	typedef vector<cells> matrix;

	struct empty : cell { // ' '
		virtual bool extendable(direction dir) { return false; }
	};
	struct horiz : cell { // '-'
		virtual bool extendable(direction dir) { return dir == HORIZ; }
	};
	struct vert : cell { // '|'
		virtual bool extendable(direction dir) { return dir == VERT; }
	};
	struct eva_wnd : cell { // wnd_ptr
		wnd_ptr ptr;
		eva_wnd(const wnd_ptr& ptr) : ptr(ptr) {}
		virtual bool extendable(direction) { return false; }
		virtual bool is_wnd() { return true; };
	};

	// header
	struct header {
		virtual int calc_length(int total_length) = 0;
		virtual char type() { return 0; }
	};
	typedef vector<header*> headers;

	struct number : header { // 100
		int num;
		number(int n) : num(n) {}
		int calc_length(int) { return num; }
	};
	struct d : header {
		direction dir;
		matrix& matx;
		int index;

		d(int index, matrix& matx, direction dir) : 
			index(index), matx(matx), dir(dir) {}

		int calc_length(int) {
			int _max = 0;

			if(dir == HORIZ) {
				for_each(matx.begin(), matx.end(), [&_max, this](cells& row) {
					cell* c = row[index];
					if(c->is_wnd()) {
						rect_t rc = static_cast<eva_wnd*>(c)->ptr->rect;
						_max = max<int>(_max, rc.width());
					}
				});
				return _max;

			} else {
				cells& row = matx[index];
				for_each(row.begin(), row.end(), [&_max](cell* c) {
					if(c->is_wnd()) {
						rect_t rc = static_cast<eva_wnd*>(c)->ptr->rect;
						_max = max<int>(_max, rc.height());
					}
				});
				return _max;
			}
		}
	};
	struct x : header { // 'x', 0.5f, 1.0
		float coeff;
		headers& hdr;
		x(float coeff, headers& hdr) : coeff(coeff), hdr(hdr) {}
		virtual char type() { return 'x'; }
		int calc_length(int total_length) {
			int rest = accumulate(
				hdr.begin(),
				hdr.end(),
				0,
				[total_length](int total, header* h) {
					return h->type() == 'x' ? total : (total + h->calc_length(total_length));
				}
			);
			return (total_length - rest) * coeff;
		}
	};



	// create_header
	header* create_header(const wnd_ptr&, direction) {
		assert(false && "cannot create eva header with wnd_ptr");
		return NULL;
	}

	header* create_header(const float& f, direction dir) {
		return new x(f, (dir==HORIZ) ? col : row);
	}
	header* create_header(const char& c, direction dir) {
		switch(c) {
			case 'x':
				return new x(1.0, (dir==HORIZ) ? col : row);
			case 'd':
				{
					int index = (dir==HORIZ) ? col.size() : row.size();
					return new d(index, matx, dir);
				}
		}
		assert(false && "creating unknown eva header");
		return NULL;
	}
	header* create_header(const int& n, direction) {
		return new number(n);
	}

	// create_cell
	cell* create_cell(const float& w) {
		return NULL;
	}
	cell* create_cell(const int& w) {
		return NULL;
	}
	cell* create_cell(const wnd_ptr& w) {
		return new eva_wnd(w);
	}
	cell* create_cell(const char& c) {
		switch(c) {
			case ' ': return new empty;
			case '-': return new horiz;
			case '|': return new vert;
		}
		assert(false && "create NULL cell in eva layout");
		return NULL;
	}



	matrix matx;
	headers row;
	headers col;

	int row_count;
	int col_count;

	eva(int row_count, int col_count) : 
		row_count(row_count), col_count(col_count) 
	{}

	~eva() {
		for(auto* r : row) delete r;
		for(auto* c : col) delete c;

		for(auto& _r : matx) 
			for(auto* cell : _r) 
				delete cell;
	}
	
	virtual void apply(const wnd_ptr& p, const vector<wnd_ptr>& ch) { 
		rect_t rc = p->client_rect;
		rc = exclude_margin(rc, this->padding);

		for(int row_num=0; row_num<row_count; row_num++) {
			for(int col_num=0; col_num<col_count; col_num++) {
				cell* c = matx[row_num][col_num];
				if(c->is_wnd()) {

					rect_t r = calc_wnd_rect(row_num, col_num, rc);
					static_cast<eva_wnd*>(c)->ptr->rect = r;
				}
			}
		}
	}
	rect_t calc_wnd_rect(int row_num, int col_num, rect_t& total_rect) {

		// horizontal
		int start_col = col_num, end_col = col_num;

        //根据EvaLayout的定义, 不“向左看”
        //while(start_col > 0 && matx[row_num][start_col-1]->extendable(HORIZ)) start_col--;
        //根据EvaLayout的定义, wnd只“向右扩展，向右看”
        while(end_col < col_count-1 && matx[row_num][end_col+1]->extendable(HORIZ)) end_col++;

		int x = start_col == 0 ? 0 : calc_length(0, start_col-1, HORIZ, total_rect.width());
		int w = calc_length(start_col, end_col, HORIZ, total_rect.width());

		// vertical
		int start_row = row_num, end_row = row_num;

        //根据EvaLayout的定义, wnd只“向下扩展，向下看”
        while(start_row > 0 && matx[start_row-1][col_num]->extendable(VERT)) start_row--;
        //根据EvaLayout的定义, 不“向上看”
        //while(end_row < row_count-1 && matx[end_row+1][col_num]->extendable(VERT)) end_row++;

		int y = start_row == 0 ? 0 : calc_length(0, start_row-1, VERT, total_rect.height());
		int h = calc_length(start_row, end_row, VERT, total_rect.height());

		return rect_t(x, y, w, h).offset(total_rect.pos);
	}

	int calc_length(int from_index, int to_index, direction dir, int total_length) {// total_length used for 'x'
		headers& hdr = (dir == HORIZ) ? col : row;
		// total_length -= to_index - from_index;
		return accumulate(hdr.begin() + from_index,
						  hdr.begin() + to_index + 1,
						  0,
						  [this, total_length](int total, header* hdr) {
						  	return total + hdr->calc_length(total_length);
						  });
	}

	template<typename _t>
	self_t& operator|(const _t& t) {
		if(col.size() < col_count) { // first line is column
			header* h = create_header(t, HORIZ);
			col.push_back(h);
		} else {
			if(row.size() == 0 || matx[matx.size()-1].size() == col_count) {
				row.push_back(create_header(t, VERT));
				matx.push_back(cells()); // add new row
			} else {
				matx[matx.size()-1].push_back(create_cell(t));
			}
		}
		return *this;
	}
};


NS_GUI_LAYOUT_END
NS_GUI_END

