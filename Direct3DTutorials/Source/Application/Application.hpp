#pragma once
#include "../Core.hpp"

namespace JSGraphicEngine3D {
	class Application {

	public:
		Application(void) = default;
		virtual ~Application(void) = default;

		virtual void Run(void) = 0;

	};
}