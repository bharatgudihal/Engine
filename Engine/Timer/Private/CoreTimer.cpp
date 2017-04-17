#include "../CoreTimer.h"
#include <Windows.h>

namespace Engine {

	CoreTimer::tick CoreTimer::previousTick = 0;
	CoreTimer::tick CoreTimer::tickFrequency = 0;

	CoreTimer::tick CoreTimer::GetFrequency() {
		LARGE_INTEGER frequency;
		if (!tickFrequency) {
			QueryPerformanceFrequency(&frequency);
			tickFrequency = frequency.QuadPart;
		}
		return tickFrequency;
	}

	CoreTimer::tick CoreTimer::GetCurrentTick() {
		LARGE_INTEGER counterValue;
		QueryPerformanceCounter(&counterValue);
		return counterValue.QuadPart;
	}

	CoreTimer::tick CoreTimer::GetTimeDifference(CoreTimer::tick time) {
		return GetCurrentTick() - time;
	}

	float CoreTimer::CalculateDeltaTime() {
		CoreTimer::tick currentTick = GetCurrentTick();
		float deltaTime;
		if (previousTick) {
			CoreTimer::tick tickDifference = currentTick - previousTick;
			deltaTime = tickDifference / static_cast<float>(GetFrequency());
		}
		else {
			deltaTime = DESIRED_FRAME_TIME;
		}
		previousTick = currentTick;
		return deltaTime;
	}

	float CoreTimer::GetDeltaTime() {
		float deltaTime = CalculateDeltaTime();
#ifdef _DEBUG
		if (deltaTime > MAX_FRAME_TIME) {
			deltaTime = MAX_FRAME_TIME;
		}
#endif // _DEBUG
		return deltaTime;
	}
}