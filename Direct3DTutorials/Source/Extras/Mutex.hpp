#pragma once
#include "../Core.hpp"

namespace JSGraphicsEngine3D {
	class Mutex {

	private:
		CRITICAL_SECTION	m_Critical;

	};
}