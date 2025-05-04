#include <Entry/Entry.hpp>
#include <Graphics/Direct3D/Direct3DGraphics.hpp>
#include <Graphics/OpenGL/OpenGLGraphics.hpp>
namespace JSGraphicsEngine3D {
	void Application::OnRun(void) {
		JSGraphicsEngine3D::Window* win = new JSGraphicsEngine3D::Window(300, 300);
		JSGraphicsEngine3D::Window* win2= new JSGraphicsEngine3D::Window(300, 300);
		JSGraphicsEngine3D::Button* but0 = new JSGraphicsEngine3D::Button(-50, -50, 100, 100 , win , win->GetId());
		JSGraphicsEngine3D::Direct3DGraphics* graphics1 = Direct3DGraphics::Create(win);
		JSGraphicsEngine3D::OpenGLGraphics* graphics2 = OpenGLGraphics::Create(win2);
		uint8_t clr = 0;
		bool increment = true;
		while (true) {
			float arr[4] = { clr / 255.0f, 0.0f, clr / 255.0f, 1.0f };
			float arr2[4] = { clr / 255.0f, 1.0f, clr / 255.0f, 1.0f };
			win->PollEvents();
			win2->PollEvents();
			graphics1->ClearBuffer(arr);
			graphics2->ClearBuffer(arr2);
			graphics1->DrawTriangle();
			2;
			graphics1->SwapBuffers();
			graphics2->SwapBuffers();
			clr = clr + ( (increment) ? +1 : -1) ;
			if (clr == 255) {
				increment = false;
				
			}
				
			if (clr == 0) {
				increment = true;
			}
		}

		return;
	}
	// after leaving the OnRun method the OnDestroy is called a little before the Application stop executing
	int  Application::OnDestroy(void) {
		return 0;
	}
	//return the exit code
}