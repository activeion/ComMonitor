#pragma once
#include "fwd.h"

NS_GUI_BEGIN

namespace cursor {

	enum type {
		app_starting, arrow, cross, hand, help, input, icon, no, size, 
		sizeall, size_nesw, size_ns, size_nwse, size_we, up_arrow, wait
	};

	char* styles[] = {
		IDC_APPSTARTING, IDC_ARROW, IDC_CROSS, IDC_HAND, IDC_HELP, IDC_IBEAM, IDC_ICON, IDC_NO, IDC_SIZE, 
		IDC_SIZEALL, IDC_SIZENESW, IDC_SIZENS, IDC_SIZENWSE, IDC_SIZEWE, IDC_UPARROW, IDC_WAIT 
	};

	void set(type t) {
		char* s = styles[t];
		HCURSOR h = LoadCursor(NULL, s);
		SetCursor(h);
	}
}

NS_GUI_END

