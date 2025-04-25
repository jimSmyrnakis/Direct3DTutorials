#include "Error.hpp"
#include <string>
namespace JSGraphicsEngine3D {
	Logger* AppI = new Logger();
	Logger* AppW = new Logger();
	Logger* AppE = new Logger();
	Logger* CoreI = new Logger();
	Logger* CoreW = new Logger();
	Logger* CoreE = new Logger();
	Logger* UserI = new Logger();
	Logger* UserW = new Logger();
	Logger* UserE = new Logger();

	Logger& GetCoreInfoLogger(void) {
		return *CoreI;
	}
	Logger& GetCoreWarnLogger(void) {
		return *CoreW;
	}
	Logger& GetCoreErroLogger(void) {
		return *CoreE;
	}

	Logger& GetAppInfoLogger(void) {
		return *AppI;
	}
	Logger& GetAppWarnLogger(void) {
		return *AppW;
	}
	Logger& GetAppErroLogger(void) {
		return *AppE;
	}

	Logger& GetUserInfoLogger(void) {
		return *UserI;
	}
	Logger& GetUserWarnLogger(void) {
		return *UserW;
	}
	Logger& GetUserErroLogger(void) {
		return *UserE;
	}

	const char* GetErrorCodeWindowsMessage(HRESULT hresult) {
		char* buffer = nullptr;
		DWORD length = FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			hresult,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&buffer,
			0, nullptr

		);

		if (length == 0)
			return "Undefine Description ";

		char* err = new char[length + 1];
		err[length] = '\0';
		strcpy_s(err, length, buffer);
		LocalFree(buffer);
		return err;


	}
}