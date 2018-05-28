#pragma once
#include "./fwd.h"

#include <commctrl.h>
class comm_ctrl {
	static void init(long type) {
		INITCOMMONCONTROLSEX icx;
		icx.dwSize = sizeof(icx);
		icx.dwICC = type;
		InitCommonControlsEx(&icx);		
	}
};
