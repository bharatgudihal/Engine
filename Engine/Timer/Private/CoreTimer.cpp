#include "../CoreTimer.h"
#include <Windows.h>

namespace Engine {

	__int64 CoreTimer::previousTick = 0;
	__int64 CoreTimer::tickFrequency = 0;

	__int64 CoreTimer::GetFrequency() {
		LARGE_INTEGER frequency;
		if (!tickFrequency) {
			QueryPerformanceFrequency(&frequency);
			tickFrequency = frequency.QuadPart;
		}
		return tickFrequency;
	}

	__int64 CoreTimer::GetCounter() {
		LARGE_INTEGER counterValue;
		QueryPerformanceCounter(&counterValue);
		return counterValue.QuadPart;
	}

	float CoreTimer::CalculateDeltaTime() {
		__int64 currentTick = GetCounter();
		float deltaTime;
		if (previousTick) {
			__int64 tickDifference = currentTick - previousTick;
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