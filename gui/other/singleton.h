#pragma once

template <class T> 
struct singleton {
	static inline T& inst() { 
		static T instance; 
		return instance; 
    }
};

