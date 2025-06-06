#include "Window.hpp"

namespace JSGraphicsEngine3D {
	Window::Window(void) {
		Window(640, 320, L"GraphicsEngine3D");
	}
	Window::Window(uint16_t width, uint16_t height, const wchar_t* title) {
		// caculate client window size
		RECT rect;
		rect.left = 100;
		rect.top = 100;
		rect.bottom = height + rect.top;
		rect.right = width + rect.left;
		BOOL res = AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, false);
		JS_WINCHECK(res != FALSE);
		
		HINSTANCE hi = WindowClass::GetHInstance();
		const wchar_t* cname = WindowClass::GetName();
		
		// Depending on the window style this function will adjust the values right to match the desire 
		// client area and not set as the hole window size 
		//Create window instance
		m_hwnd = CreateWindowExW(
			0, // no extend styles
			cname,
			title,
			WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU , //dwstyle
			CW_USEDEFAULT ,
			CW_USEDEFAULT ,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			hi,
			this //  very important parameter as is mainly can used on the message handle
			// to interfiece with the window properties etc. Is used mainly for initiallization of the 
			// right call back function for events . Fisrt is passed to the MessageHandleSetUp function
			// so this function be able to change the handle procedure to the desired one of this class (C++ class i mean)
		);
		JS_WINCHECK(m_hwnd != 0);

		m_height = height;
		m_width = width;
		m_EventProducer = (new EventProducer(64));
		msg = new MSG;
		
		JS_WINCHECK(ShowWindow(m_hwnd, SW_SHOWDEFAULT));

		
	}
	Window::~Window(void) {
		if (msg)
			delete msg;
		if (m_EventProducer)
			delete m_EventProducer;
		JS_WINCHECK(DestroyWindow(m_hwnd));
	}

	EventProducer& Window::GetEventProducer(void) const  {
		return (*m_EventProducer);
	}

	HWND Window::GetId(void) const  {
		return m_hwnd;
	}

	bool Window::PollEvents(void) {
		
		BOOL res;
		
		JS_WINCHECK(res = PeekMessageW(msg, m_hwnd, 0, 0, PM_REMOVE));
		
		if (res == TRUE) {

			JS_WINCHECK(TranslateMessage(msg));//Translates virtual-key messages into character messages.
			//The character messages are posted to the calling thread's message queue, to be 
			// read the next time the thread calls the GetMessage or PeekMessage function.
			JS_WINCHECK(DispatchMessageW(msg));//Dispatches a message to a window procedure. It is typically 
			//used to dispatch a message retrieved by the GetMessage function.

			m_EventProducer->PollEvents();

			return true;

		}

		//if (res > 0)
		//	return false;

		return false;
	}

	uint32_t Window::GetWidth(void) const { return m_width; }

	uint32_t Window::GetHeight(void) const { return m_height; }

}