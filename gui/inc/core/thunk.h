#pragma once

#include "../common/heap.h"

NS_GUI_BEGIN



struct thunk_base {
	// mov dword ptr [esp+4], p_this  
	// jmp WndProc
#pragma pack(push, 1)
	struct thunk_code {
		unsigned short stub1;      // lea ecx, 
		unsigned long  p_this;   // this
		unsigned char  stub2;      // mov eax,
		unsigned long  jump_proc;  // pointer to destination function
		unsigned short stub3;      // jmp eax
		void init() {
			stub1		= 0x0D8D;
			p_this		= 0;
			stub2		= 0xB8;
			jump_proc	= 0;
			stub3		= 0xE0FF;
		}
	};
#pragma pack(pop)
    thunk_code* code_;

	thunk_base() {
        code_ = heap::inst().alloc<thunk_code>();
        code_->init();
	}
	~thunk_base() {
        if(code_) {
            heap::inst().free(code_);
		}
	}
};


template<class class_t, typename fn_t>
struct thunk;

template<class class_t, typename ret_t, typename...arg_t>
struct thunk<class_t, ret_t(arg_t...)> : thunk_base {

	typedef ret_t (__stdcall *callback_type)(arg_t...);
	typedef ret_t (__thiscall class_t::*memfun_type)(arg_t...);

	void init(class_t* obj, memfun_type mem_fun) {
        code_->p_this = (unsigned long)(obj);
        code_->jump_proc = *(unsigned long*)(&mem_fun);

        ::FlushInstructionCache(GetCurrentProcess(), code_, sizeof(thunk_code));
	}

	unsigned long addr() {
        return (unsigned long)code_;
	}
	ret_t operator()(arg_t... args) {
        return ((callback_type)code_)(args...);
	}
};

NS_GUI_END
