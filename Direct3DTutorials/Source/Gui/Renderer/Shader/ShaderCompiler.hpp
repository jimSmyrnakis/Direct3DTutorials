#pragma once
#include "../../../Core.hpp"

namespace JSGraphicsEngine3D {
	namespace Gui {
		class ShaderCompiler {

		private:
			ShaderCompiler(const char* vertex, const char* fragment);
			~ShaderCompiler(void);

			ShaderCompiler(const ShaderCompiler&) = delete;
			ShaderCompiler& operator=(const ShaderCompiler&) = delete;

		public:
			static ShaderCompiler* Create(const char* vertex, const char* fragment);
			static void Destroy(ShaderCompiler* ptr);

		public:
			void Bind(void) const;
			void Unbind(void) const;

			uint32_t GetProgram(void) const;

		private:
			uint32_t    m_Program;
		};
	}
}