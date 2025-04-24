#pragma once
#include "../Core.hpp"
#include <string>
#include "../ErrorHandling/JSException.hpp"
#include "EventSystem/EventProducer.hpp"
namespace JSGraphicsEngine3D {
	class Window {

	public:
		class Exception : public JSException {
		public:
			Exception(const char* file, uint32_t line, HRESULT hreult);

			virtual const char* type(void) const noexcept override;
			virtual std::string msg (void) const noexcept override;

			static std::string TranslateErrorCode(HRESULT hresult) noexcept;
			HRESULT GetErrorCode(void) const noexcept;
			std::string GetErrorString(void) const noexcept;
		private:
			HRESULT m_hresult;
		};
		
	private: /* We will handle the windows created with one Window Class */
		class WindowClass {
		public:
			static const wchar_t* GetName(void);
			static HINSTANCE GetHInstance(void);
			
		private:
			WindowClass(void);
			~WindowClass(void);
			WindowClass(const WindowClass& copy) = delete;
			WindowClass& operator=(const WindowClass& copy) = delete;

			static const wchar_t* Name;// = L"JSGraphicsEngine3D";
			static WindowClass* WindowClassThis;

			HINSTANCE hinstance;

		};

	public:
		Window( uint16_t width = 640 , uint16_t height = 320 ,const wchar_t* title = L"GraphicsEngine3D");
		~Window(void);
		EventProducer* GetEventProducer(void) const noexcept;
		Window(const Window& copy) = delete;
		Window& operator=(const Window& copy) = delete;

		HWND GetId(void) const noexcept;

	private:
		int m_width;
		int m_height;
		HWND m_hwnd;
		EventProducer* m_EventProducer;

		

	private: /*Event call backs function */
		static LRESULT CALLBACK HandleMsgSetUp(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandleMsgThunk(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam);
		LRESULT MessageEventsHandle(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam); // this method actually handles the message events of this window 

	};

#define JSWindowError(hr_code)  JSGraphicsEngine3D::Window::Exception(__FILE__,__LINE__,hr_code)
#define JSWindowLastError  JSGraphicsEngine3D::Window::Exception(__FILE__,__LINE__,GetLastError())

}