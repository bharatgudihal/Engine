#pragma once
#define DESIRED_FPS 60.0f
#define DESIRED_FRAME_TIME (1.0f/DESIRED_FPS)
#define MAX_FRAME_TIME (2*DESIRED_FRAME_TIME)

namespace Engine {
	class CoreTimer{

	public:
		static float GetDeltaTime();

	private:
		static __int64 previousTick;
		static __int64 tickFrequency;
		static __int64 GetCounter();
		static __int64 GetFrequency();
		static float CalculateDeltaTime();		
	};
}