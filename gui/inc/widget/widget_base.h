#pragma once

#include "../core/wnd_base.h"

NS_GUI_BEGIN

HMODULE GetCurrentModuleHandle() {
    HMODULE hMod = NULL;
    GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
          reinterpret_cast<char*>(&GetCurrentModuleHandle),
          &hMod);
     return hMod;
}

void create_widget_base_class() {
	WNDCLASS cls;
	ZeroMemory(&cls, sizeof(cls));

	cls.lpfnWndProc      = DefWindowProc;
	cls.lpszClassName    = "widget_base";
	cls.hInstance        = GetCurrentModuleHandle();

	cls.style            = CS_VREDRAW | CS_HREDRAW;
	cls.hbrBackground    = HBRUSH(COLOR_WINDOW);
	// cls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	cls.hCursor          = LoadCursor(NULL, IDC_ARROW);
	
	if(::RegisterClass(&cls) == 0) {
		throw std::runtime_error(last_err("RegisterClass"));
	}
}
CALL_BEFORE_MAIN(create_widget_base_class);

template<typename event_t = event::base>
struct widget_base : wnd_base<event_t> {
	string class_name() {
		return "widget_base";
	}
};


NS_GUI_END


