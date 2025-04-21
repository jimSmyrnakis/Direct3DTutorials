#include "JSException.hpp"
#include <sstream>
namespace JSGraphicsEngine3D {

	JSException::JSException(const char* file, uint32_t line) noexcept : std::exception() {
		m_file = (char*)file;
		m_line = line;
	}
	JSException::~JSException(void) noexcept {

	}

	char const* JSException::what(void) const noexcept {
		std::stringstream ss;
		ss << "{ [ type : " << type() << "] [ message : " << "\"" << msg() << "\" ]";

	    ss << " [Line : " << line() << "] [ File : " << "\"" << file() << "\" ] } " << std::endl;
		m_WhatBuffer = ss.str();
		return m_WhatBuffer.c_str();
	}
	static const char* ExType = "Generic JSException Type";
	const char* JSException::type(void) const noexcept {
		return ExType;
	}
	uint32_t    JSException::line(void) const noexcept {
		return m_line;
	}
	const char* JSException::file(void) const noexcept {
		return m_file;
	}

	std::string JSException::msg(void) const noexcept {
		return std::string("Generic JSException");
	}


}