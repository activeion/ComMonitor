#pragma once
#include <functional>
#include <map>
using namespace std;

template<typename x>
struct signal;

template <typename ret_t, typename... args_t>
struct signal<ret_t(args_t...)> {
	typedef int key_t; //
	typedef function<ret_t(args_t...)> func_t;

	key_t nextkey_t;
	map<key_t, func_t> connections;

	key_t operator+=(func_t f) {
		key_t k = nextkey_t++;
		connections[k] = f;
		return k;
	}

	void operator-=(key_t k){
		connections.erase(k);
	}

	void operator()(const args_t&... args) {
		for(auto conn : connections) {
			(conn.second)(args...);
		}
	}
};

