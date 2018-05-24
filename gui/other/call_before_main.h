#pragma once

#define CALL_BEFORE_MAIN( name ) \
	struct initer ## name { \
		initer ## name () { name (); } \
	} s_init ## name ; 

