#include "ShaderCompiler.hpp"
#include "../glad/include/glad/glad.h"
#include "../ErrorInfo.hpp"
#include <stdlib.h>
namespace JSGraphicsEngine3D {
	namespace Gui {
		uint32_t CompileShaderStage(GLenum type , const char* source) {
			uint32_t id;
			GLCALL(id = glCreateShader(type));
			GLCALL(glShaderSource(id, 1, &source, nullptr));
			GLCALL(glCompileShader(id));
			GLint status;
			GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &status));
			if (status == GL_FALSE) {
				int32_t CharBuffSize;
				GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &CharBuffSize));
				char* Message = (char*)malloc(CharBuffSize + 1);
				JS_CORE_ASSERT(Message, JS_ERROR_NO_MEMORY, "No memory !!!");
				Message[CharBuffSize] = '\0';
				GLCALL(glGetShaderInfoLog(id, CharBuffSize, nullptr, Message));
				JS_CORE_ERROR(Message, JS_ERROR_SHADER_COMPILE_FAILED);
				free(Message);
			}
			return id;
		}

		uint32_t CreateProgram(const char* vertex, const char* fragment) {
			uint32_t v = CompileShaderStage(GL_VERTEX_SHADER, vertex);
			uint32_t f = CompileShaderStage(GL_FRAGMENT_SHADER, fragment);

			uint32_t id;
			GLCALL(id = glCreateProgram());

			GLCALL(glAttachShader(id, v));
			GLCALL(glAttachShader(id, f));

			GLCALL(glLinkProgram(id));

			GLint status;
			GLCALL(glGetProgramiv(id, GL_LINK_STATUS, &status));
			if (status == GL_FALSE) {
				int32_t CharBuffSize;
				GLCALL(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &CharBuffSize));
				char* Message = (char*)malloc(CharBuffSize + 1);
				JS_CORE_ASSERT(Message, JS_ERROR_NO_MEMORY, "No memory !!!");
				Message[CharBuffSize] = '\0';
				GLCALL(glGetProgramInfoLog(id, CharBuffSize, nullptr, Message));
				JS_CORE_ERROR(Message, JS_ERROR_SHADER_LINK_FAILED);
				free(Message);
			}

			GLCALL(glDetachShader(id, v));
			GLCALL(glDetachShader(id, f));

			GLCALL(glDeleteShader(v));
			GLCALL(glDeleteShader(f));


			return id;
		}
		ShaderCompiler::ShaderCompiler(const char* vertex, const char* fragment) {
			JS_CORE_ASSERT_FATAL(vertex, JS_ERROR_NULL_PARAMETER, "vertex source is null !!!");
			JS_CORE_ASSERT_FATAL(fragment, JS_ERROR_NULL_PARAMETER, "fragment source is null !!!");

			//Create all 
			m_Program = CreateProgram(vertex, fragment);


		}

		ShaderCompiler::~ShaderCompiler(void) {
			GLCALL(glUseProgram(0));
			GLCALL(glDeleteProgram(m_Program));
		}

		void ShaderCompiler::Bind(void) const {
			GLCALL(glUseProgram(m_Program));
		}

		void ShaderCompiler::Unbind(void) const {
			GLCALL(glUseProgram(0));
		}

		uint32_t ShaderCompiler::GetProgram(void) const { return m_Program; }

		ShaderCompiler* ShaderCompiler::Create(const char* vertex, const char* fragment) {
			ShaderCompiler* ptr = new ShaderCompiler(vertex, fragment);
			JS_CORE_ASSERT_FATAL(ptr, JS_ERROR_NO_MEMORY, "No memory !!!");
			return ptr;
		}
		void ShaderCompiler::Destroy(ShaderCompiler* ptr) {
			if (ptr)
				delete ptr;
		}
	}
}