#pragma once
#include "../../Core.hpp"

namespace JSGraphicsEngine3D {

	class Event {
	public:
		enum class Type {
			KEY_PRESSED,
			KEY_RELEASE,
			MOUSE_KEY_PRESSED,
			MOUSE_KEY_RELEASED,
			KEY_CHAR,
			MOUSE_MOVE 
		};
	public:
		Event(void) noexcept = default ;
		virtual ~Event(void) noexcept = default;

		Event(const Event& copy) = delete;
		Event& operator=(const Event& copy) = delete;

		virtual Type GetType(void) const noexcept = 0;

		
	};

	


}