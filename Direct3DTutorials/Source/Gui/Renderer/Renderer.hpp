#pragma once
#include "../../Core.hpp"
#include "../../FrameWork/Window.hpp"
#include "ErrorInfo.hpp"
#include "Drawable.hpp"
#include <vector>
#include "../../Extras/Mutex.hpp"
namespace JSGraphicsEngine3D {

	namespace Gui {
		
		class GuiRenderer {

		public:
			GuiRenderer(std::shared_ptr<Window>	& win);
			~GuiRenderer(void);

			GuiRenderer(const GuiRenderer& cp) = delete;
			GuiRenderer& operator=(const GuiRenderer& cp) = delete;


		public:

			void Viewport(float x, float y, float width, float height);
			void ClearBuffer(float rgba[4]);
			void SwapBuffers(void) const;

		public: // these methods will be called from different thread , so thread safety must implement
			void StartFrame(void) ; 
			void SubmitDrawable(Drawable* drw) ;
			void EndFrame(void) ;

			void Run(void);


		public:
			static GuiRenderer* Create(std::shared_ptr<Window>& win);
			static void Destroy(GuiRenderer* ptr);

		private:
			HGLRC		m_GLContext;
			HDC			m_DeviceContext;
			std::shared_ptr<Window>		m_Window;
			struct Viewport {
				float x;
				float y;
				float w;
				float h;
			};
			struct Viewport	m_Viewport;
			std::vector<Drawable*>	m_Draws; // must be accessed from one thread at the time
			Mutex*					m_Mutex;
			bool					m_RenderFinish;

		};

	};
}