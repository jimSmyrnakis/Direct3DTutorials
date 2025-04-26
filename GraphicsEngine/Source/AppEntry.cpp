#include <Entry/Entry.hpp>

namespace JSGraphicsEngine3D {
	void Application::OnRun(void) {
		JSGraphicsEngine3D::Window* win = new JSGraphicsEngine3D::Window(300, 300);
		JSGraphicsEngine3D::Window* win2= new JSGraphicsEngine3D::Window(300, 300);
		JSGraphicsEngine3D::Button* but0 = new JSGraphicsEngine3D::Button(-50, -50, 100, 100 , win , win->GetId());

		while (true) {
			win->PollEvents();
			win2->PollEvents();
		}

		return;
	}
	// after leaving the OnRun method the OnDestroy is called a little before the Application stop executing
	int  Application::OnDestroy(void) {
		return 0;
	}
	//return the exit code
}