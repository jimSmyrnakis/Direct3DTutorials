#pragma once
#include "../FrameWork/Window.hpp"
#include "../FrameWork/EventLisceners/Example/Button.hpp"

namespace JSGraphicsEngine3D {
	class Application {

	public:
		Application(void) = default;
		~Application(void) = default;

		void OnRun(void);
		// after leaving the OnRun method the OnDestroy is called a little before the Application stop executing
		int OnDestroy(void);
		//return the exit code

	};

	Application* ApplicationEntry;
}


int CALLBACK WinMain( // CALLBACK is stdcall function conversion , is important for window methods calls 
	_In_ HINSTANCE hInstance, // the current instance of the application window 
	_In_ HINSTANCE hPrevInstance, // not used any more
	_In_ LPSTR lpCmdLine, // a string to the command line argument (all in one and not seperate)
	_In_ int  nCmdhow // how the window must be show when the program starts
) {
	JSGraphicsEngine3D::ApplicationEntry = new JSGraphicsEngine3D::Application();
	if (JSGraphicsEngine3D::ApplicationEntry == nullptr) {
		return 1;
	}
	JSGraphicsEngine3D::ApplicationEntry->OnRun();
	int cd = JSGraphicsEngine3D::ApplicationEntry->OnDestroy();
	delete JSGraphicsEngine3D::ApplicationEntry;
	return cd;

}