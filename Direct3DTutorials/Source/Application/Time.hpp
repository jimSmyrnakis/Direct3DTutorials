#pragma once
#include "../Core.hpp"

namespace JSGraphicsEngine3D {
	class Time {

	public:
		
		Time(void);
		~Time(void) = default;

		float GetTime(void) const ; // In Seconds

	private:
		float m_BeginTime; // in seconds
		float m_CurrentTime;// in seconds

	};
}