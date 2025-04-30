#pragma once
#include "../Core.hpp"

namespace JSGraphicsEngine3D {
	DWORD CALLBACK ThreadEntry(
		_In_ LPVOID lpParameter // this parameter will have a pointer to the current thread that is currently called
	);
	class Thread {

	private:
		Thread(void); // A Thread must always created on data segments (Initiallized or not ==> like heap section
		// making the constructor and destructor private this behavor is forced to the user
		~Thread(void);
	public:
		

		virtual void OnStart(void) noexcept;
		// When the thread is first created
		virtual void OnLoop(void) noexcept ;
		// When the thread is running
		virtual void OnStop(void) noexcept ;
		// When the thread is stop (cause from other thread )
		virtual void OnRestart(void) noexcept ;
		// when the thread is comming from a stop state
		virtual void OnDestroy(void) noexcept ;
		// when the thread is destroyed 
	public:
		static Thread*	CreateThread(void); // allocates the thread in the heap 
		static void		DestroyThread(Thread** thread);// free's the thread from the heap
		static void		StopThread(Thread& thread); // Stop Execution of the new thread
		static void		StartThread(Thread& thread);// Resumes the execution of a stopped thread
	private:
		HANDLE		m_ThreadHandle;
		LPDWORD		m_ThreadId;
		bool		m_KeepRunning;
		bool        m_Stop;

	private: // friend functions
		friend DWORD CALLBACK ThreadEntry(
			_In_ LPVOID lpParameter // this parameter will have a pointer to the current thread that is currently called
		); // make this thread entry point to have access to private members of this class

	
	};

	


}