#pragma once
#include "../common/fwd.h"

NS_GUI_BEGIN

void msg_loop() {
	MSG msg;
	while(::GetMessage(&msg, 0, 0, 0)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}
void quit_msg_loop(int exit_code = 0) {
	::PostQuitMessage(exit_code);
}

NS_GUI_END
