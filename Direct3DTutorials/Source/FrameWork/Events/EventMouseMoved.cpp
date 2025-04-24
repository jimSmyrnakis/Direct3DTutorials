#include "EventMouseMoved.hpp"

namespace JSGraphicsEngine3D {
	EventMouseMoved::EventMouseMoved(int16_t MouseX, int16_t MouseY) noexcept {
		m_MouseX = MouseX;
		m_MouseY = MouseY;
	}



	EventMouseMoved::Type EventMouseMoved::GetType(void) const noexcept { return Type::MOUSE_MOVE; }

	int16_t EventMouseMoved::GetMouseX(void) const noexcept { return m_MouseX; }
	int16_t EventMouseMoved::GetMouseY(void) const noexcept { return m_MouseY; }
}