#pragma once
#include "../../Core.hpp"
#include "../../FrameWork/Window.hpp"
namespace JSGraphicsEngine3D {
	class OpenGLGraphics {
	private:
		OpenGLGraphics(Window* win);
		~OpenGLGraphics(void);

		OpenGLGraphics(const OpenGLGraphics& cp) = delete;
		OpenGLGraphics& operator=(const OpenGLGraphics& cp) = delete;


	public:

		void ClearBuffer(float rgba[4]);
		void SwapBuffers(void) const;

		void DrawTriangle(void);

	public:
		static OpenGLGraphics* Create(Window* win);
		static void Destroy(OpenGLGraphics* ptr);

	private:
		HGLRC		m_GLContext;
		HDC			m_DeviceContext;
		Window*		m_Window;


	};
}