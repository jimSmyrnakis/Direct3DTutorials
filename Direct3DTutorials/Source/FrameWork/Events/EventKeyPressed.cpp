#include "EventKeyPressed.hpp"

namespace JSGraphicsEngine3D {
	EventKeyPressed::EventKeyPressed(uint32_t Repeats, uint32_t KeyCode) noexcept {
		m_KeyCode = KeyCode;
		m_Repeats = Repeats;
	}

	

	EventKeyPressed::Type EventKeyPressed::GetType(void) const noexcept { return Type::KEY_PRESSED;  }

	uint32_t EventKeyPressed::GetKeyCode(void) const noexcept { return m_KeyCode; }
	uint32_t EventKeyPressed::GetRepeats(void) const noexcept { return m_Repeats; }
}