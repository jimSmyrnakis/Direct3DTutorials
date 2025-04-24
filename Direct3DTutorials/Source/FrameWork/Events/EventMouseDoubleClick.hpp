#pragma once
#include "Events.hpp"

namespace JSGraphicsEngine3D {
	class EventMouseDoubleClick : public Event {
	public:
		EventMouseDoubleClick( uint32_t KeyCode, uint16_t MouseX, uint16_t MouseY) noexcept;
		virtual ~EventMouseDoubleClick(void) noexcept = default;

		EventMouseDoubleClick(const EventMouseDoubleClick& copy) = delete;
		EventMouseDoubleClick& operator=(const EventMouseDoubleClick& copy) = delete;

		virtual Type GetType(void) const noexcept override;

		uint32_t GetKeyCode(void) const noexcept;
		uint16_t GetMouseX(void) const noexcept;
		uint16_t GetMouseY(void) const noexcept;

	private:
		uint32_t m_KeyCode;
		uint16_t m_MouseX;
		uint16_t m_MouseY;

	};
}