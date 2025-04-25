#pragma once

#include "JSWin.hpp"
#include "Error/Error.hpp"
#include "Error/EWCodes.hpp"
#include <stdio.h>

#include <stdint.h>
#include <stddef.h>

namespace JSGraphicsEngine3D {
	char* formatString(const char* fmt, ...);
}
#define JS_CORE_ASSERT(cond , errorCode , fmt , ... ) {\
	if (!(cond)) { \
		const char* message = formatString(fmt , __VA_ARGS__ );\
		JS_CORE_ERROR(errorCode , message);\
	}\
}
#define JS_APP_ASSERT(cond , errorCode ,fmt , ... ) {\
	if (!(cond)) { \
		const char* message = formatString(fmt , __VA_ARGS__ );\
		JS_APP_ERROR(errorCode , message);\
	}\
}

#define JS_CORE_WINDOWS_ASSERT(cond  ) JS_CORE_ASSERT(cond , GetLastError() , "Windows Error ==> %s",  GetErrorCodeWindowsMessage(GetLastError()))



//must find way to print error messages :) TODO
