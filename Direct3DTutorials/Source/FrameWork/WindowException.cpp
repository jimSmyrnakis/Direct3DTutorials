#include "Window.hpp"
#include <sstream>

namespace JSGraphicsEngine3D {

	Window::Exception::Exception(const char* file, uint32_t line , HRESULT hresult) : JSException(file,line){
		m_hresult = hresult;
	}

	
	static const char* ExName = "JSWindow Exception";

	const char* Window::Exception::type(void) const noexcept {
		return ExName;
	}

	std::string Window::Exception::msg(void) const noexcept {
		std::stringstream ss;
		ss << "# Error code ==> " << GetErrorCode() << std::endl;
		ss << "# Error Description ==> " << GetErrorString() << std::endl;
		return ss.str();
	}

	HRESULT Window::Exception::GetErrorCode(void) const noexcept {
		return m_hresult;
	}

	std::string Window::Exception::GetErrorString(void) const noexcept {
		return TranslateErrorCode(m_hresult);
	}

	std::string Window::Exception::TranslateErrorCode(HRESULT hresult) noexcept {
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

		std::string err = buffer;
		LocalFree(buffer);
		return err;
		

	}



















}
