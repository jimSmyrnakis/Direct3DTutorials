#pragma once
#include "ShaderCompiler.hpp"
#include "../Uniforms/Uniform.hpp"
#include <memory>
namespace JSGraphicsEngine3D {
	namespace Gui {
		class Shader {
		public:
			Shader(const char* vsource , const char* fsource);
			Shader(const Shader&) = delete;
			Shader& operator=(const Shader&) = delete;
			~Shader(void);

		public:
			static Shader* Create(const char* vsource, const char* fsource);
			static void Destroy(Shader* ptr);

		public:
			void Bind(void) const;
			void Ubind(void) const;
			UniformsGenerator& GetUniforms(void);

		private:
			ShaderCompiler*						m_Program;
			UniformsGenerator*					m_Uniforms;
		};
	}
}