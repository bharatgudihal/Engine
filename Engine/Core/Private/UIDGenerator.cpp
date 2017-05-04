#include "../UIDGenerator.h"

namespace Engine {
	namespace Core {
		UIDGenerator* UIDGenerator::instance = nullptr;

		bool UIDGenerator::Startup() {
			if (!instance) {
				instance = new UIDGenerator();				
			}
			return instance != nullptr;
		}

		void UIDGenerator::ShutDown() {
			if (instance) {
				delete instance;
			}
		}

		uint32_t UIDGenerator::GetUID() {
			uint32_t id = 0;
			if (instance) {
				id = instance->counter++;
			}
			return id;
		}
	}
}