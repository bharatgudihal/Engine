#pragma once
#define DESIRED_FPS 60.0f
#define DESIRED_FRAME_TIME (1.0f/DESIRED_FPS)
#define MAX_FRAME_TIME (2*DESIRED_FRAME_TIME)

namespace Engine {
	class CoreTimer{		
	public:
		typedef __int64 tick;
		static float GetDeltaTime();
		static tick GetCurrentTick();
		static tick GetTimeDifference(tick);
	private:
		static tick previousTick;
		static tick tickFrequency;
		static tick GetFrequency();
		static float CalculateDeltaTime();		
	};
}