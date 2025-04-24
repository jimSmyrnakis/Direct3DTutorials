#pragma once
#include "Events.hpp"

namespace JSGraphicsEngine3D {

	class EventMouseLeave : public Event {

	public:
		EventMouseLeave(void) noexcept = default;
		virtual ~EventMouseLeave(void) noexcept = default;

		EventMouseLeave(const EventMouseLeave& copy) = delete;
		EventMouseLeave& operator=(const EventMouseLeave& copy) = delete;

		virtual Type GetType(void) const noexcept;


	};


}