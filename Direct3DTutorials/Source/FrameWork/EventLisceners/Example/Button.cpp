#include "Button.hpp"
#include "../../Events/EventMouseKeyPressed.hpp"
#include "../../Events/EventMouseKeyReleased.hpp"
namespace JSGraphicsEngine3D {
	
	Button::Button(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Window* pWindow) : EventLiscener(pWindow) {
		m_PosX = x;
		m_PosY = y;
		m_Width = width;
		m_Height = height;
	}
		
	bool Button::HandleEvent(const Event* event) {
		static bool ButtonPushed = false;
		if (event->GetType() == Event::Type::MOUSE_KEY_PRESSED) {
			EventMouseKeyPressed* e = (EventMouseKeyPressed*)event;
			if (IsInRect(e->GetMouseX(), e->GetMouseY())) {
				ButtonPushed = true;
				ButtonClick();
			}
			return true;
		}

		if (event->GetType() == Event::Type::MOUSE_KEY_RELEASED) {
			EventMouseKeyReleased* e = (EventMouseKeyReleased*)event;
			if (IsInRect(e->GetMouseX(), e->GetMouseY())) {
				if (ButtonPushed)
					ButtonReleased();
				else
					return false;
			}
			return true;
		}

		return false;
	}

	bool Button::IsInRect(uint16_t x, uint16_t y) {

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

	void Button::ButtonClick(void) {
		MessageBoxA(nullptr, "Button Clicked", "Hi", MB_OK | MB_ICONEXCLAMATION);
	}

	void Button::ButtonReleased(void) {
		MessageBoxA(nullptr, "Button Released", "Hi", MB_OK | MB_ICONEXCLAMATION);
	}

}