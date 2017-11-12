#pragma once
#include "../Timer/CoreTimer.h"
#include "Accumulator.h"

namespace Engine {
	namespace Profiling {
		class ScopedTimer {
		public:
			ScopedTimer(Accumulator&);
			~ScopedTimer();
		private:
			CoreTimer::tick currentTick;
			Accumulator* accumulator;
		};
	}
}
#include "ScopedTimer_Inl.h"