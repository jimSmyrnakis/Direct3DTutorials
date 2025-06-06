#pragma once
#include "../Events/Events.hpp"
#include <vector>

namespace JSGraphicsEngine3D {
	extern class EventLiscener;
	class EventProducer { // Responsible for handing a event queue in a thread safe maner

	public:
		EventProducer(uint32_t MaxEvents);
		~EventProducer(void);

		void PushEvent(Event* event); 
		void EmptyEvents(void);
		void AddLiscener(EventLiscener* liscener); // must be a thread safe method

		void PollEvents(void); // must be a thread safe method



		EventProducer(const EventProducer& copy) = delete;
		EventProducer& operator=(const EventProducer& copy) = delete;

	private:
		Event**			m_Events;
		uint32_t		m_MaxEvents;
		uint32_t		m_EventsCount;
		uint32_t        m_CurrentEvent;
		

		std::vector<EventLiscener*> m_Lisceners;

		HANDLE			m_Mutex;
		

	};
}