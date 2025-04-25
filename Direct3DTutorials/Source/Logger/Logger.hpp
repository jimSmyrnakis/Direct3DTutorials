#pragma once
#include "../JSWin.hpp"
#include <stdint.h>
#include <stddef.h>

namespace JSGraphicsEngine3D {
	class Logger {

	public:
		Logger(void);
		~Logger(void);
		Logger(const Logger& cp) = delete;



		void PushMessage(int errorCode , const char* type ,const char* file , int line , const char* message);
		bool PopMessage(void);

		const char* GetLastMessage(void) const;
	
		uint32_t GetMessageCount(void) const;


		

		Logger& operator=(const Logger& cp) = delete;
	private:
		void*    m_Messages;
		uint32_t m_Size;
		HANDLE   m_Mutex;


	};
}