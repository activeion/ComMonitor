#pragma once

#include "../common/fwd.h"


NS_GUI_BEGIN

struct msg_reflector {
	typedef function<void(wnd_msg&)> handler_t;

    static map<ulong, vector<handler_t> > handlers_;

	static void reg(ulong id, function<void(wnd_msg&)> handler) {
        handlers_[id].push_back(handler);
	}

	static void process_msg(wnd_msg& msg) {
        if(handlers_.find(msg.type_) != handlers_.end()) {
            for(auto& h : handlers_[msg.type_])
				h(msg);
			msg.kill();
		}
	}
};
map<ulong, vector<msg_reflector::handler_t>> msg_reflector::handlers_;


NS_GUI_END
