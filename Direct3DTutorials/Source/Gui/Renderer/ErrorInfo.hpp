#pragma once

#include "../../Core.hpp"
#include "../../Error/Error.hpp"

namespace JSGraphicsEngine3D {
    void    GLClearErrors(void);
    bool    GLHasError(void);
    char*    GLLogCall(const char* FunctionName, const char* SourceFile, unsigned int line);

	
}

#define GLCALL(function) \
        GLClearErrors();\
        (function);\
        if (GLHasError())\
        JS_CORE_ASSERT(0 , JS_ERROR_OPENGL_ERROR ,  GLLogCall(#function , __FILE__ , __LINE__ ));

