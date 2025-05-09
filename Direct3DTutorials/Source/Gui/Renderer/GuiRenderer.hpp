#pragma once
#include "../../Core.hpp"
#include "../../FrameWork/Window.hpp"
#include "ErrorInfo.hpp"
namespace JSGraphicsEngine3D {

	namespace Gui {
		class GuiRenderer {
		private:
			GuiRenderer(Window* win);
			~GuiRenderer(void);

			GuiRenderer(const GuiRenderer& cp) = delete;
			GuiRenderer& operator=(const GuiRenderer& cp) = delete;


		public:

			void ClearBuffer(float rgba[4]);
			void SwapBuffers(void) const;


		public:
			static GuiRenderer* Create(Window* win);
			static void Destroy(GuiRenderer* ptr);

		private:
			HGLRC		m_GLContext;
			HDC			m_DeviceContext;
			Window* m_Window;


		};

	};
}