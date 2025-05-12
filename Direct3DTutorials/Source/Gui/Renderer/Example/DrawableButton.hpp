#pragma once
#include "../../../Core.hpp"
#include "../Drawable.hpp"
namespace JSGraphicsEngine3D {
	namespace Gui {
		class DrawableButton {
		public:
			DrawableButton(void);
			~DrawableButton(void);

			Drawable& GetDrawable(void) const;
		private:
			Drawable* m_Drawable;
		};
	}
}