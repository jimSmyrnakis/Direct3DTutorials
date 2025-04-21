#pragma once
#include "Events.hpp"

namespace JSGraphicsEngine3D {
	class EventMouseMoved : public Event {
	public:
		EventMouseMoved(uint16_t MouseX , uint16_t MouseY) noexcept;
		virtual ~EventMouseMoved(void) noexcept = default;

		EventMouseMoved(const EventMouseMoved& copy) = delete;
		EventMouseMoved& operator=(const EventMouseMoved& copy) = delete;

		virtual Type GetType(void) const noexcept override;

		uint16_t GetMouseX(void) const noexcept;
		uint16_t GetMouseY(void) const noexcept;

	private:
		uint16_t m_MouseX;
		uint16_t m_MouseY;

	};
}