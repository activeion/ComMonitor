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
    wnd<button> btn2("button2");
    wnd<button> btn3("button3");
    wnd<button> btn4("button4");
    wnd<button> btn5("button5");
    wnd<button> btn6("button6");

    //EvaLayout 官方示例
    //https://www.codeproject.com/Articles/13891/EvaLayout-Lay-it-be
    auto& grid = *new layout::eva(5,5);//增加专门的3个像素的两列网格来增加间隔
    grid.padding = padding(10,10,5,5);
    grid.hgap=5;grid.vgap=5;
    grid|  75 | 3  |   'x'   | 3 |  'd'  |
    'd'| btn1 | ' '| btn5    |'-'|  '-'  |
    'd'| btn2 | ' '|  '|'    |' '|  ' '  |
    'd'| btn3 | ' '|  '|'    |' '|  ' '  |
    'x'| ' '  | ' '|  '|'    |' '|  ' '  |
    'd'| btn6 | '-'|  '-'    |' '|  btn4 ;
    wnd<window> w1 = new_<window>()
            .text("layout test")
            .resizable(true)
            .size(300,200)
            .layout(&grid);
    w1->add_child(btn1, btn2, btn3, btn4, btn5, btn6);

    //最简化版
    /*
    auto& grid = *new layout::eva(1,4);
    grid.padding = padding(10,10,5,5);
    grid.hgap=4;grid.vgap=4;//没有起作用, 需要增加专门的3个像素的网格来增加间隔
    grid|  75   |   'x'   | 3 |   'd'  |
    'd'| btn6   |  '-'    |' '|   btn4 ;
    wnd<window> w1 = new_<window>()
            .text("layout test")
            .resizable(true)
            .size(300,200)
            .layout(&grid);
    w1->add_child(btn4, btn6);
    */


    w1->create();
    msg_loop();
}
