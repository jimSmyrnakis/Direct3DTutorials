#pragma once
#include "Events.hpp"

namespace JSGraphicsEngine3D {
	class EventMouseMoved : public Event {
	public:
		EventMouseMoved(int16_t MouseX , int16_t MouseY ) noexcept;
		virtual ~EventMouseMoved(void) noexcept = default;

		EventMouseMoved(const EventMouseMoved& copy) = delete;
		EventMouseMoved& operator=(const EventMouseMoved& copy) = delete;

		virtual Type GetType(void) const noexcept override;

		int16_t GetMouseX(void) const noexcept;
		int16_t GetMouseY(void) const noexcept;

	private:
		int16_t m_MouseX;
		int16_t m_MouseY;
		uint32_t m_KeyCode;

	};
}