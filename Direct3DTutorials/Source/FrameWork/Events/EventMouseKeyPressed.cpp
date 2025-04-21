#include "EventMouseKeyPressed.hpp"

namespace JSGraphicsEngine3D {
	EventMouseKeyPressed::EventMouseKeyPressed(uint32_t Repeats, uint32_t KeyCode, uint16_t MouseX, uint16_t MouseY) noexcept  {
		m_KeyCode = KeyCode;
		m_Repeats = Repeats;
		m_MouseX = MouseX;
		m_MouseY = MouseY;
	}



	EventMouseKeyPressed::Type EventMouseKeyPressed::GetType(void) const noexcept { return Type::MOUSE_KEY_PRESSED; }

	uint32_t EventMouseKeyPressed::GetKeyCode(void) const noexcept { return m_KeyCode; }
	uint32_t EventMouseKeyPressed::GetRepeats(void) const noexcept { return m_Repeats; }
	uint16_t EventMouseKeyPressed::GetMouseX(void) const noexcept { return m_MouseX; }
	uint16_t EventMouseKeyPressed::GetMouseY(void) const noexcept { return m_MouseY; }
}