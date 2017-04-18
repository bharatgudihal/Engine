#pragma once
#include <map>
#include <stdio.h>
#include "../Logger/Logger.h"

namespace Engine {
	namespace Profiling {
		class Accumulator;
		class Profiler {
		public:
			static bool Startup();
			static void Shutdown();
			inline static Profiler* Instance();
			inline void RegisterAccumulator(const char*, const Accumulator*);
		private:
			Profiler() {}
			~Profiler();
			static Profiler* instance;
			std::map<const char*, const Accumulator*> accumulators;
		};
	}
}
#include "Profiler_Inl.h"