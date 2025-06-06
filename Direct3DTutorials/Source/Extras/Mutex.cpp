#include "Mutex.hpp"
#define JS_SPIN_COUNT 4000
namespace JSGraphicsEngine3D {
	Mutex::Mutex(void) {
		m_Critical = new CRITICAL_SECTION;
		JS_CORE_ASSERT(m_Critical != nullptr, JS_ERROR_NO_MEMORY,
			"Out of memory , can't allocate critical section object !!!");
		JS_WINCHECK_FATAL(InitializeCriticalSectionAndSpinCount(m_Critical, JS_SPIN_COUNT));
		
	}
	Mutex::~Mutex(void) {
		if (m_Critical) {
			JS_WINCHECK(DeleteCriticalSection(m_Critical));
		}
			
	}

	void Mutex::Lock(void) {
		JS_WINCHECK(EnterCriticalSection(m_Critical));
	}
	bool Mutex::TryLock(void) {
		bool isLocked;
		JS_WINCHECK(isLocked = (TryEnterCriticalSection(m_Critical) == TRUE));
		return isLocked;
	}

	void Mutex::Unlock(void) {
		JS_WINCHECK(LeaveCriticalSection(m_Critical));
	}

	Mutex* Mutex::Create(void) {
		Mutex* mut = new Mutex;
		JS_CORE_ASSERT(mut != nullptr, JS_ERROR_NO_MEMORY, "Out of memory , mutex can't allocated !!!");
		return mut;
	}
	void Mutex::Destroy(Mutex* ptr) {
		if (ptr)
			delete ptr;
	}
}