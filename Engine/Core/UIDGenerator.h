#pragma once
#include <stdint.h>

namespace Engine {
	namespace Core {
		class UIDGenerator {
		public:
			static bool Startup();
			static void ShutDown();
			static uint32_t GetUID();
		private:
			UIDGenerator() {};
			~UIDGenerator() {};
			UIDGenerator(UIDGenerator&) {};
			UIDGenerator& operator=(UIDGenerator&) {};
			static UIDGenerator* instance;
			uint32_t counter;
		};
	}
}