#include "Drawable.hpp"

namespace JSGraphicsEngine3D {
	namespace Gui {
		Drawable::Drawable(std::shared_ptr<Mesh2D>& mesh, std::shared_ptr<Shader>& shader) {
			m_Mesh = mesh;
			m_Shader = shader;
		}

		Drawable* Drawable::Create(std::shared_ptr<Mesh2D>& mesh, std::shared_ptr<Shader>& shader) {
			Drawable* ptr = new Drawable(mesh, shader);
			JS_CORE_ASSERT_FATAL(ptr, JS_ERROR_NO_MEMORY, "No memory !!!");
			return ptr;
		}
		void Drawable::Destroy(Drawable* ptr) {
			if (ptr)
				delete ptr;
		}

		void Drawable::Bind(void) const {
			m_Shader->Bind();
			m_Mesh->Bind();
		}
		void Drawable::Unbind(void) const {
			m_Shader->Ubind();
			m_Mesh->Bind();
		}
		std::shared_ptr<Mesh2D> Drawable::GetMesh(void) const { return m_Mesh; }
		std::shared_ptr<Shader> Drawable::GetShader(void) const { return m_Shader; }
	}
}