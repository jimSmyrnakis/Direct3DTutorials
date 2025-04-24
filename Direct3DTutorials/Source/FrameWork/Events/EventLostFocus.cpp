#include "EventLostFocus.hpp"

namespace JSGraphicsEngine3D {

	
	EventLostFocus::Type EventLostFocus::GetType(void) const noexcept {
		return Type::LOST_FOCUS;
	}


}