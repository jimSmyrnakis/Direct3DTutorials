#pragma once
#include "../../Core.hpp"
#include "Shader/Shader.hpp"
#include "Uniforms/Uniform.hpp"
#include "Mesh2D/Mesh2D.hpp"
#include <memory>
namespace JSGraphicsEngine3D {
	namespace Gui {
		class Drawable {
		public:
			Drawable(std::shared_ptr<Mesh2D>& mesh , std::shared_ptr<Shader>& shader);
			~Drawable(void) = default;


			Drawable& operator=(const Drawable&) = delete;
			Drawable(const Drawable&) = delete;

		public:
			static Drawable* Create(std::shared_ptr<Mesh2D>& mesh, std::shared_ptr<Shader>& shader);
			static void Destroy(Drawable* ptr);

		public:

			void Bind(void) const;
			void Unbind(void) const;

			std::shared_ptr<Mesh2D> GetMesh(void) const;
			std::shared_ptr<Shader> GetShader(void) const;
		private:
			std::shared_ptr<Mesh2D>		m_Mesh;
			std::shared_ptr<Shader>		m_Shader;

		};
	}
}