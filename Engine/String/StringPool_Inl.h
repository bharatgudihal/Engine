#pragma once
namespace Engine {
	namespace String {
		inline StringPool* StringPool::Create(const size_t size) {
			assert(size > 0);
			return new StringPool(size);
		}

		inline StringPool::~StringPool() {
			assert(startOfBlock);
			MasterMemoryManager::Instance()->DefaultHeapManager()->free(startOfBlock);
		}
	}
}