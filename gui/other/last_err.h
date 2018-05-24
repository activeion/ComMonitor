#pragma once
#include <windows.h>
#include <string>
#include <sstream>

std::string last_err(const std::string s = "") {
	char* err_s;
	::FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_ARGUMENT_ARRAY,
		0,
		GetLastError(),
		// MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
		(LPSTR)&err_s,
		0,
		0 
	);
	std::stringstream ss;
	ss << s << " " << GetLastError() << ": " << err_s ;
	::LocalFree(err_s);
	return ss.str();
}
