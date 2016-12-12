#include "../FSATest.h"
#include "../../Memory/Allocators.h"
#include <vector>

namespace Engine {
	bool FSAUnitTest() {		
		FixedSizeAllocator* FSA = FixedSizeAllocator::Create(1600, 100, Engine::MasterMemoryManager::Instance()->DefaultHeapManager());
		std::vector<void*> allocatedPointers;
		for (int i = 0; i < 100; i++) {
			void* ptr = FSA->allocate();
			assert(ptr);			
			allocatedPointers.push_back(ptr);
		}
		assert(FSA->allocate() == nullptr);
		assert(FSA->AreAllAllocated());
		std::random_shuffle(allocatedPointers.begin(), allocatedPointers.end());
		while (!allocatedPointers.empty()) {
			void* ptr = allocatedPointers.back();
			allocatedPointers.pop_back();
			FSA->free(ptr);
		}
		assert(FSA->AreAllFreed());
		delete FSA;
		return true;
	}
}