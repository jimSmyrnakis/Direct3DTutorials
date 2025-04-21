#include "EventMouseKeyReleased.hpp"

namespace JSGraphicsEngine3D {
	EventMouseKeyReleased::EventMouseKeyReleased( uint32_t KeyCode, uint16_t MouseX, uint16_t MouseY) noexcept{
		m_KeyCode = KeyCode;
		m_MouseX = MouseX;
		m_MouseY = MouseY;
	}



	EventMouseKeyReleased::Type EventMouseKeyReleased::GetType(void) const noexcept { return Type::MOUSE_KEY_RELEASED; }

	uint32_t EventMouseKeyReleased::GetKeyCode(void) const noexcept { return m_KeyCode; }
	uint16_t EventMouseKeyReleased::GetMouseX(void) const noexcept { return m_MouseX; }
	uint16_t EventMouseKeyReleased::GetMouseY(void) const noexcept { return m_MouseY; }
}