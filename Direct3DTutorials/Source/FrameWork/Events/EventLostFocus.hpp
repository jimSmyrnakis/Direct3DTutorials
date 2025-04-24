#pragma once
#include "Events.hpp"

namespace JSGraphicsEngine3D {

	class EventLostFocus : public Event{
	
	public:
		EventLostFocus(void) noexcept = default;
		virtual ~EventLostFocus(void) noexcept = default;

		EventLostFocus(const EventLostFocus& copy) = delete;
		EventLostFocus& operator=(const EventLostFocus& copy) = delete;

		virtual Type GetType(void) const noexcept ;


	};


}