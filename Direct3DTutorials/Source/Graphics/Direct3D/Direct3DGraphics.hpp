#pragma once
#include "../../Core.hpp"
#include "../../FrameWork/Window.hpp"
#include <d3d11.h>
namespace JSGraphicsEngine3D {
	class Direct3DGraphics {
	private:
		Direct3DGraphics(Window* win);
		~Direct3DGraphics(void);

		Direct3DGraphics(const Direct3DGraphics& cp) = delete;
		Direct3DGraphics& operator=(const Direct3DGraphics& cp) = delete;


	public:

		void ClearBuffer(float rgba[4]);
		void SwapBuffers(void) const;

		void DrawTriangle(void);

	public :
		static Direct3DGraphics* Create(Window* win);
		static void Destroy(Direct3DGraphics* ptr);
	private:
		ID3D11Device*			m_DevicePtr;
		IDXGISwapChain*			m_SwapChain;
		ID3D11DeviceContext*	m_Context;
		ID3D11RenderTargetView* m_RenderTargetView;
		 
	};
}