#pragma once

#include "JSWin.hpp"

#define JSASSERT(cond ) 

#if defined(__JSDEBUG__) 
	#define JSASSERT(cond) {if (!(cond)) { __debugbreak(); }}
#endif

#include <stdint.h>
#include <stddef.h>

//must find way to print error messages :) TODO
