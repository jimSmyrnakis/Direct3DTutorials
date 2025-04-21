#pragma once
#include "Events.hpp"

namespace JSGraphicsEngine3D {
	class EventKeyReleased : public Event {
	public:
		EventKeyReleased( uint32_t KeyCode) noexcept;
		virtual ~EventKeyReleased(void) noexcept = default;

		EventKeyReleased(const EventKeyReleased& copy) = delete;
		EventKeyReleased& operator=(const EventKeyReleased& copy) = delete;

		virtual Type GetType(void) const noexcept override;

		uint32_t GetKeyCode(void) const noexcept;

	private:
		uint32_t m_KeyCode;

	};
}