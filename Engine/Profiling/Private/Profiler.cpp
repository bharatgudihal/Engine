#include "../Profiler.h"
#include "../Accumulator.h"

namespace Engine {
	namespace Profiling {
		Profiler* Profiler::instance = nullptr;

		bool Profiler::Startup() {
			bool result = false;
			if (instance == nullptr) {
				instance = new Profiler();
				if (instance) {
					result = true;
				}
			}
			return result;
		}

		void Profiler::Shutdown() {
			if (instance) {
				delete instance;
			}
		}

		Profiler::~Profiler() {
			if (!accumulators.empty()) {
				std::map<const char*, const Accumulator*>::iterator it;
				for (it = accumulators.begin(); it != accumulators.end(); it++) {
					PROFILE_LOG("%s average time %f\n", it->first, it->second->average());
					PROFILE_LOG("%s min time %f\n", it->first, it->second->minTime);
					PROFILE_LOG("%s max time %f\n", it->first, it->second->maxTime);
				}
			}
		}
	}
}