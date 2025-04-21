#include "FrameWork/Window.hpp"
#include "FrameWork/EventLisceners/Example/Button.hpp"
int CALLBACK WinMain( // CALLBACK is stdcall function conversion , is important for window methods calls 
	_In_ HINSTANCE hInstance, // the current instance of the application window 
	_In_ HINSTANCE hPrevInstance, // not used any more
	_In_ LPSTR lpCmdLine, // a string to the command line argument (all in one and not seperate)
	_In_ int  nCmdhow // how the window must be show when the program starts
) {
	try {
		JSGraphicsEngine3D::Window win(300, 300);
		JSGraphicsEngine3D::Window win2(300, 300);
		JSGraphicsEngine3D::Button* but0 = new JSGraphicsEngine3D::Button(0, 0, 20, 20 , &win);
		MSG msg;
		BOOL res;
		while ((res = GetMessageW(&msg, NULL, 0, 0)) > 0) {
			TranslateMessage(&msg);//Translates virtual-key messages into character messages.
			//The character messages are posted to the calling thread's message queue, to be 
			// read the next time the thread calls the GetMessage or PeekMessage function.
			DispatchMessageW(&msg);//Dispatches a message to a window procedure. It is typically 
			//used to dispatch a message retrieved by the GetMessage function.
			win.GetEventProducer()->PollEvents();
		}

		if (res == -1) {
			return -1;
		}
		else {
			return msg.wParam; // the exit code we give in the method
		}

		return 0;
	}
	catch (JSGraphicsEngine3D::JSException& e) {
		MessageBoxA(nullptr, e.what(), e.type(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (std::exception& e) {
		MessageBoxA(nullptr, e.what(), "std Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...) {
		MessageBoxA(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	

	return -1;
}