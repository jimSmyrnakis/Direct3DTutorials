#pragma once
#include "../../EventSystem/EventLiscener.hpp"
#include "../../Events/EventMouseKeyPressed.hpp"
#include "../../Events/EventMouseKeyReleased.hpp"
#include "../../Events/EventMouseMoved.hpp"
#include "../../Events/EventMouseDoubleClick.hpp"
#include "../../Events/EventMouseLeave.hpp"

namespace JSGraphicsEngine3D {
	class Button : public EventLiscener {
	public:
		Button(uint16_t x , uint16_t y , uint16_t width , uint16_t height , std::shared_ptr<Window>& pWindow );
		~Button(void) = default;

		virtual bool HandleEvent(const Event* event) override;

		virtual void Click(EventMouseKeyPressed* e);
		virtual void DoubleClick(EventMouseDoubleClick* e);
		virtual void Released(EventMouseKeyReleased* e);
		virtual void MouseMoved(EventMouseMoved* e);
		virtual void OnCapture(EventMouseMoved* e);
		void TrollMe(void);


		Button(const Button& copy) = delete;
		Button& operator=(const Button& copy) = delete;

	private:
		uint16_t m_PosX;
		uint16_t m_PosY;
		uint16_t m_Width;
		uint16_t m_Height;
		std::shared_ptr<Window> m_Window;
		HWND    m_hwnd;
	private:
		bool IsInRect(int16_t, int16_t);
	};
}