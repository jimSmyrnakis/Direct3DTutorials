#include "Button.hpp"

#include <sstream>
namespace JSGraphicsEngine3D {
	
	Button::Button(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Window* pWindow, HWND hwnd) : EventLiscener(pWindow) {
		m_PosX = x;
		m_PosY = y;
		m_Width = width;
		m_Height = height;
		m_Window = pWindow;
		m_hwnd = hwnd;
	}

#define PrintPos( h , e ) { \
	std::wstringstream ss;\
	ss << L"Pos : ( " << e->GetMouseX() << L" , " << e->GetMouseY() << L" ) " << std::endl;\
	SetWindowTextW(h, ss.str().c_str());\
}
		
	bool Button::HandleEvent(const Event* event) {
		
		static bool ButtonPushed = false;
		if (event->GetType() == Event::Type::MOUSE_MOVE) {
			EventMouseMoved* e = (EventMouseMoved*)event;
			if (ButtonPushed) {
				OnCapture(e);
				return true;
			}
			if (IsInRect(e->GetMouseX(), e->GetMouseY())) {
				MouseMoved(e);
				return true;
			}
			
		}

		if (event->GetType() == Event::Type::MOUSE_KEY_PRESSED) {
			EventMouseKeyPressed* e = (EventMouseKeyPressed*)event;
			if (IsInRect(e->GetMouseX(), e->GetMouseY())) {
				ButtonPushed = true;
				Click(e);
				return true;
			}

			
		}

		if (event->GetType() == Event::Type::MOUSE_DOUBLE_CLICK) {
			EventMouseDoubleClick* e = (EventMouseDoubleClick*)event;
			if (IsInRect(e->GetMouseX(), e->GetMouseY())) {
				
				ButtonPushed = true;
				DoubleClick(e);
				return true;
			}

		}

		if (event->GetType() == Event::Type::MOUSE_KEY_RELEASED) {
			EventMouseKeyReleased* e = (EventMouseKeyReleased*)event;
			if (ButtonPushed) {
				Released(e);
				ButtonPushed = false;
				return true;
			}
			
		}

		//PrintPos(m_hwnd, e);


		return false;
	}

	bool Button::IsInRect(int16_t x, int16_t y) {

		POINTS xRange = { .x = (SHORT)m_PosX , .y = (SHORT)(m_PosX + m_Width) };
		if (x < xRange.x)
			return false;
		if (x > xRange.y)
			return false;

		POINTS yRange = { .x = (SHORT)m_PosY , .y = (SHORT)(m_PosY + m_Height) };
		if (y < yRange.x)
			return false;
		if (y > yRange.y)
			return false;

		return true;
	}

	void Button::Click(EventMouseKeyPressed* e) {
		SetWindowTextW(m_hwnd, L"Button Clikced !!!");
		//MessageBoxA(nullptr, "Button Clicked", "Hi", MB_OK | MB_ICONEXCLAMATION);
	}

	void Button::Released(EventMouseKeyReleased* e) {
		SetWindowTextW(m_hwnd, L"Button Released !!!");
		//MessageBoxA(nullptr, "Button Released", "Hi", MB_OK | MB_ICONEXCLAMATION);
	}

	void Button::MouseMoved(EventMouseMoved* e) {
		std::wstringstream ss;
		ss << L"Mouse Move (" << e->GetMouseX() << L" , " << e->GetMouseY() << L" ) " << std::endl;
		SetWindowTextW(m_hwnd, ss.str().c_str());
		//MessageBoxA(nullptr, "Mouse Moved", "Hi", MB_OK | MB_ICONEXCLAMATION);
	}

	void Button::DoubleClick(EventMouseDoubleClick* e) {
		SetWindowTextW(m_hwnd, L"Mouse Double Click !!!");
		//de-activate this liscener
		//this->SetActive(false);
		// after this event the liscener is takes other events
	}
	void Button::OnCapture(EventMouseMoved* e) {
		SetWindowTextW(m_hwnd, L"On Capture !!!");
	}
	void Button::TrollMe(void) {
		//SetWindowTextW(m_hwnd, L"Που Πας ? \"Where are you going ?\"");
	}

}