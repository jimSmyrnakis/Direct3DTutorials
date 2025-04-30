#pragma once
#include "../Core.hpp"

namespace JSGraphicsEngine3D {
	class Mutex {
	private:
		Mutex(void);
		~Mutex(void);
		Mutex(const Mutex& cp) = delete;
		Mutex& operator=(const Mutex& cp) = delete;

	public://static methods

		static Mutex* Create(void); // Creates a Mutex on the heap for security reasons only this method can be called
		static void Destroy(Mutex* ptr); // Deletes the mutex from the heap
	
	public:

		void Lock(void);  //  lock the mutex if is not locked for entering the critical section , otherwise waits until is free to lock it again 
		bool TryLock(void); // same as Lock but only if returns true , prevents a waiting stage

		void Unlock(void); // unlocks the mutex

	private:
		LPCRITICAL_SECTION	m_Critical; // pointer to the critical section object 
		// good with critical section is the spin count , spin count ensures that 
		// when it tries to lock the critical section object it does it with cpu
		// instuctions per spin . When no loger spin exists then calls kernel
		
	};
}