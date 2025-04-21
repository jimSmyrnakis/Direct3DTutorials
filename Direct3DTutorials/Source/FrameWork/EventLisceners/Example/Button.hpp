#include "../../EventSystem/EventLiscener.hpp"

namespace JSGraphicsEngine3D {
	class Button : public EventLiscener {
	public:
		Button(uint16_t x , uint16_t y , uint16_t width , uint16_t height , Window* pWindow);
		~Button(void) = default;

		virtual bool HandleEvent(const Event* event) override;

		virtual void ButtonClick(void);
		virtual void ButtonReleased(void);


		Button(const Button& copy) = delete;
		Button& operator=(const Button& copy) = delete;

	private:
		uint16_t m_PosX;
		uint16_t m_PosY;
		uint16_t m_Width;
		uint16_t m_Height;
	private:
		bool IsInRect(uint16_t, uint16_t);
	};
}