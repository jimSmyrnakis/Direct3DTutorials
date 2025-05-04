#include "Error.hpp"
#include <string>
#include <sstream>
#include <ostream>//
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


namespace JSGraphicsEngine3D {
	void Logger::PrintMessage(
		Type        type,
		const char* who, // Core , App etc.
		const char* from, // OpenGL , Direct3D , Windows , Core , App Etc.
		const char* msg, // What message
		const char* file, // from what file (.cpp) is
		uint32_t    line, // in what line 
		uint32_t    code   // what type of error , fatal , warning code ?
	) {
		std::stringstream ss;
		ss << "[ Message From : " << from << " ] " << std::endl;
		ss << "[ File : " << file << " ] " << std::endl;
		ss << "[ Line : " << line << " ] " << std::endl;
		UINT boxType = 0;
		switch (type) {
		case Type::Error:
			boxType |= MB_ICONERROR;
#ifdef __JSDIST__
			std::string s = "Error Code : ";
			s += code;
			MessageBoxA(nullptr, s.c_str(), who, boxType);
			ExitProcess(code);
#endif
			ss << "[ Error Code : " << code << " ]" << std::endl;
			break;
		case Type::Fatal:
			boxType |= MB_ICONSTOP;
#ifdef __JSDIST__
			std::string s = "Fatal Code : ";
			s += code;
			MessageBoxA(nullptr, s.c_str(), who, boxType);
			ExitProcess(code);
#endif	
			ss << "[ Fatal Code : " << code << " ]" << std::endl;
			break;
		case Type::Warning:
			boxType |= MB_ICONWARNING;
#ifdef __JSDIST__ // in warning do nothing if you are in dist mode , end user doesn't have any releation with it
			retrun;
#endif	
			ss << "[ Warning Code : " << code << " ]" << std::endl;
			break;
		case Type::Info:
#ifdef __JSDIST__ // in warning do nothing if you are in dist mode , end user doesn't have any releation with it
			retrun;
#endif	
			boxType |= MB_ICONINFORMATION;

			break;
		}

		ss << "[ Message : {" << msg << "} ]" << std::endl;

		::MessageBoxA(nullptr, ss.str().c_str(), who, boxType);

	}

	char* GetFormatedText(const char* format, ...) {
		va_list args;
		va_start(args, format);

		// Υπολογισμός μεγέθους για την μορφοποιημένη συμβολοσειρά
		int size = vsnprintf(NULL, 0, format, args);
		va_end(args);

		if (size < 0) {
			return NULL; // Σφάλμα κατά τη μορφοποίηση
		}

		// Δέσμευση μνήμης για το αποτέλεσμα (+1 για τον '\0')
		char* buffer = (char*)malloc(size + 1);
		if (!buffer) {
			return NULL; // Αποτυχία δέσμευσης μνήμης
		}

		// Δημιουργία μορφοποιημένου κειμένου
		va_start(args, format);
		vsnprintf(buffer, size + 1, format, args);
		va_end(args);

		return buffer;
	}

	char* GetLastWindowsMessage(void) {
		DWORD errorCode = GetLastError();
		if (errorCode == 0) {
			return NULL; // Δεν υπάρχει σφάλμα
		}

		char* messageBuffer = NULL;

		size_t size = FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			errorCode,
			0, // default language
			(LPSTR)&messageBuffer,
			0,
			NULL
		);

		if (size == 0 || messageBuffer == NULL) {
			return NULL; // Αποτυχία λήψης μηνύματος
		}

		// Αντιγραφή σε buffer που μπορεί να χειριστεί ο χρήστης
		char* result = (char*)malloc(size + 1);
		if (result) {
			memcpy(result, messageBuffer, size + 1);
		}

		LocalFree(messageBuffer); // Ελευθέρωση buffer από FormatMessage
		return result; // Ο χρήστης πρέπει να καλέσει free()
	}

	
}