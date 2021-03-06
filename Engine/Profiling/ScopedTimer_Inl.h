#pragma once
namespace Engine {
	namespace Profiling {
		ScopedTimer::ScopedTimer(Accumulator& i_accumulator) :currentTick(CoreTimer::GetCurrentTick()), accumulator(&i_accumulator) {}

		ScopedTimer::~ScopedTimer() {
			*accumulator += static_cast<float>(CoreTimer::GetTimeDifference(currentTick));
		}
	}
}