#include "EventKeyReleased.hpp"

namespace JSGraphicsEngine3D {
	EventKeyReleased::EventKeyReleased(uint32_t KeyCode) noexcept {
		m_KeyCode = KeyCode;
	}



	EventKeyReleased::Type EventKeyReleased::GetType(void) const noexcept { return Type::KEY_RELEASE; }

	uint32_t EventKeyReleased::GetKeyCode(void) const noexcept { return m_KeyCode; }
}