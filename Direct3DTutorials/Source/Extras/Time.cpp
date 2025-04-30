#include "Time.hpp"
#include <chrono>

namespace JSGraphicsEngine3D {



	Time::Time(void) {
		m_Mutex = Mutex::Create();
		m_StartTime =  (float)GetTickCount64();
	}

	Time::~Time(void) {
		Mutex::Destroy(m_Mutex);
	}

	Time* Time::Create(void) {
		Time* tim = new Time;
		JS_CORE_ASSERT(tim, JS_ERROR_NO_MEMORY, "Out Of memory , Can't allocate space for Time variable");
		return tim;
	}
	void  Time::Destroy(Time* ptr) {
		if (ptr) {
			delete ptr;
		}
	}
	float Time::GetTime(void) const {
		m_Mutex->Lock();
		float difference = m_StartTime - (float)GetTickCount64();
		m_Mutex->Unlock();
		// ensures safety even if GetTickCount64 is not
		return difference * 1000;

	}
}