#pragma once

#include "../Core.hpp"
#include <stdio.h>

namespace JSGraphicsEngine3D {
	class Logger {
	public:
		enum class Type {
			Error,
			Fatal,
			Warning,
			Info
		};
	public:
		static void PrintMessage(
			Type        type,
			const char* who, // Core , App etc.
			const char* from, // OpenGL , Direct3D , Core , App Etc.
			const char* msg, // What message
			const char* file, // from what file (.cpp) is
			uint32_t    line, // in what line 
			uint32_t    code   // what type of error , warning code ?
		);

		// Prints The Message to the system using the system output (here is Message Boxe's of windows
		// although not the best approach , is something for now . In future better desition is to use 
		// a console for output warning's and info , but still errors and fatals are going to be Message
		// Boxe's

		// Another thing that must be solved is when the process exits it must call all system's OnDestroy 
		// method so finallize of the application in the current state be right and have no file losses and
		// bad things in general
	};

	// prints to the system the 

	char* GetFormatedText(const char* format, ...);

	char* GetLastWindowsMessage(void);

}

#if defined(__JSDEBUG__) 
	#define js_break(exitCode) __debugbreak()
#elif defined(__JSRELEASE__) || defined(__JSDIST__)
	#define js_break(exitCode) ExitProcess(exitCode)
#else 
	#error must define debug , release or dist mode !!!
#endif

#define JS_ERROR(who , from , msg , errorcode ) {\
	Logger::PrintMessage(Logger::Type::Error , who , from , msg  , __FILE__ , __LINE__ , errorcode   );\
	js_break(errorcode);\
}

#define JS_FATAL(who , from , msg , fatalcode) {\
	Logger::PrintMessage(Logger::Type::Fatal , who , from , msg  , __FILE__ , __LINE__ , fatalcode   );\
	ExitProcess(fatalcode);\
}
// don't break on warning's , keep going 
#define JS_WARN(who , from , msg , warncode) {\
	Logger::PrintMessage(Logger::Type::Warning , who , from , msg  , __FILE__ , __LINE__ , warncode   );\
}

// ofcourse just print message
#define JS_INFO(who , from , msg ) {\
	Logger::PrintMessage(Logger::Type::Info , who , from , msg  , __FILE__ , __LINE__ , 0   );\
}

#define JS_CORE_ERROR(msg , code ) JS_ERROR("Core"  , "Core" , msg , code)
#define JS_APP_ERROR(msg , code )  JS_ERROR("App"  , "App" , msg , code)

#define JS_CORE_FATAL(msg , code ) JS_FATAL("Core"  , "Core" , msg , code)
#define JS_APP_FATAL(msg , code ) JS_FATAL("App"  , "App" , msg , code)

#define JS_CORE_WARN(msg , code ) JS_WARN("Core"  , "Core" , msg , code)
#define JS_APP_WARN(msg , code ) JS_WARN("App"  , "App" , msg , code)

#define JS_CORE_INFO(msg  ) JS_INFO("Core"  , "Core" , msg )
#define JS_APP_INFO(msg  ) JS_INFO("App"  , "App" , msg )

#define JS_CORE_ASSERT(cond , ErrorCode , ... ) if (!(cond)) { \
	JS_CORE_ERROR(JSGraphicsEngine3D::GetFormatedText( __VA_ARGS__ ) , ErrorCode);\
}
#define JS_CORE_ASSERT_FATAL(cond , ErrorCode , ... ) if (!(cond)) { \
	JS_CORE_FATAL(JSGraphicsEngine3D::GetFormatedText( __VA_ARGS__ ) , ErrorCode);\
}

#define JS_APP_ASSERT(cond , ErrorCode , ... ) if (!(cond)) { \
	JS_APP_ERROR(JSGraphicsEngine3D::GetFormatedText( __VA_ARGS__ ) , ErrorCode);\
}
#define JS_APP_ASSERT_FATAL(cond , ErrorCode ,  ... ) if (!(cond)) { \
	JS_APP_FATAL(JSGraphicsEngine3D::GetFormatedText( __VA_ARGS__ ) , ErrorCode);\
}

#define JS_WINCHECK(function) { \
	SetLastError(0);\
	(function);\
	if (GetLastError() != ERROR_SUCCESS){ \
		char* msg = GetLastWindowsMessage(); \
		JS_CORE_ERROR(msg , GetLastError()); \
	} \
}

#define JS_WINCHECK_FATAL(function) { \
	SetLastError(0);\
	(function);\
	if (GetLastError() != ERROR_SUCCESS){ \
		char* msg = GetLastWindowsMessage(); \
		JS_CORE_FATAL(msg , GetLastError()); \
	} \
}







