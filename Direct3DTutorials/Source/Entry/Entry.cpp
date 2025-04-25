#include "../FrameWork/Window.hpp"
#include "../FrameWork/EventLisceners/Example/Button.hpp"

TRACKMOUSEEVENT tme = { 0 };
int CALLBACK WinMain( // CALLBACK is stdcall function conversion , is important for window methods calls 
	_In_ HINSTANCE hInstance, // the current instance of the application window 
	_In_ HINSTANCE hPrevInstance, // not used any more
	_In_ LPSTR lpCmdLine, // a string to the command line argument (all in one and not seperate)
	_In_ int  nCmdhow // how the window must be show when the program starts
) {
		JSGraphicsEngine3D::Window* win= new JSGraphicsEngine3D::Window(300, 300);
		JSGraphicsEngine3D::Window* win2= new JSGraphicsEngine3D::Window(300, 300);
		JSGraphicsEngine3D::Button* but0 = new JSGraphicsEngine3D::Button(-50, -50, 100, 100 , win , win->GetId());
		
		while (true) {
			win->PollEvents();
			win2->PollEvents();
		}

		return 0;
	
	

	return -1;
}