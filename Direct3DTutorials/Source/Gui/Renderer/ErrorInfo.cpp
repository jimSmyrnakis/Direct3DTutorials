#define _CRT_SECURE_NO_WARNINGS
#include "ErrorInfo.hpp"
#include "glad/include/glad/glad.h"
#include <sstream>
#include <string>
#include <string.h>

namespace JSGraphicsEngine3D {
    void GLClearErrors(void) {
        while (glGetError() != GL_NO_ERROR);
    }

    bool    GLHasError(void) {
        return  glGetError() != GL_NO_ERROR;
    }

    char* GLLogCall(const char* FunctionName, const char* SourceFile, unsigned int line) {
        GLenum error;
        bool nfound = true;
        static char Message[2048] = { 0 };
        std::stringstream ss;
        while ((error = glGetError()) != GL_NO_ERROR) {
            ss << "Error Code ( " << (int)error <<
                " ) at function \" " << FunctionName <<
                " \" , Source File \" " << SourceFile <<
                " \" at line " << line << std::endl;
            
        }
        strncpy(Message, ss.str().c_str(), 2048);
        return Message;
    }
}