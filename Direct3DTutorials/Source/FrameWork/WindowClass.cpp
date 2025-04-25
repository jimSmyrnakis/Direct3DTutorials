#include "Window.hpp"
#include "../../resource1.h"
namespace JSGraphicsEngine3D {

	
	
	
	Window::WindowClass* Window::WindowClass::WindowClassThis = new  Window::WindowClass();
	
	Window::WindowClass::WindowClass(void) : hinstance( GetModuleHandle(nullptr)) /*Gets the current process instance */ {
		JS_CORE_ASSERT(WindowClassThis == nullptr , JS_ERROR_REINSTANCIATE_SIGLITON , "WindowClass must created only once !!!");
		WindowClassThis = this;
		//register a window class , with unicode 16-bit utf support :)
		WNDCLASSEXW WindowClassConfiguration = { 0 }; // good practise to zero-ed all of it except if sayd otherwise 
		WindowClassConfiguration.cbSize = sizeof(WNDCLASSEXW); // size in bytes of this structure 
		WindowClassConfiguration.style = CS_OWNDC | CS_DBLCLKS; // one device context per window instance :)
		WindowClassConfiguration.lpfnWndProc = Window::HandleMsgSetUp; // one handle for all events on all window instances :)
		WindowClassConfiguration.hInstance = GetHInstance();
		WindowClassConfiguration.lpszClassName = GetName();
		WindowClassConfiguration.hIcon = (HICON)(LoadImage(hinstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 256, 256, 0));
		WindowClassConfiguration.hIconSm = (HICON)(LoadImage(hinstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 256, 256, 0));;
		JS_CORE_WINDOWS_ASSERT(RegisterClassExW(&WindowClassConfiguration));  // Register the class
		
	}
	Window::WindowClass::~WindowClass(void) {
		UnregisterClassW(GetName() , hinstance);
	}

	wchar_t* Window::WindowClass::GetName(void) { 

		static LPWSTR name = new wchar_t[64];
		static bool firstTime = true;
		if (firstTime) {
			firstTime = false;
			lstrcpyW(name, L"JSGraphicsEngine3D");
		}
		return name;  
	}

	
	HINSTANCE Window::WindowClass::GetHInstance(void) { 
		return WindowClassThis->hinstance;  
	}

}