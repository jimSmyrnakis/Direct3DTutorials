#include "Logger.hpp"
#include <vector>
#include <string>
#include <sstream>

namespace JSGraphicsEngine3D{
#define JSMSG (*(std::vector<std::string>*)m_Messages)
	Logger::Logger(void) {
		m_Size = 0;
		m_Messages = new std::vector<std::string>();

		//Create a mutex for thread synchronization (Handle is already a pointer )
		m_Mutex = CreateMutexA(nullptr, FALSE, nullptr);
		if (m_Mutex == NULL) {
			MessageBoxA(nullptr, "Can't Create Mutex Object", "Core Fatal !!!", MB_OK | MB_ICONEXCLAMATION);
			ExitProcess(1234);//(1234);
		}
		
	}

	Logger::~Logger(void) {
		if (m_Messages) {
			
			//while (JSMSG.size()){
			//	std::string *ptr = JSMSG.back();
			//	if (ptr)
			//		delete ptr;
				//JSMSG.pop_back();
			//}
			//JSMSG.clear();
			delete m_Messages;
		}
		CloseHandle(m_Mutex);
		
	}

#define Before_Entry //WaitForSingleObject(m_Mutex, INFINITE)

#define Before_Leaving // ReleaseMutex(m_Mutex) 


	void Logger::PushMessage(int errorCode, const char* type, const char* file, int line , const char* msg) {
		Before_Entry;
		std::stringstream ss;
		ss << "{ [ Error Code : " << errorCode << " ] [Type:" << type << "] ";
		ss << "[ Line : " << line << " ] [ File : \"" << file << "\"] [ Message: \"" << msg << "\" ] }" << std::endl;
		JSMSG.push_back(std::string(ss.str()));
		m_Size++;
		Before_Leaving;
	}

	bool Logger::PopMessage(void) {
		Before_Entry;
		if (JSMSG.size() == 0)
			return false;

		
		JSMSG.pop_back();
		m_Size--;
		Before_Leaving;
		return true;
	}

	const char* Logger::GetLastMessage(void) const {
		Before_Entry;
		if (JSMSG.size() == 0) 
			return nullptr;
		
		std::string* ref = new std::string(JSMSG[m_Size - 1]);
		Before_Leaving;
		return ref->c_str();

	}

	uint32_t Logger::GetMessageCount(void) const {
		return m_Size;
	}




}