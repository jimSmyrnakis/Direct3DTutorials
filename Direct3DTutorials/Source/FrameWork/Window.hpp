#pragma once
#include "../Core.hpp"
#include <string>
#include "EventSystem/EventProducer.hpp"
#include <memory>
namespace JSGraphicsEngine3D {
	class Window {

	
		
	public: /* We will handle the windows created with one Window Class */
		class WindowClass {
		public:
			static wchar_t* GetName(void);
			static HINSTANCE GetHInstance(void);
			
		private:
			WindowClass(void);
			~WindowClass(void);
			WindowClass(const WindowClass& copy) = delete;
			WindowClass& operator=(const WindowClass& copy) = delete;

			static WindowClass* WindowClassThis;

			HINSTANCE hinstance;

		};

	public:
		Window(void);
		Window( uint16_t width , uint16_t height ,const wchar_t* title);
		
		~Window(void);
		EventProducer& GetEventProducer(void) const ;

		Window(const Window& copy) = delete;
		Window& operator=(const Window& copy) = delete;

		HWND GetId(void) const ;

		uint32_t GetWidth(void) const;
		uint32_t GetHeight(void) const;


		bool PollEvents(void);
		// return false if the window close 

	private:
		int m_width;
		int m_height;
		HWND m_hwnd;
		EventProducer* m_EventProducer;
		
		MSG* msg;
		

	private: /*Event call backs function */
		static LRESULT CALLBACK HandleMsgSetUp(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK HandleMsgThunk(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam);
		LRESULT MessageEventsHandle(HWND hwnd, UINT msgCode, WPARAM wParam, LPARAM lParam); // this method actually handles the message events of this window 

	};


}