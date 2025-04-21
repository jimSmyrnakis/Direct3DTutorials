#pragma once
#include "../Core.hpp"
#include <string>
namespace JSGraphicsEngine3D {
	class Window {
		
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
		
		Window(const Window& copy) = delete;
		Window& operator=(const Window& copy) = delete;

	private:
		int m_width;
		int m_height;
		HWND m_hwnd;

	private: /*Event call backs function */
		static LRESULT CALLBACK HandleMsgSetUp(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandleMsgThunk(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam);
		LRESULT MessageEventsHandle(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam); // this method actually handles the message events of this window 

	};
}