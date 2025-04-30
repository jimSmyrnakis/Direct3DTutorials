#include "Thread.hpp"

namespace JSGraphicsEngine3D {
	DWORD CALLBACK ThreadEntry(
		_In_ LPVOID lpParameter // this parameter will have a pointer to the current thread that is currently called
	) {
		Thread* thisThread = (Thread*)lpParameter;
		// call the first time this method
		thisThread->OnStart();

		//after start executing the loop method in a while true loop
		while (true) thisThread->OnLoop();


		return 0;
	}
	Thread::Thread() {


		m_ThreadId = new DWORD;
		if (m_ThreadId == nullptr) {
			JS_CORE_ASSERT(0, JS_ERROR_NO_MEMORY, "Can't Allocate space for the thread indentifier !!!");
			ExitProcess(JS_ERROR_NO_MEMORY); // force quit
		}


		m_ThreadHandle = ::CreateThread(
			nullptr, //default security attributes
			0, // Use the default stack size
			ThreadEntry, // Thread entry point
			this, // A pointer to this thread class
			CREATE_SUSPENDED, // Do not start running this thread yet
			m_ThreadId
		);
		JS_CORE_WINDOWS_ASSERT(m_ThreadHandle);
		if (m_ThreadHandle) {
			ExitProcess(1); // force quit
		}

		m_Stop = true;
		m_KeepRunning = true;



	}
	Thread::~Thread() {

		if (m_ThreadId)
			delete m_ThreadId;
		CloseHandle(m_ThreadHandle);
		
	}

	Thread* Thread::CreateThread(void) {
		return new Thread();
	}

	void Thread::DestroyThread(Thread** thread) {

		delete *thread;
		*thread = nullptr;
	}

	void Thread::StopThread(Thread& thread) {
		SuspendThread(thread.m_ThreadHandle);
	}

	void Thread::StartThread(Thread& thread) {
		ResumeThread(thread.m_ThreadHandle);
	}
}