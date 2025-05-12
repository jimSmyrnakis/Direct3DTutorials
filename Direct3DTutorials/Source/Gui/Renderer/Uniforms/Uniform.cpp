#include "Uniform.hpp"
#include "../glad//include/glad/glad.h"
#include <memory.h>
#ifdef __JSDEBUG__
#include <string>
#include <sstream>
#endif
namespace JSGraphicsEngine3D {
	namespace Gui {
		
		UniformsGenerator::UniformsGenerator(uint32_t program) {
			// initiallize members
			m_Buffer = nullptr;
			m_Size = 0;
			m_Count = 0;
			m_Program = 0;
			m_Locations = nullptr;
			m_Names = nullptr;
			m_Offsets = nullptr;
			m_Types = nullptr;
			
			// Test if the program exists otherwise fatal error
			JS_CORE_ASSERT_FATAL(glIsProgram(program) == GL_TRUE, JS_ERROR_BAD_GL_PROGRAM, "This program doesn't exist !!!");
			// 
			m_Program = program;

			//take the number of total uniforms in the program
			GLCALL( glGetProgramiv(m_Program, GL_ACTIVE_UNIFORMS, (int32_t*) & m_Count) );
			
			//from this number create all the meta data as types , names , etc.
			m_Types = new int32_t[m_Count];
			m_Offsets = new uint32_t[m_Count];
			m_Names = new char* [m_Count];
			m_Locations = new uint32_t[m_Count];
			// metadata now have all the desired space but first check each one of them
			JS_CORE_ASSERT_FATAL(m_Types, JS_ERROR_NO_MEMORY, "No memory !!!");
			JS_CORE_ASSERT_FATAL(m_Offsets, JS_ERROR_NO_MEMORY, "No memory !!!");
			JS_CORE_ASSERT_FATAL(m_Names, JS_ERROR_NO_MEMORY, "No memory !!!");
			JS_CORE_ASSERT_FATAL(m_Locations, JS_ERROR_NO_MEMORY, "No memory !!!");

			//now find all the names but first find out the biggest uniforms name
			GLint maxNameLength;
			GLCALL(glGetProgramiv(m_Program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength));
			//create each name with that size
			m_Size = 0;
			for (uint16_t i = 0; i < m_Count; i++) {
				m_Names[i] = new char[maxNameLength + 1];
				JS_CORE_ASSERT_FATAL(m_Names[i], JS_ERROR_NO_MEMORY, "No memory !!!");
				(m_Names[i])[maxNameLength] = '\0'; // for security reasons
				// nowtake the name of it and all metadata
				// offsets
				m_Offsets[i] = m_Size;
				int32_t usize; // size in bytes of the uniform
				GLenum GLUType;
				
				GLCALL(glGetActiveUniform(m_Program, i, maxNameLength, nullptr, &usize, &GLUType, m_Names[i]));
				//caculate size's 
				m_Size += usize;
				//take the type
				m_Types[i] = GLUType;
				//find the location on the index table
				GLCALL( m_Locations[i] = glGetUniformLocation(m_Program, m_Names[i]));
			}

			// now we have the total size create the buffer
			m_Buffer = malloc(m_Size);
			JS_CORE_ASSERT_FATAL(m_Buffer, JS_ERROR_NO_MEMORY, "No memory !!!");

#ifdef __JSDEBUG__
			// for print out all information needed
			std::stringstream ss;
			ss << "Uniform Count : " << m_Count << std::endl;
			ss << "Uniform Buffer Size : " << m_Size << std::endl;
			ss << "Uniform Names { " << std::endl;
			for (uint16_t i = 0; i < m_Count; i++) {
				ss << "Name[" << i << "] : " << m_Names[i] << std::endl;
			}
			ss << "}" << std::endl;
			ss << "Uniform Offsets { " << std::endl;
			for (uint16_t i = 0; i < m_Count; i++) {
				ss << "Offset[" << i << "] : " << m_Offsets[i] << std::endl;
			}
			ss << "}" << std::endl;

			JS_CORE_INFO(ss.str().c_str());
#endif
			m_Mutex = Mutex::Create();

		}
		UniformsGenerator::~UniformsGenerator(void) {
			// delete the variables
			if (m_Types)
				delete[] m_Types;

			if (m_Offsets)
				delete[] m_Offsets;

			if (m_Locations)
				delete[] m_Locations;

			if (m_Names) {
				for (uint16_t i = 0;i < m_Count; i++) {
					delete[] m_Names[i];
				}
				delete[] m_Names;
			}

			if (m_Buffer)
				free(m_Buffer);

			Mutex::Destroy(m_Mutex);
		}

		static void UpdateUniform(uint32_t loc, void* buffer, uint32_t offset, int32_t type) {
			JS_CORE_ASSERT(buffer, JS_ERROR_NULL_PARAMETER, "buffer is nullptr :( !!!");
			
			switch (type) {
			case GL_FLOAT:		GLCALL(glUniform1f(loc, *((float*)buffer + offset))); break;
			case GL_FLOAT_VEC2: GLCALL(glUniform2fv(loc, 1 , ((float*)buffer + offset))); break;
			case GL_FLOAT_VEC3: GLCALL(glUniform3fv(loc, 1, ((float*)buffer + offset))); break;
			case GL_FLOAT_VEC4: GLCALL(glUniform4fv(loc, 1, ((float*)buffer + offset))); break;
			case GL_FLOAT_MAT3: GLCALL(glUniformMatrix3fv(loc, 1, GL_TRUE, ((float*)buffer + offset))); break;
			case GL_FLOAT_MAT4: GLCALL(glUniformMatrix4fv(loc, 1, GL_TRUE, ((float*)buffer + offset))); break;

			
			}
		}

		void UniformsGenerator::UpdateUniforms(void) {
			//for each type update the uniform data
			m_Mutex->Lock();
			for (uint16_t i = 0; i < m_Count; i++) 
				UpdateUniform(m_Locations[i], m_Buffer, m_Offsets[i], m_Types[i]);
			m_Mutex->Unlock();

		}

		uint32_t UniformsGenerator::GetIndexByName(const char* name) const {

			for (uint16_t i = 0; i < m_Count; i++) {
				if (strcmp(m_Names[i], name) == 0)
					return i;
			}

			return 0xFFFFFFFF;
		}

		void UniformsGenerator::SetData(uint32_t index, void* data, uint8_t size) {
			m_Mutex->Lock();
			JS_CORE_ASSERT(index < m_Count, JS_ERROR_OUT_OF_BOUNDS, "Out of Bounds ");
			uint32_t isize = m_Offsets[index];
			if (index == (m_Count - 1))
				isize = m_Size - isize;
			else
				isize = m_Offsets[index + 1] - isize;
			JS_CORE_ASSERT(isize >= size, JS_ERROR_BAD_SIZE, "Size of data bigger of that of the uniform space !!!");
			JS_CORE_ASSERT(memcpy((void*)((char*)m_Buffer + m_Offsets[index]), data, size), JS_ERROR_NULL_PTR, "memcpy failed !!!");

			m_Mutex->Unlock();

		}

		UniformsGenerator* UniformsGenerator::Create(uint32_t program) {
			UniformsGenerator* ptr = new UniformsGenerator(program);
			JS_CORE_ASSERT_FATAL(ptr, JS_ERROR_NO_MEMORY, "No memory !!!");
			return ptr;
		}
		void UniformsGenerator::Destroy(UniformsGenerator* ptr) {
			if (ptr)
				delete ptr;
		}
	}
}