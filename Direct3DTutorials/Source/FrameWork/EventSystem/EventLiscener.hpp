#pragma once
#include "../Events/Events.hpp"
#include "../Window.hpp"
#include <memory>
namespace JSGraphicsEngine3D {
	class EventLiscener {
	public:
		EventLiscener(std::shared_ptr<Window>& pWindow) ;
		virtual ~EventLiscener(void) ;
		virtual bool HandleEvent(const Event* event) = 0;
		bool IsActive(void) const ;// must be done in thread safe manner
		void SetActive(bool active); // must be done in thread safe manner

		EventLiscener(const EventLiscener& copy) = delete;
		EventLiscener& operator=(const EventLiscener& copy) = delete;

	private:
		HANDLE					m_Mutex;
		bool					m_Active;
		std::shared_ptr<Window> m_Window;
	};
}