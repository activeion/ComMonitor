#pragma once

#include "./msg.h"
#include "../common/types.h"

#include "signal.h"

NS_GUI_BEGIN

namespace event {

	typedef gui::pos pos_t;
	typedef gui::size size_t;

	struct base {
		signal<void(const pos_t&)> move;
		signal<void(const size_t&)> size;
		signal<void(bool)> activate;
		signal<void(wnd_msg&)> paint;
		signal<void(bool)> enable;
		signal<void()> close;
		signal<void()> quit;
		signal<void(bool)> show;
		signal<void(wnd_msg&)> moving;
		signal<void(wnd_msg&)> sizing;
		signal<void(wnd_msg&)> erase_bg;
		signal<void(char)> char_;
		signal<void(wnd_msg&)> mouse_move;
		signal<void(wnd_msg&)> mouse_down;
		signal<void(wnd_msg&)> mouse_up;
		signal<void(wnd_msg&)> mouse_r_down;
		signal<void(wnd_msg&)> mouse_r_up;
		signal<void()> db_click;
		signal<void()> focus;
		signal<void()> lost_focus;

		virtual void process_msg(wnd_msg& msg) {
            switch(msg.type_) {
                case WM_MOVE:			move(pos_t(msg.lp_.loword(), msg.lp_.hiword())); break;
                case WM_SIZE:			size(size_t(msg.lp_.loword(), msg.lp_.hiword())); break;
                case WM_ACTIVATE:		activate(msg.wp_.loword() == WA_ACTIVE || msg.wp_.loword() == WA_CLICKACTIVE); break;
				case WM_PAINT:			paint(msg); break;
                case WM_ENABLE:			enable(!(msg.wp_ == 0)); break; // urgly syntax to prevent C4800 performance warning
				case WM_CLOSE:			close(); break;
				case WM_QUIT:			quit(); break;
                case WM_SHOWWINDOW:		show(!(msg.wp_ == 0)); break;
				case WM_MOVING:			moving(msg); break;
				case WM_SIZING:			sizing(msg); break;
				case WM_ERASEBKGND:		erase_bg(msg); break;
                case WM_CHAR:			char_(msg.wp_); break;
				case WM_MOUSEMOVE:		mouse_move(msg); break;
				case WM_LBUTTONDOWN:	mouse_down(msg); break;
				case WM_LBUTTONUP:		mouse_up(msg); break;
				case WM_RBUTTONDOWN:	mouse_r_down(msg); break;
				case WM_RBUTTONUP:		mouse_r_up(msg); break;
				case WM_LBUTTONDBLCLK:	db_click(); break;
				case WM_SETFOCUS:		focus(); break;
				case WM_KILLFOCUS:		lost_focus(); break;
			}
		}
	};
}

NS_GUI_END
