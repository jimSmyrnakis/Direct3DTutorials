#include "EventMouseDoubleClick.hpp"

namespace JSGraphicsEngine3D {
	EventMouseDoubleClick::EventMouseDoubleClick( uint32_t KeyCode, uint16_t MouseX, uint16_t MouseY) noexcept {
		m_KeyCode = KeyCode;
		m_MouseX = MouseX;
		m_MouseY = MouseY;
	}



	EventMouseDoubleClick::Type EventMouseDoubleClick::GetType(void) const noexcept { return Type::MOUSE_DOUBLE_CLICK; }

	uint32_t EventMouseDoubleClick::GetKeyCode(void) const noexcept { return m_KeyCode; }
	uint16_t EventMouseDoubleClick::GetMouseX(void) const noexcept { return m_MouseX; }
	uint16_t EventMouseDoubleClick::GetMouseY(void) const noexcept { return m_MouseY; }
}