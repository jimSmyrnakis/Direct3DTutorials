#include "Window.hpp"
#include "../../resource1.h"
namespace JSGraphicsEngine3D {

	const wchar_t* Window::WindowClass::Name = L"JSGraphicsEngine3D";
	Window::WindowClass* Window::WindowClass::WindowClassThis = nullptr;

	Window::WindowClass::WindowClass(void) : hinstance( GetModuleHandle(nullptr)) /*Gets the current process instance */ {
		JSASSERT(WindowClassThis == nullptr);
		WindowClassThis = this;
		//register a window class , with unicode 16-bit utf support :)
		WNDCLASSEXW WindowClassConfiguration = { 0 }; // good practise to zero-ed all of it except if sayd otherwise 
		WindowClassConfiguration.cbSize = sizeof(WNDCLASSEXW); // size in bytes of this structure 
		WindowClassConfiguration.style = CS_OWNDC; // one device context per window instance :)
		WindowClassConfiguration.lpfnWndProc = Window::HandleMsgSetUp; // one handle for all events on all window instances :)
		WindowClassConfiguration.hInstance = GetHInstance();
		WindowClassConfiguration.lpszClassName = GetName();
		WindowClassConfiguration.hIcon = (HICON)(LoadImage(hinstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 256, 256, 0));
		WindowClassConfiguration.hIconSm = (HICON)(LoadImage(hinstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 256, 256, 0));;
		JSASSERT(RegisterClassExW(&WindowClassConfiguration)); // Register the class
		
	}
	Window::WindowClass::~WindowClass(void) {
		UnregisterClassW(GetName() , hinstance);
	}

	const wchar_t* Window::WindowClass::GetName(void) { 
		if (WindowClassThis == nullptr) {
			WindowClassThis = new  Window::WindowClass();
		}
		return Name;  
	}

	
	HINSTANCE Window::WindowClass::GetHInstance(void) { 
		if (WindowClassThis == nullptr) {
			WindowClassThis = new  Window::WindowClass();
		}
		return WindowClassThis->hinstance;  
	}

}