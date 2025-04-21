#include "EventLiscener.hpp"

#define Before_Entry { \
    DWORD res = WaitForSingleObject(m_Mutex, INFINITE); \
	if (res != WAIT_OBJECT_0) {\
			throw JSWindowLastError; \
	}\
} 

#define Before_Leaving { \
	BOOL check = ReleaseMutex(m_Mutex); \
	if (check == FALSE) { \
		throw JSWindowLastError; \
	} \
}

namespace JSGraphicsEngine3D {
	EventLiscener::EventLiscener(Window* pWindow) {

		//Create a mutex for thread synchronization (Handle is already a pointer )
		m_Mutex = CreateMutexA(nullptr, FALSE, nullptr);
		if (m_Mutex == NULL) {
			throw JSWindowLastError;
		}
		m_Active = true;
		m_Window = pWindow;
		// add me to the liscener list of the pWindow Event Producer
		m_Window->GetEventProducer()->AddLiscener(this);

	}
	EventLiscener::~EventLiscener(void) {
		CloseHandle(m_Mutex);
	}
	bool EventLiscener::IsActive(void) const {
		Before_Entry;
		bool takeVal = m_Active;
		Before_Leaving;
		return takeVal;
	}
	void EventLiscener::SetActive(bool active) {
		Before_Entry;
		m_Active = active;
		Before_Leaving;
	}

}