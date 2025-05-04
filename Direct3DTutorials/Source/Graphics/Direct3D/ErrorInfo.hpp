#pragma once
#include "Direct3D11Inc.h"

namespace JSGraphicsEngine3D {
	void InitD3DDebug(ID3D11Device* device);
	void ClearD3DErrors(void);
	bool D3DHasNewError(void);
	char* GetLastD3DErrorMessageA(void);
}

#define JS_CHECKD3DH(function) ClearD3DErrors(); if (FAILED((function))) { JS_CORE_ASSERT(0 , JS_ERROR_DIRECT3D_ERROR , GetLastD3DErrorMessageA() ); } 
#define JS_CHECKD3D(function) ClearD3DErrors(); (function); if (D3DHasNewError()) { JS_CORE_ASSERT(0 , JS_ERROR_DIRECT3D_ERROR , GetLastD3DErrorMessageA() ); }