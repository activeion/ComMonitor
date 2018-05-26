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

#include <vector>
#include <string>
#include "CSerial/SerialWnd.h"

int main()
{
    wnd<button> btn1("button1");
    btn1->event.click +=[](){std::cout << "clicked" << std::endl;};
    wnd<button> btn2("button2");

    auto& grid = *new layout::eva(1,3);
    grid.padding = padding(10,10,5,5);
    grid|  75   |   'x'   |   'd'  |
    'd'| btn1   |  '-'    |   btn2 ;
    wnd<window> w1 = new_<window>()
            .text("layout test")
            .size(300,200)
            .resizable(true)
            .layout(&grid);
    w1->add_child(btn1, btn2);
    w1->create();
    //message loop
    msg_loop();
}
