#include <Entry/Entry.hpp>
#include <Graphics/Direct3D/Direct3DGraphics.hpp>
#include <Gui/Renderer/Uniforms/Uniform.hpp>
#include <Gui/Renderer/Renderer.hpp>
#include <Gui/Renderer/Example/DrawableButton.hpp>
#include <Extras/Time.hpp>

namespace JSGraphicsEngine3D {
	void Application::OnRun(void) {
		namespace js = JSGraphicsEngine3D;
		std::shared_ptr<js::Window> win(new js::Window(300, 300 , L"Program"));
		js::Button* but0 = new js::Button(-50, -50, 100, 100 , win );
		js::Gui::GuiRenderer* GuiRender = new  js::Gui::GuiRenderer(win);
		js::Gui::DrawableButton* but0_drawable = new js::Gui::DrawableButton();
		js::Time* time = js::Time::Create();
		uint8_t clr = 0;
		bool increment = true;

		while (true) {
			float arr[4] = { clr / 255.0f, 0.0f, clr / 255.0f, 1.0f };
			float arr2[4] = { clr / 255.0f, 1.0f, clr / 255.0f, 1.0f };
			win->PollEvents();
			GuiRender->ClearBuffer(arr);
			GuiRender->StartFrame();
			GuiRender->SubmitDrawable(&but0_drawable->GetDrawable());
			GuiRender->EndFrame();
			GuiRender->Run();
			GuiRender->SwapBuffers();
			clr = clr + ( (increment) ? +1 : -1) ;
			if (clr == 255) {
				increment = false;
				
			}
				
			if (clr == 0) {
				increment = true;
			}
		}

		return;
	}
	// after leaving the OnRun method the OnDestroy is called a little before the Application stop executing
	int  Application::OnDestroy(void) {
		return 0;
	}
	//return the exit code
}