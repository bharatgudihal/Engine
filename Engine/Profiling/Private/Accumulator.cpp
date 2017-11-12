#include "../Accumulator.h"
#include "../Profiler.h"

namespace Engine {
	namespace Profiling {
		Accumulator::Accumulator(const char* name) :sum(0.0), count(0), minTime(std::numeric_limits<float>::max()), maxTime(std::numeric_limits<float>::lowest()) {
			Profiler::Instance()->RegisterAccumulator(name, this);
		}
	}
}