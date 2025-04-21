#pragma once

#include "JSWin.hpp"



#if defined(__JSDEBUG__) 
	#define JSASSERT(cond) {if (!(cond)) { __debugbreak(); }}
#else
	#define JSASSERT(cond ) 
#endif

#include <stdint.h>
#include <stddef.h>

//must find way to print error messages :) TODO
