#pragma once
#include "../Core.hpp"
#include <string>
#include <exception>

namespace JSGraphicsEngine3D {

	class JSException : public std::exception{
	public:
		JSException(const char* file , uint32_t line) noexcept;
		~JSException(void) noexcept;

		virtual char const* what(void) const noexcept override;
        virtual const char* type(void) const noexcept;
		        uint32_t    line(void) const noexcept;
		        const char* file(void) const noexcept;
		virtual std::string msg (void) const noexcept;
	private:
		char*		m_file;
		uint32_t	m_line;
	protected:
		mutable std::string m_WhatBuffer;
	};
}