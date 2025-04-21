#include "EventMouseMoved.hpp"

namespace JSGraphicsEngine3D {
	EventMouseMoved::EventMouseMoved( uint16_t MouseX, uint16_t MouseY) noexcept {
		m_MouseX = MouseX;
		m_MouseY = MouseY;
	}



	EventMouseMoved::Type EventMouseMoved::GetType(void) const noexcept { return Type::MOUSE_KEY_PRESSED; }

	uint16_t EventMouseMoved::GetMouseX(void) const noexcept { return m_MouseX; }
	uint16_t EventMouseMoved::GetMouseY(void) const noexcept { return m_MouseY; }
}