#pragma once
#include "../../Core.hpp"

namespace JSGraphicsEngine3D {

	class Event {
	public:
		enum class Type {
			//KeyBoard Events
			KEY_PRESSED,
			KEY_RELEASE,
			KEY_CHAR,

			//Mouse Events
			MOUSE_KEY_PRESSED,
			MOUSE_DOUBLE_CLICK ,
			MOUSE_KEY_RELEASED,
			MOUSE_MOVE ,
			MOUSE_LEAVE,

			//Window Events
			LOST_FOCUS 
		};
	public:
		Event(void) noexcept = default ;
		virtual ~Event(void) noexcept = default;

		Event(const Event& copy) = delete;
		Event& operator=(const Event& copy) = delete;

		virtual Type GetType(void) const noexcept = 0;

		
	};

	


}