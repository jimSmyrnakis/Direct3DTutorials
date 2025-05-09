#pragma once
#include "../glad/include/glad/glad.h"
#include "../ErrorInfo.hpp"
#include "../../../Core.hpp"
namespace JSGraphicsEngine3D {
	namespace Gui {
		class UniformsGenerator {
		public:
			enum class Type {
				F32,
				VEC2F32,
				VEC3F32,
				VEC4F32,
				MAT4F32,

				F16,
				VEC2F16,
				VEC3F16,
				VEC4F16,
				MAT4F16

				

			};
		public:
			UniformsGenerator(uint32_t program);
			~UniformsGenerator(void);

			void UpdateUniforms(void);

		private:
			void*		m_Buffer;// the cpu uniforms data
			uint32_t	m_Size;  // size of the buffer all together
			uint16_t    m_Count; // number of uniform constants
			uint32_t    m_Program; // the program id(Shader program)
			uint32_t*	m_Offsets; // offset of each uniform in this cpu buffer
			char**		m_Names; // the name of each uniform
			uint32_t*	m_Locations; // the locations in the program index table
			int32_t*	m_Types; // The Type of each uniform 
		};
	}
}