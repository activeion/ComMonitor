#pragma once

#include "../common/fwd.h"


NS_GUI_BEGIN

struct msg_reflector {
	typedef function<void(wnd_msg&)> handler_t;

	static map<ulong, vector<handler_t> > handlers;

	static void reg(ulong id, function<void(wnd_msg&)> handler) {
		handlers[id].push_back(handler);
	}

	static void process_msg(wnd_msg& msg) {
		if(handlers.find(msg.type) != handlers.end()) {
			for(auto& h : handlers[msg.type])
				h(msg);
			msg.kill();
		}
	}
};
map<ulong, vector<msg_reflector::handler_t>> msg_reflector::handlers;


NS_GUI_END
