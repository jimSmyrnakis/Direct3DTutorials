#include "Shader.hpp"

namespace JSGraphicsEngine3D {
	namespace Gui {
		Shader::Shader(const char* vsource, const char* fsource) {
			m_Program = ShaderCompiler::Create(vsource , fsource);
			m_Uniforms = UniformsGenerator::Create(m_Program->GetProgram());

		}
		Shader::~Shader(void) {
			UniformsGenerator::Destroy(m_Uniforms);
			ShaderCompiler::Destroy(m_Program);
		}

		void Shader::Bind(void) const {
			m_Uniforms->UpdateUniforms();
			m_Program->Bind();
		}
		void Shader::Ubind(void) const {
			m_Program->Unbind();
		}
		UniformsGenerator& Shader::GetUniforms(void) {
			return *m_Uniforms;
		}

		Shader* Shader::Create(const char* vsource, const char* fsource) {
			Shader* ptr = new Shader(vsource, fsource);
			JS_CORE_ASSERT_FATAL(ptr, JS_ERROR_NO_MEMORY, "no Memory !!!");
			return ptr;
		}
		void Shader::Destroy(Shader* ptr) {
			if (ptr)
				delete ptr;
		}

	}
}