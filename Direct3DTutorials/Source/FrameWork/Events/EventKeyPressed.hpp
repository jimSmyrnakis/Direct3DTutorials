#pragma once
#include "Events.hpp"

namespace JSGraphicsEngine3D {
	class EventKeyPressed : public Event {
	public:
		EventKeyPressed(uint32_t Repeats, uint32_t KeyCode) noexcept;
		virtual ~EventKeyPressed(void) noexcept = default;

		EventKeyPressed(const EventKeyPressed& copy) = delete;
		EventKeyPressed& operator=(const EventKeyPressed& copy) = delete;

		virtual Type GetType(void) const noexcept override;

		uint32_t GetKeyCode(void) const noexcept;
		uint32_t GetRepeats(void) const noexcept;

	private:
		uint32_t m_Repeats;
		uint32_t m_KeyCode;

	};
}
