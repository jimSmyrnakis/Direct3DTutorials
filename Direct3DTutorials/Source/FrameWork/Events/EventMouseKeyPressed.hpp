#pragma once
#include "Events.hpp"

namespace JSGraphicsEngine3D {
	class EventMouseKeyPressed : public Event {
	public:
		EventMouseKeyPressed(uint32_t Repeats, uint32_t KeyCode , uint16_t MouseX , uint16_t MouseY) noexcept;
		virtual ~EventMouseKeyPressed(void) noexcept = default;

		EventMouseKeyPressed(const EventMouseKeyPressed& copy) = delete;
		EventMouseKeyPressed& operator=(const EventMouseKeyPressed& copy) = delete;

		virtual Type GetType(void) const noexcept override;

		uint32_t GetKeyCode(void) const noexcept;
		uint32_t GetRepeats(void) const noexcept;
		uint16_t GetMouseX(void) const noexcept;
		uint16_t GetMouseY(void) const noexcept;

	private:
		uint32_t m_Repeats;
		uint32_t m_KeyCode;
		uint16_t m_MouseX;
		uint16_t m_MouseY;

	};
}