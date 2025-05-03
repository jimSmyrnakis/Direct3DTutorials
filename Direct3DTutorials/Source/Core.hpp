#pragma once

#include "JSWin.hpp"
#include <comdef.h>
#include "Error/Error.hpp"
#include "Error/EWCodes.hpp"
#include <stdio.h>
#include <string>

#include <stdint.h>
#include <stddef.h>

namespace JSGraphicsEngine3D {
	char* formatString(const char* fmt, ...);
}
#define JS_CORE_ASSERT(cond , errorCode , fmt , ... ) {\
	if (!(cond)) { \
		const char* message = JSGraphicsEngine3D::formatString(fmt , __VA_ARGS__ );\
		JS_CORE_ERROR(errorCode , message);\
	}\
}
#define JS_APP_ASSERT(cond , errorCode ,fmt , ... ) {\
	if (!(cond)) { \
		const char* message = JSGraphicsEngine3D::formatString(fmt , __VA_ARGS__ );\
		JS_APP_ERROR(errorCode , message);\
	}\
}

#ifdef __JSDEBUG__
	#define JS_CORE_WINDOWS_ASSERT(cond  ) JS_CORE_ASSERT(cond , GetLastError() , "Windows Error ==> %s",  GetErrorCodeWindowsMessage(GetLastError()))

	#define DIRECT3D_ASSERT(x)                 \
		{                                                   \
			HRESULT hr__ = (x);                             \
			if (FAILED(hr__)) {                             \
				JSGraphicsEngine3D::PrintHR(hr__);          \
				js_break(1); \
			}                                               \
		}
#else 
	#define JS_CORE_WINDOWS_ASSERT(cond  ) (cond)
	#define DIRECT3D_ASSERT(x, msg) (x)
#endif
namespace JSGraphicsEngine3D {
	inline void PrintHR(HRESULT hr) {
		_com_error err(hr);
		std::wstring fullMsg = std::wstring(L"[D3D Error] ") +
			err.ErrorMessage();
		MessageBoxW(nullptr, fullMsg.c_str(), L"Direct3D Error", MB_ICONERROR);
		return;
	}
}



