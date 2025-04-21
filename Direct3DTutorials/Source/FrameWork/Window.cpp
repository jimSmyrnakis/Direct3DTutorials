#include "Window.hpp"

namespace JSGraphicsEngine3D {

	Window::Window(uint16_t width, uint16_t height, const wchar_t* title) {
		// caculate client window size
		RECT rect;
		rect.left = 100;;
		rect.top = 100;
		rect.bottom = height + rect.top;
		rect.right = width + rect.left;
		AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, false);
		// Depending on the window style this function will adjust the values right to match the desire 
		// client area and not set as the hole window size 
		//Create window instance
		m_hwnd = CreateWindowExW(
			0, // no extend styles
			WindowClass::GetName(),
			title,
			WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, //dwstyle
			CW_USEDEFAULT ,
			CW_USEDEFAULT ,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			WindowClass::GetHInstance(),
			this //  very important parameter as is mainly can used on the message handle
			// to interfiece with the window properties etc. Is used mainly for initiallization of the 
			// right call back function for events . Fisrt is passed to the MessageHandleSetUp function
			// so this function be able to change the handle procedure to the desired one of this class (C++ class i mean)
		);

		m_height = height;
		m_width = width;

		ShowWindow(m_hwnd, SW_SHOWDEFAULT);
	}
	Window::~Window(void) {
		DestroyWindow(m_hwnd);
	}

}