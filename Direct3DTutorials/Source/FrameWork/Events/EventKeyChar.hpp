#pragma once
#include "Events.hpp"

namespace JSGraphicsEngine3D {
	class EventKeyChar : public Event {
	public:
		EventKeyChar(char ch ) noexcept;
		virtual ~EventKeyChar(void) noexcept = default;

		EventKeyChar(const EventKeyChar& copy) = delete;
		EventKeyChar& operator=(const EventKeyChar& copy) = delete;

		virtual Type GetType(void) const noexcept override;

		uint32_t GetCharacter(void) const noexcept;

	private:
		uint32_t m_Character;
	};
}
