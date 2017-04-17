#pragma once
#include <stdint.h>
#include "Profiler.h"

namespace Engine {
	namespace Profiling {
		class Accumulator {
		public:
			inline Accumulator(const char* name);
			inline void operator+=(float time);
			inline float average() const;
			float min, max;
		private:
			double sum;
			uint64_t count;			
		};
	}
}
#include "Accumulator_Inl.h"