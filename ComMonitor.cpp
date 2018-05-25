#include <iostream>
#include <thread>

#include "gui/inc/gui.h"
#include "gui/inc/widget/window.h"
#include "gui/inc/widget/tab.h"
#include "gui/inc/widget/combo.h"
#include "gui/inc/widget/label.h"
#include "gui/inc/widget/button.h"
#include "gui/inc/widget/checkbox.h"
#include "gui/inc/widget/list_view.h"
#include "gui/inc/widget/edit.h"
#include "gui/inc/widget/rich_edit.h"
#include "gui/inc/widget/progress.h"
#include "gui/inc/layout/fit.h"
#include "gui/inc/layout/split.h"
#include "gui/inc/layout/grid.h"
#include "gui/inc/layout/eva.h"
using namespace gui;

int main()
{
    // ChildWin for MainWindow
    wnd<label> lbl_name("name");
    wnd<label> lbl_psw("password");
    wnd<edit> edt_psw = new_<edit>()
            .password_type(true)
            .size(200, 100);
    wnd<button> btn_ok("ok");
    wnd<button> btn_cancel("cancel");
    wnd<progress> prog = new_<progress>()
            .size(100, 10);

    // layout for MainWindow
    auto& lay = *new layout::eva(5, 5);
    lay.padding = padding(10, 10, 10, 10);
    lay/**/ | 80        | 'x'   | 'd'  | 10  | 'd' |
        'd' | lbl_name  |edt_psw| '-'  | '-' | '-' |
        3   | ' '       | ' '   | ' '  | ' ' | ' ' |
        'd' | lbl_psw   | prog  | '-'  | '-' | '-' |
        'x' | ' '       | ' '   | ' '  | ' ' | ' ' |
        'd' | ' '       | ' '   |btn_ok| ' ' | btn_cancel ;
    wnd<window> w = new_<window>()
            .text("login")
            .size(300, 200)
            .resizable(true)
            .layout(&lay);
    w->add_child(lbl_name, edt_psw,
            lbl_psw, prog,
            btn_ok, btn_cancel);

    // Event for ChildWind and MainWindow
    btn_ok->event.click += [&]() { prog->step_it(); };
    btn_cancel->event.click += [&]() {
        prog->pos = 0;
        prog->visible = false;
    };
    auto caret = []() {
        POINT p;
        GetCaretPos(&p);
        std::cout << "caret:" << p.x << std::endl;
    };
    edt_psw->event.mouse_down += [&](wnd_msg&) {
        std::cout << "mosue down" << std::endl;
        caret();
    };
    w->event.move += [](const pos& p) {
        std::cout << "window moved to ("
                  << p.x << "| " << p.y << ")"
                  << std::endl;
    };

    // Create and Loop
    w->create();
    msg_loop();
}

/****************************
int main() {
	// wnd<label> lbl_name("name"), lbl_psw("password");
	wnd<edit> edt_psw = new_<edit>().password_type(true).size(200, 100);
	// wnd<combo> cmb_psw;
	// wnd<button> btn_ok("ok"), btn_cancel("cancel");
// 
	// wnd<progress> prog = new_<progress>().size(100, 10);
// 
	// btn_ok->event.click += [&]() { prog->step_it(); };
	// btn_cancel->event.click += [&]() { prog->pos = 0; prog->visible = false;};
// 
	// auto& lay = *new layout::eva(5, 5);
	// lay.padding = padding(10, 10, 10, 10);
// 
	// lay | 80       | 'x'      | 'd'    | 10  | 'd'        |
	// 'd' | lbl_name | edt_psw | '-'    | '-' | '-'        |
	//  3  | ' '      | ' '      | ' '    | ' ' | ' '        |
	// 'd' | lbl_psw  | prog     | '-'    | '-' | '-'        |
	// 'x' | ' '      | ' '      | ' '    | ' ' | ' '        |
	// 'd' | ' '      | ' '      | btn_ok | ' ' | btn_cancel ;


	wnd<window> w = new_<window>().text("login").size(300, 60).resizable(true)
									// .layout(&lay)
									.layout(new layout::fit)
									;

	// wnd<edit> editor_name = new_<edit>().text("admin");
	// wnd<edit> editor_psw = new_<edit>().text("123456").password_type(true);

	// wnd<button> btn_login("login");
	// wnd<button> btn_cancel = new_<button>().text("cancel");
	// btn_login->event.click += [&]() {
	// 	string psw = editor_psw->text;
	// 	cout << (psw.compare("123456") ? "correct" : "wrong password") << endl;
	// };
	// btn_cancel->event.click += [&]() { quit_msg_loop(0); };

	// wnd<list_view> lv;
	// wnd<edit> edt;

	auto caret = []() {
		POINT p;
		GetCaretPos(&p);
		
		cout << "caret:" << p.x << endl;
	};
	edt_psw->event.mouse_down += [&](wnd_msg&) { cout << "mosue down" << endl; caret(); };
	// wnd<button> b1("b1");
	// wnd<button> b2("b2");
    w->event.move += [](const pos& p) { cout << "window moved to (" << p.x << "| " << p.y << ")" << endl; };
	w->add_child(
				 edt_psw
		// lv
		// lbl_name, edt_psw,
		// lbl_psw, prog,
		// btn_ok, btn_cancel

		// wnd<tab>()->add_child(
			// wnd<label>("name:")| 		editor_name|
			// wnd<label>("password:")| 	editor_psw|
					// btn_login| btn_cancel
		// )
	);
	w->create();

	// lv->event.db_click += [&]() {
	// 	int row = lv->sel;
	// 	cout << row << endl;
	// };

	// prog->range(0, 100);
	// prog->step = 5;

	// lv->add_col("aaa")->add_col("bbb");
	// lv->add_row(3);
	// lv->item(0, 0) = lv_item("x");
	// lv->item(1, 0) = lv_item("y");
	// lv->item(2, 0) = lv_item("z");
	// lv->item(1, 1) = lv_item("a");
	// lv->sel = 1;
	msg_loop();

}
***********/
