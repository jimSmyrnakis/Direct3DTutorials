#include "EventKeyChar.hpp"

namespace JSGraphicsEngine3D {
	
	EventKeyChar::EventKeyChar(char ch) noexcept  {
		m_Character = ch;
	}
		

	EventKeyChar::Type EventKeyChar::GetType(void) const noexcept {
		return Type::KEY_CHAR;
	}

	uint32_t EventKeyChar::GetCharacter(void) const noexcept {
		return m_Character;
	}
	

}