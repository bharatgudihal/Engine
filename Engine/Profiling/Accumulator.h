#pragma once
#include <stdint.h>
#include <limits>


namespace Engine {
	namespace Profiling {
		class Accumulator {
		public:
			Accumulator(const char* name);
			inline Accumulator& operator+=(float time);
			inline float average() const;
			float minTime, maxTime;
		private:
			double sum;
			uint64_t count;			
		};
	}
}
#include "Accumulator_Inl.h"