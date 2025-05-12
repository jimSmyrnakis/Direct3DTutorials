#pragma once
#include "../glad/include/glad/glad.h"
#include "../ErrorInfo.hpp"
#include "../../../Core.hpp"
#include "../../../Extras/Mutex.hpp"

namespace JSGraphicsEngine3D {
	namespace Gui {
		class UniformsGenerator {
		
		public:
			UniformsGenerator(uint32_t program);
			~UniformsGenerator(void);

		public:

			static UniformsGenerator* Create(uint32_t program);
			static void Destroy(UniformsGenerator* ptr);

			uint32_t GetIndexByName(const char* name) const;
			// return's 0xFFFFFFFF is the name doesnt exist's
			// otherwise return's the identifier that you will 
			// use to refer on uniform with name "name" 


			void SetData(uint32_t index, void* data, uint8_t size);
			// sets new data to the specific indexed uniform
			// ofcourse first check if things are ok

			void UpdateUniforms(void);
			// Update Uniforms on the gpu side with the current cpu buffer data
			// and is thread safe


		private:
			void*		m_Buffer;// the cpu uniforms data
			uint32_t	m_Size;  // size of the buffer all together
			uint16_t    m_Count; // number of uniform constants
			uint32_t    m_Program; // the program id(Shader program)
			uint32_t*	m_Offsets; // offset of each uniform in this cpu buffer
			char**		m_Names; // the name of each uniform
			uint32_t*	m_Locations; // the locations in the program index table
			int32_t*	m_Types; // The Type of each uniform 
			Mutex*	    m_Mutex; // protects access of the uniform cpu buffer from accessing multiple thread at the same time
		};
	}
}