#include "EventLiscener.hpp"

#define Before_Entry {\
	DWORD res = WaitForSingleObject(m_Mutex, INFINITE); \
	JS_CORE_ASSERT(res == WAIT_OBJECT_0 , JS_ERROR_BAD_MUTEX , "Bad Mutex State !!!" );\
} 

#define Before_Leaving { \
	BOOL check = ReleaseMutex(m_Mutex); \
	JS_CORE_ASSERT(check != FALSE , JS_ERROR_BAD_MUTEX , "Bad Mutex State !!!")\
}

namespace JSGraphicsEngine3D {

	EventLiscener::EventLiscener(Window* pWindow) {

		//Create a mutex for thread synchronization (Handle is already a pointer )
		m_Mutex = CreateMutexW(nullptr, FALSE, nullptr);
		JS_CORE_ASSERT(m_Mutex != nullptr, JS_ERROR_CANT_CREATE_MUTEX, "Can't Create mutex object !!!");
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