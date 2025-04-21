#pragma once
#include "Events.hpp"

namespace JSGraphicsEngine3D {
	class EventMouseKeyReleased : public Event {
	public:
		EventMouseKeyReleased(uint32_t KeyCode, uint16_t MouseX , uint16_t MouseY) noexcept;
		virtual ~EventMouseKeyReleased(void) noexcept = default;

		EventMouseKeyReleased(const EventMouseKeyReleased& copy) = delete;
		EventMouseKeyReleased& operator=(const EventMouseKeyReleased& copy) = delete;

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