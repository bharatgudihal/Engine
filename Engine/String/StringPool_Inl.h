#pragma once
namespace Engine {
	namespace String {
		inline bool StringPool::Startup(const size_t size) {
			assert(size > 0);
			if (!instance) {
				instance = new StringPool(size);
			}
			return true;
		}

		inline StringPool* StringPool::Instance() {
			return instance;
		}

		inline void StringPool::ShutDown() {
			if (instance) {
				delete instance;
			}
		}

		inline StringPool::~StringPool() {
			assert(startOfBlock);
			Memory::MasterMemoryManager::Instance()->DefaultHeapManager()->free(startOfBlock);
		}
	}
}