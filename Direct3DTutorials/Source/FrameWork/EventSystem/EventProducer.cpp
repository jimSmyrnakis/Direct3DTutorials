#include "EventProducer.hpp"
#include "EventLiscener.hpp"
#include <sstream>
namespace JSGraphicsEngine3D {
	EventProducer::EventProducer(uint32_t MaxEvents) {
		// allocate the space needed for the queue
		m_Events = new Event * [MaxEvents];
		JS_CORE_ASSERT(m_Events != nullptr, JS_ERROR_NO_MEMORY , "Out Of Memory , can't allocate space for events !!!");
		m_MaxEvents = MaxEvents;
		m_EventsCount = 0;
		m_CurrentEvent = 0;
		

		

		//Create a mutex for thread synchronization (Handle is already a pointer )
		m_Mutex = CreateMutexW(nullptr, FALSE, nullptr);
		JS_CORE_ASSERT(m_Mutex != nullptr, JS_ERROR_CANT_CREATE_MUTEX, "Can't Create mutex object !!!");

	}

	EventProducer::~EventProducer(void) {
		this->EmptyEvents();
		if (m_Events)
			delete[] m_Events;
		for (int i = 0; i < m_Lisceners.size(); i++)
			delete m_Lisceners[i];
		CloseHandle(m_Mutex);
	}

#define Before_Entry {\
	DWORD res = WaitForSingleObject(m_Mutex, INFINITE); \
	JS_CORE_ASSERT(res == WAIT_OBJECT_0 , JS_ERROR_BAD_MUTEX , "Bad Mutex State !!!" );\
} 

#define Before_Leaving { \
	BOOL check = ReleaseMutex(m_Mutex); \
	JS_CORE_ASSERT(check != FALSE , JS_ERROR_BAD_MUTEX , "Bad Mutex State !!!")\
}

	void EventProducer::PushEvent(Event* event) {
		// before entry lock
		Before_Entry;
		// check if has space for new event
		if (m_EventsCount < m_MaxEvents) {
			// add the event in the next available slot
			m_Events[m_CurrentEvent] = event;
			//increment the currentEvent to point to the next available slot
			m_CurrentEvent++;
			m_EventsCount++;
			//before leaving unlock
			Before_Leaving;
			return; // return;
		}

		JS_CORE_WARN("Events are full for the current Event Producer so a event loss is happening " , JS_WARNING_LOSSY_EVENTS );


		//if the space is fulled then
		//if m_CurrentEvent is equal to max Events then make it zero
		if (m_CurrentEvent >= m_MaxEvents) {
			m_CurrentEvent = 0;
		}

		//replace the old event with the new one :( bad case events runs out
		//first free it 
		delete m_Events[m_CurrentEvent];
		//after point to the new one 
		m_Events[m_CurrentEvent] = event;

		//increment only the current event to point to the next event that will replace
		m_CurrentEvent++;
		//before leaving unlock
		Before_Leaving;
		return;

	}

	void EventProducer::AddLiscener(EventLiscener * liscener){// must be a thread safe method
		// before entry lock
		Before_Entry;

		
		m_Lisceners.push_back(liscener);

		//before leaving unlock
		Before_Leaving;
		return;
	}

	void EventProducer::PollEvents(void) { // must be a thread safe method
		// before entry lock
		Before_Entry;

		//check all available lisceners for each event
		for (int i = m_EventsCount - 1; i >= 0; i--) {
			for (int j = 0; j < m_Lisceners.size(); j++) {
				
				if ((m_Lisceners[j]->IsActive()) ) if  (m_Lisceners[j]->HandleEvent(m_Events[i])) break; 
				// event is served from this Liscener
			} // --TODO : Make priorities
			//event always deleted and removed after
			delete m_Events[i];
			m_Events[i] = nullptr;
		}

		m_EventsCount = m_CurrentEvent = 0;

		Before_Leaving;
		return;
	}

	void EventProducer::EmptyEvents(void) {
		Before_Entry;

		for (int i = 0; i < m_EventsCount; i++) {
			if (m_Events[i])
				delete m_Events[i];
		}
		m_EventsCount = m_CurrentEvent = 0;

		Before_Leaving;
	}
}