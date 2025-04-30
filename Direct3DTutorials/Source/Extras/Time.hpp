#pragma once
#include "../Core.hpp"
#include "Mutex.hpp"
namespace JSGraphicsEngine3D {
	class Time {

	private:
		
		Time(void);
		~Time(void);

	public:

		float GetTime(void) const ; // In Seconds - must be thread safe
		// returns time difference from the last time called

	public:

		static Time* Create(void);
		static void  Destroy(Time* ptr);

	private:
		float m_StartTime; // in seconds
		Mutex* m_Mutex;
	};
}