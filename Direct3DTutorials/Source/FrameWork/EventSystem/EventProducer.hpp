#pragma once
#include "../Events/Events.hpp"
#include "../Events/EventKeyChar.hpp"
#include "../Events/EventKeyPressed.hpp"
#include "../Events/EventKeyReleased.hpp"
#include "../Events/EventMouseKeyPressed.hpp"
#include "../Events/EventMouseKeyReleased.hpp"
#include "../Events/EventMouseMoved.hpp"
//#include "EventLiscener.hpp"

namespace JSGraphicsEngine3D {
	extern class EventLiscener;
	class EventProducer { // Responsible for handing a event queue in a thread safe maner

	public:
		EventProducer(uint32_t MaxEvents ,uint16_t MaxLisceners );
		~EventProducer(void);

		void PushEvent(Event* event); 
		void AddLiscener(EventLiscener* liscener); // must be a thread safe method

		void PollEvents(void); // must be a thread safe method



		EventProducer(const EventProducer& copy) = delete;
		EventProducer& operator=(const EventProducer& copy) = delete;

	private:
		Event**			m_Events;
		uint32_t		m_MaxEvents;
		uint32_t		m_EventsCount;
		uint32_t        m_CurrentEvent;
		

		EventLiscener** m_Lisceners;
		uint16_t		m_MaxLisceners;
		uint16_t		m_LiscenersCount;
		HANDLE			m_Mutex;
		

	};
}