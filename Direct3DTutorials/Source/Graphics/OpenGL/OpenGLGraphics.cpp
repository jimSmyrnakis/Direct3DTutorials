#include "OpenGLGraphics.hpp"
#include "wgl/include/glad/glad_wgl.h"
#include "../../FrameWork/Window.hpp"
#pragma comment (lib ,"opengl32.lib" )
namespace JSGraphicsEngine3D {

	static void CreateModernOpenGLContext(HWND hwnd , HDC* hdc , HGLRC* modernContext) {
		

		

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
		JS_CORE_ASSERT(wglMakeCurrent(*hdc, hglrc) != FALSE , JS_ERROR_FAILED_CREATE_CONTEXT , "Failed make dummy Context current !!!");

		
		// 6. Load wglCreateContextARB method from dll (opengl32.dll)
		PFNWGLCREATECONTEXTATTRIBSARBPROC MyCreateContext = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
			wglGetProcAddress("wglCreateContextAttribsARB");
		JS_CORE_ASSERT(MyCreateContext, JS_ERROR_FAILED_CREATE_CONTEXT, "Can't Load wglCreateContextARB method");
		

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
		JS_CORE_ASSERT(wglMakeCurrent(nullptr, nullptr) != FALSE , JS_ERROR_FAILED_CREATE_CONTEXT , "Failed clear current contexts");

		// 10. Delete Dummy Context
		JS_CORE_ASSERT(wglDeleteContext(hglrc) != FALSE, JS_ERROR_FAILED_CREATE_CONTEXT, "Failed deleting dummy context");

		// 11. Make Modern Context current
		JS_CORE_ASSERT( wglMakeCurrent(*hdc, *modernContext) != FALSE, JS_ERROR_FAILED_CREATE_CONTEXT, "Failed make modern context as current");

		// 12. Load all Modern OpenGL methods
		if (!gladLoadGL()) {
			MessageBoxA(0, "Failed to load OpenGL functions", "Error", MB_ICONERROR);
			js_break(1);
		}

		

	}

	OpenGLGraphics::OpenGLGraphics(Window* win) {
		JS_CORE_ASSERT(win, JS_ERROR_NULL_PARAMETER, "win of the Graphics parameter is nullptr !!!");
		m_Window = win;
		CreateModernOpenGLContext(win->GetId(), &m_DeviceContext, &m_GLContext);

		const GLubyte* renderer = glGetString(GL_RENDERER);   // Κάρτα (π.χ. "NVIDIA GeForce GTX 1660")
		const GLubyte* vendor = glGetString(GL_VENDOR);     // Κατασκευαστής (π.χ. "NVIDIA Corporation")
		const GLubyte* version = glGetString(GL_VERSION);    // Έκδοση OpenGL (π.χ. "4.6.0 NVIDIA 537.13")
		const GLubyte* glslVer = glGetString(GL_SHADING_LANGUAGE_VERSION); // GLSL έκδοση (π.χ. "4.60 NVIDIA")
		std::string info = "renderer : " + std::string((char*)renderer) + "\n";
		info += "vendor : " + std::string((char*)vendor) + "\n";
		info += "version : " + std::string((char*)version) + "\n";
		info += "glsl version : " + std::string((char*)glslVer) + "\n";
		JS_CORE_INFO((char*)info.c_str());
	}

	OpenGLGraphics::~OpenGLGraphics(void) {
		wglMakeCurrent(m_DeviceContext, nullptr);
		wglDeleteContext(m_GLContext);
		ReleaseDC(m_Window->GetId(), m_DeviceContext);
	}

	void OpenGLGraphics::ClearBuffer(float rgba[4]) {
		glViewport(100, 100, 200, 200);
		glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void OpenGLGraphics::SwapBuffers(void) const {
		
		::SwapBuffers(GetDC(m_Window->GetId()));
	}

	void OpenGLGraphics::DrawTriangle(void) {

	}

	OpenGLGraphics* OpenGLGraphics::Create(Window* win) {
		return new OpenGLGraphics(win);
	}
	void OpenGLGraphics::Destroy(OpenGLGraphics* ptr) {
		delete ptr;
	}
}
