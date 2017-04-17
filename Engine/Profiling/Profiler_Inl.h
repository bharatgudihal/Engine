#pragma once
namespace Engine {
	namespace Profiling {
		Profiler* Profiler::Instance() {
			return instance;
		}

		void Profiler::RegisterAccumulator(const char* name, const Accumulator* accumulator) {
			accumulators[name] = accumulator;
		}
	}
}