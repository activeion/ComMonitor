// MinGW doesn't provide <mutex> ...
#pragma once
namespace std {

struct once_flag {
	bool f;
	once_flag(bool f = false) : f(f) {}
};
template<typename fn_t, typename... args_t>
void call_once(once_flag& flag, fn_t fn, args_t... args) {
	if(!flag.f) {
		flag.f = true;
		fn(args...);
	}
}

}

