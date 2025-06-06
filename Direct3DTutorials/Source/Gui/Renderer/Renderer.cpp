#include "Renderer.hpp"
#include "wgl/include/glad/glad_wgl.h"
#include "../../FrameWork/Window.hpp"
#include "ErrorInfo.hpp"
#pragma comment (lib ,"opengl32.lib" )
namespace JSGraphicsEngine3D {
	namespace Gui {
		static void CreateModernOpenGLContext(HWND hwnd, HDC* hdc, HGLRC* modernContext) {




			(*hdc) = GetDC(hwnd);

			// 1 specify window context format description 
			PIXELFORMATDESCRIPTOR pfd =
			{

				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
				PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
				32,                   // Colordepth of the framebuffer.
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				24,                   // Number of bits for the depthbuffer
				8,                    // Number of bits for the stencilbuffer
				0,                    // Number of Aux buffers in the framebuffer.
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			};

			// 2. Translate Format from opengl to windows
			int format = ChoosePixelFormat(*hdc, &pfd);
			JS_CORE_ASSERT(format, JS_ERROR_CANT_CONVERT_PIXELFORMAT, "Can't Convert pixel format for creating the desire opangl context ");

			// 3. Set that pixel format
			BOOL result = SetPixelFormat(*hdc, format, &pfd);
			JS_CORE_ASSERT(result, JS_ERROR_SET_PIXELFORMAT_FAILED, "SetPixelFormat failed");

			// 4. Create a dummy context
			HGLRC hglrc = wglCreateContext(*hdc);
			JS_CORE_ASSERT(hglrc, JS_ERROR_FAILED_CREATE_CONTEXT, "Failed to create OpenGL context !!!");

			// 5. Make dummy Context Current
			JS_CORE_ASSERT(wglMakeCurrent(*hdc, hglrc) != FALSE, JS_ERROR_FAILED_CREATE_CONTEXT, "Failed make dummy Context current !!!");


			// 6. Load wglCreateContextARB method from dll (opengl32.dll)
			PFNWGLCREATECONTEXTATTRIBSARBPROC MyCreateContext = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
				wglGetProcAddress("wglCreateContextAttribsARB");
			JS_CORE_ASSERT_FATAL(MyCreateContext, JS_ERROR_FAILED_CREATE_CONTEXT, "Can't Load wglCreateContextARB method");


			// 7. Define modern context attributes (At least 4.3 that supports tesselation )
			int attribs[] = {
				WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				WGL_CONTEXT_MINOR_VERSION_ARB, 3,
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	#if defined( __JSDEBUG__ ) || defined ( __JSRELEASE__ )
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
	#endif 
				0
			};

			// 8. Create modern OpenGL context 
			*modernContext = MyCreateContext(*hdc, 0, attribs);
			JS_CORE_ASSERT(*modernContext, JS_ERROR_NOT_SUPPORTED_OPENGL_VERSION, "Failed to create modern context with version OpenGL4.0 + ");

			// 9. Make none context current
			JS_CORE_ASSERT(wglMakeCurrent(nullptr, nullptr) != FALSE, JS_ERROR_FAILED_CREATE_CONTEXT, "Failed clear current contexts");

			// 10. Delete Dummy Context
			JS_CORE_ASSERT(wglDeleteContext(hglrc) != FALSE, JS_ERROR_FAILED_CREATE_CONTEXT, "Failed deleting dummy context");

			// 11. Make Modern Context current
			JS_CORE_ASSERT(wglMakeCurrent(*hdc, *modernContext) != FALSE, JS_ERROR_FAILED_CREATE_CONTEXT, "Failed make modern context as current");

			// 12. Load all Modern OpenGL methods
			if (!gladLoadGL()) {
				MessageBoxA(0, "Failed to load OpenGL functions", "Error", MB_ICONERROR);
				js_break(1);
			}



		}

		GuiRenderer::GuiRenderer(std::shared_ptr<Window>& win) {
			JS_CORE_ASSERT(win, JS_ERROR_NULL_PARAMETER, "win of the Graphics parameter is nullptr !!!");
			m_Window = win;
			CreateModernOpenGLContext(win->GetId(), &m_DeviceContext, &m_GLContext);
			m_Viewport = { 0,0,1080 , 720 };
			m_RenderFinish = true;
			m_Mutex = Mutex::Create();
#ifndef __JSDEBUG__
			return;
#endif
			const GLubyte* renderer = glGetString(GL_RENDERER);   // ����� (�.�. "NVIDIA GeForce GTX 1660")
			const GLubyte* vendor = glGetString(GL_VENDOR);     // ������������� (�.�. "NVIDIA Corporation")
			const GLubyte* version = glGetString(GL_VERSION);    // ������ OpenGL (�.�. "4.6.0 NVIDIA 537.13")
			const GLubyte* glslVer = glGetString(GL_SHADING_LANGUAGE_VERSION); // GLSL ������ (�.�. "4.60 NVIDIA")
			std::string info = "renderer : " + std::string((char*)renderer) + "\n";
			info += "vendor : " + std::string((char*)vendor) + "\n";
			info += "version : " + std::string((char*)version) + "\n";
			info += "glsl version : " + std::string((char*)glslVer) + "\n";
			JS_CORE_INFO((char*)info.c_str());

		}

		GuiRenderer::~GuiRenderer(void) {
			wglMakeCurrent(m_DeviceContext, nullptr);
			wglDeleteContext(m_GLContext);
			ReleaseDC(m_Window->GetId(), m_DeviceContext);
			Mutex::Destroy(m_Mutex);
		}

		void GuiRenderer::ClearBuffer(float rgba[4]) {

			GLCALL(glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]));
			GLCALL(glClear(GL_COLOR_BUFFER_BIT));
		}

		void GuiRenderer::SwapBuffers(void) const {
			::SwapBuffers(m_DeviceContext);
		}

		void GuiRenderer::Viewport(float x, float y, float width, float height) {
			m_Viewport = { x,y,width,height };
		}


		GuiRenderer* GuiRenderer::Create(std::shared_ptr<Window>& win) {
			return new GuiRenderer(win);
		}

		void GuiRenderer::Destroy(GuiRenderer* ptr) {
			delete ptr;
		}

		void GuiRenderer::StartFrame(void)  {
			while (!m_RenderFinish);
			m_Mutex->Lock();
			m_Draws.clear();
			
		}

		void GuiRenderer::SubmitDrawable(Drawable* drw)  {
			m_Draws.push_back(drw);
		}

		void GuiRenderer::EndFrame(void)  {
			m_Mutex->Unlock();
		}

		void GuiRenderer::Run(void) {
			
			m_Mutex->Lock();
			
			for (int i = 0; i < m_Draws.size(); i++) {
				m_Draws[i]->Bind();
				GLCALL(glDrawElements(
					GL_TRIANGLES,
					m_Draws[i]->GetMesh()->GetData()->IndexSize / sizeof(uint16_t),
					GL_UNSIGNED_SHORT, nullptr));
			}


			

			m_RenderFinish = true;
			m_Mutex->Unlock();
		}
	};
};
