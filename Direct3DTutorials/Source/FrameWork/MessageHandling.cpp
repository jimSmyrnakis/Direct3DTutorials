#include "Window.hpp"
#include <string>
#include <sstream>
namespace JSGraphicsEngine3D {
	
	LRESULT CALLBACK Window::HandleMsgSetUp(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam) {
		if (msgCode == WM_NCCREATE) { // this event called the first time a window is created
			//now if this is true then lParam is actualy a pointer to the CREATESTRUCT that constains
			//all the information of the window function parameters of the CreateWindow so 
			CREATESTRUCT* CreateWindowStructPTR = (CREATESTRUCT*)lParam;
			//know the first mebmer of this struct is lpCreateParams that contain the extra parameters
			//we pass through when first create a window instance
			Window* ThisWindow = (Window*)CreateWindowStructPTR->lpCreateParams;
			//now set the window instance data pointers and settings , so it can access them any time
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)ThisWindow);
			//Change the message handle procedure of this hwnd instance window
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)Window::HandleMsgThunk);
			//Before leaving handle the message
			return ThisWindow->MessageEventsHandle(hwnd, msgCode, wParam, lParam);
		}
		//if something else , then handle it with the default way
		return DefWindowProcW(hwnd, msgCode, wParam, lParam);
	}

	LRESULT CALLBACK Window::HandleMsgThunk(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam) {
		//its job is to just call the proper method of the current window instance
		Window* ThisWindow = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		//now call the right one
		return ThisWindow->MessageEventsHandle(hwnd, msgCode, wParam, lParam);
	}

	LRESULT Window::MessageEventsHandle(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam) {
		static std::wstring title;
		switch (msgCode) {
		case WM_CLOSE:
			PostQuitMessage(69); return 0;
		case WM_MOUSEMOVE:
			SetWindowTextW(hwnd, L"Mouse Move");return 0;;
		case WM_KEYDOWN:
			if (wParam == 'Q') {
				SetWindowTextW(hwnd, L"Key Down Q");
			}
			return 0;
		case WM_KEYUP:
			if (wParam == 'Q') {
				SetWindowTextW(hwnd, L"Pussy");
			}
			return 0;
		case WM_CHAR:

			title += wParam;
			SetWindowTextW(hwnd, title.c_str());
			return 0;
		case WM_LBUTTONDOWN:
			POINTS p = MAKEPOINTS(lParam);
			std::wstringstream title2;
			title2 << L"Aoutch at (" << p.x << L',' << p.y << L")";
			SetWindowTextW(hwnd, title2.str().c_str());
			return 0;
		}


		return DefWindowProcW(hwnd, msgCode, wParam, lParam);
	}


}