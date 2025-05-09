#include "Window.hpp"
#include <string>
#include <sstream>
#include "EventSystem/EventProducer.hpp"
#include "Events/EventKeyChar.hpp"
#include "Events/EventKeyPressed.hpp"
#include "Events/EventKeyReleased.hpp"
#include "Events/EventMouseKeyPressed.hpp"
#include "Events/EventMouseKeyReleased.hpp"
#include "Events/EventMouseMoved.hpp"
#include "Events/EventLostFocus.hpp"
#include "Events/EventMouseDoubleClick.hpp"
#include "Events/EventMouseLeave.hpp"
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
		
		// then every time push the right events to the EventProducer
		bool HasEvent = false;
		Event* e = nullptr;
		POINTS p ;LPPOINT pt = new POINT();
		LPPOINT pr = new POINT();
		POINT realp;
		static bool OnReleaseCapture = false;
		std::stringstream ss;
		switch (msgCode) {
		case WM_CLOSE:
			PostQuitMessage(0); return 0;
		
		case WM_KEYDOWN:
			if (wParam == 'Q') {
				SetWindowTextW(hwnd, L"Key Down Q");
			}
			return 0;
		case WM_KEYUP:
			if (wParam == 'Q') {
				SetWindowTextW(hwnd, L"Key Up :)");
			}
			return 0;
		case WM_CHAR:

			return 0;




		//==========================================================================
		//==========================================================================
		//==========================================================================
		//==========================================================================
		//================================Mouse Events==============================
		case WM_MOUSEMOVE:
		{
			if (OnReleaseCapture) {
				OnReleaseCapture = false;
				return 0;
			} 
			
			GetCursorPos(pt); // screen coordinates
			(*pr) = { 0 };
			ClientToScreen(m_hwnd , pr); // get client base screen coords
			//find the difference to the screen (mainly for capture and draging)
			realp = {
				.x = pt->x - pr->x ,
				.y = pt->y - pr->y
			};
			e = new EventMouseMoved(realp.x, realp.y);
			
			HasEvent = true;
			break;
		}
			
		//Mouse Left Button
		case WM_LBUTTONDOWN:
			SetCapture(m_hwnd);
			p = MAKEPOINTS(lParam);
			GetCursorPos(pt); // screen coordinates
			(*pr) = { 0 };
			ClientToScreen(m_hwnd, pr); // get client base screen coords
			//find the difference to the screen (mainly for capture and draging)
			realp = {
				.x = pt->x - pr->x ,
				.y = pt->y - pr->y
			};
			e = new EventMouseKeyPressed(0, VK_LBUTTON, p.x, p.y);
			HasEvent = true;
			break;
		case WM_LBUTTONUP:
			ReleaseCapture();
			OnReleaseCapture = true;
			p = MAKEPOINTS(lParam);
			GetCursorPos(pt); // screen coordinates
			(*pr) = { 0 };
			ClientToScreen(m_hwnd, pr); // get client base screen coords
			//find the difference to the screen (mainly for capture and draging)
			realp = {
				.x = pt->x - pr->x ,
				.y = pt->y - pr->y
			};
			e = new EventMouseKeyReleased(VK_LBUTTON, p.x, p.y);
			HasEvent = true;
			break;
		case WM_LBUTTONDBLCLK:
			SetCapture(m_hwnd);
			p = MAKEPOINTS(lParam);
			GetCursorPos(pt); // screen coordinates
			(*pr) = { 0 };
			ClientToScreen(m_hwnd, pr); // get client base screen coords
			//find the difference to the screen (mainly for capture and draging)
			realp = {
				.x = pt->x - pr->x ,
				.y = pt->y - pr->y
			};
			e = new EventMouseDoubleClick(VK_LBUTTON, p.x, p.y);
			HasEvent = true;
			break;
		//Mouse Right Button
		case WM_RBUTTONDOWN:
			SetCapture(m_hwnd);
			p = MAKEPOINTS(lParam);
			e = new EventMouseKeyPressed(0, VK_RBUTTON, p.x, p.y);
			HasEvent = true;
			break;
		case WM_RBUTTONUP:
			ReleaseCapture();
			OnReleaseCapture = true;
			p = MAKEPOINTS(lParam);
			e = new EventMouseKeyReleased(VK_RBUTTON, p.x, p.y);
			HasEvent = true;
			break;
		case WM_RBUTTONDBLCLK:
			SetCapture(m_hwnd);
			p = MAKEPOINTS(lParam);
			e = new EventMouseDoubleClick(VK_RBUTTON, p.x, p.y);
			HasEvent = true;
			break;
		//Mouse Middle Button 
		case WM_MBUTTONDOWN:
			SetCapture(m_hwnd);
			p = MAKEPOINTS(lParam);
			e = new EventMouseKeyPressed(0, VK_MBUTTON, p.x, p.y);
			HasEvent = true;
			break;
		case WM_MBUTTONUP:
			ReleaseCapture();
			OnReleaseCapture = true;
			p = MAKEPOINTS(lParam);
			e = new EventMouseKeyReleased(VK_MBUTTON, p.x, p.y);
			HasEvent = true;
			break;
		case WM_MBUTTONDBLCLK:
			SetCapture(m_hwnd);
			p = MAKEPOINTS(lParam);
			e = new EventMouseDoubleClick(VK_MBUTTON, p.x, p.y);
			HasEvent = true;
			break;
		//Extra Button 1 or 2
		case WM_XBUTTONDOWN:
			SetCapture(m_hwnd);
			p = MAKEPOINTS(lParam);
			e = new EventMouseKeyPressed(0, GET_XBUTTON_WPARAM(wParam), p.x, p.y);
			HasEvent = true;
			break;
		case WM_XBUTTONUP:
			ReleaseCapture();
			OnReleaseCapture = true;
			p = MAKEPOINTS(lParam);
			e = new EventMouseKeyReleased(GET_XBUTTON_WPARAM(wParam), p.x, p.y);
			HasEvent = true;
			break;
		case WM_XBUTTONDBLCLK:
			SetCapture(m_hwnd);
			p = MAKEPOINTS(lParam);
			e = new EventMouseDoubleClick(GET_XBUTTON_WPARAM(wParam), p.x, p.y);
			HasEvent = true;
			break;
		//Mouse Leave
		case WM_MOUSELEAVE:
			ReleaseCapture();
			OnReleaseCapture = true;
			e = new EventMouseLeave();
			HasEvent = true;
			break;




		case WM_KILLFOCUS: // if lost focus remove all events and add a eventLostFocus event only
			ReleaseCapture();
			OnReleaseCapture = true;
			m_EventProducer->EmptyEvents();
			e = new EventLostFocus();
			HasEvent = true;
			break;
		}

		delete pt;
		delete pr;
		if (HasEvent) {
			m_EventProducer->PushEvent(e);
			return 0;
		}
		
		return DefWindowProcW(hwnd, msgCode, wParam, lParam);
	}


}