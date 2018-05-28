#include "fwd.h"

#include "singleton.h"

NS_GUI_BEGIN

#ifndef HEAP_CREATE_ENABLE_EXECUTE
	#define HEAP_CREATE_ENABLE_EXECUTE 0x00040000
#endif

struct heap : singleton<heap> {
    HANDLE h_;
	heap() {
        h_ = ::HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0, 0);
        if(!h_) {
			throw last_err("HeapCreate");
		}
	}

	void* alloc(int size) {
        void* memory = ::HeapAlloc(h_, HEAP_ZERO_MEMORY, size);
		if(!memory) {
			throw last_err("HeapAlloc");
		}
		return memory;
	}
	template <typename _t>
	_t* alloc() {
		return (_t*)alloc(sizeof(_t));
	}

	template <typename _t>
	bool free(_t* addr) {
        return !!::HeapFree(h_, 0, (void*)addr);
	}
};

NS_GUI_END
