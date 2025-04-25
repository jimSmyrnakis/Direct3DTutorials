#pragma once
#include "../Logger/Logger.hpp"

namespace JSGraphicsEngine3D {
	Logger& GetCoreInfoLogger(void);
	Logger& GetCoreWarnLogger(void);
	Logger& GetCoreErroLogger(void);

	Logger& GetAppInfoLogger(void);
	Logger& GetAppWarnLogger(void);
	Logger& GetAppErroLogger(void);

	Logger& GetUserInfoLogger(void);
	Logger& GetUserWarnLogger(void);
	Logger& GetUserErroLogger(void);



	const char* GetErrorCodeWindowsMessage(HRESULT hresult);





};

#ifdef __JSDEBUG__
	#define js_break(user_code) __debugbreak()
#elif defined(__JSRELEASE__)
	#define js_break(user_code) 
#elif defined(__JSDIST__) 
	#define js_break(user_code) ExitProcess(user_code)
#endif

#define JS_CORE_INFO(  message)  { \
	GetCoreInfoLogger().PushMessage(0, "Core Info", __FILE__ , __LINE__ , message);\
	MessageBoxA(nullptr,GetCoreInfoLogger().GetLastMessage() , "Core", MB_OK | MB_ICONEXCLAMATION);\
	GetCoreInfoLogger().PopMessage();\
}

#define JS_CORE_WARN(warnCode  , message)  { \
	GetCoreWarnLogger().PushMessage(warnCode, "Core Warning", __FILE__ , __LINE__ , message);\
	MessageBoxA(nullptr,GetCoreInfoLogger().GetLastMessage() , "Core", MB_OK | MB_ICONEXCLAMATION);\
	GetCoreWarnLogger().PopMessage();\
}

#define JS_CORE_ERROR(errorCode  , message)  { \
	GetCoreErroLogger().PushMessage(errorCode, "Core Error", __FILE__ , __LINE__ , message);\
	MessageBoxA(nullptr,GetCoreInfoLogger().GetLastMessage() , "Core", MB_OK | MB_ICONEXCLAMATION);\
	GetCoreErroLogger().PopMessage();\
	js_break(1);\
}





#define JS_APP_INFO(  message)  { \
	GetAppInfoLogger().PushMessage(0, "App Info", __FILE__ , __LINE__ , message);\
	MessageBoxA(nullptr,GetCoreInfoLogger().GetLastMessage() , "App", MB_OK | MB_ICONEXCLAMATION);\
	GetAppInfoLogger().PopMessage();\
}

#define JS_APP_WARN(warnCode  , message)  { \
	GetAppWarnLogger().PushMessage(warnCode, "App Warning", __FILE__ , __LINE__ , message);\
	MessageBoxA(nullptr,GetCoreInfoLogger().GetLastMessage() , "App", MB_OK | MB_ICONEXCLAMATION);\
	GetAppWarnLogger().PopMessage();\
}

#define JS_APP_ERROR(errorCode  , message)  { \
	GetAppErroLogger().PushMessage(errorCode, "App Error", __FILE__ , __LINE__ , message);\
	MessageBoxA(nullptr,GetCoreInfoLogger().GetLastMessage() , "App", MB_OK | MB_ICONEXCLAMATION);\
	GetAppErroLogger().PopMessage();\
	js_break(1);\
}






#define JS_USER_INFO(  message)  { \
	GetUserInfoLogger().PushMessage(0, "User Info", __FILE__ , __LINE__ , message);\
	MessageBoxA(nullptr,GetCoreInfoLogger().GetLastMessage() , "User", MB_OK | MB_ICONEXCLAMATION);\
	GetUserInfoLogger().PopMessage();\
}

#define JS_USER_WARN(warnCode  , message)  { \
	GetUserWarnLogger().PushMessage(warnCode, "User Warning", __FILE__ , __LINE__ , message);\
	MessageBoxA(nullptr,GetCoreInfoLogger().GetLastMessage() , "User", MB_OK | MB_ICONEXCLAMATION);\
	GetUserWarnLogger().PopMessage();\
}

#define JS_USER_ERROR(errorCode  , message)  { \
	GetUserErroLogger().PushMessage(errorCode, "User Error", __FILE__ , __LINE__ , message);\
	MessageBoxA(nullptr,GetCoreInfoLogger().GetLastMessage() , "User", MB_OK | MB_ICONEXCLAMATION);\
	GetUserErroLogger().PopMessage();\
	js_break(1);\
}



