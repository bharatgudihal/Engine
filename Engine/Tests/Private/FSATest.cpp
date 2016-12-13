#include "../FSATest.h"
#include "../../Memory/Allocators.h"
#include <vector>

namespace Engine {
	bool FSAUnitTest() {
		size_t blockSize = 1600;
		size_t units = 100;
		FixedSizeAllocator* FSA = FixedSizeAllocator::Create(blockSize, units, Engine::MasterMemoryManager::Instance()->DefaultHeapManager());
		std::vector<void*> allocatedPointers;
		// Allocate all
		for (unsigned int i = 0; i < units; i++) {
			void* ptr = FSA->allocate();
			assert(ptr);			
			allocatedPointers.push_back(ptr);
		}
		assert(FSA->allocate() == nullptr);
		assert(FSA->AreAllAllocated());
		// Randomize vector
		std::random_shuffle(allocatedPointers.begin(), allocatedPointers.end());
		// Free all
		while (!allocatedPointers.empty()) {
			void* ptr = allocatedPointers.back();
			allocatedPointers.pop_back();
			bool success = FSA->free(ptr);
			assert(success);
		}
		assert(FSA->AreAllFreed());
		// Allocate to exhaustion while freeing randomly
		while(true) {
			void* ptr = FSA->allocate();
			if (ptr == nullptr) {
				break;
			}
			allocatedPointers.push_back(ptr);

			const unsigned int freeAboutEvery = 10;
			if (!allocatedPointers.empty() && ((rand() % freeAboutEvery) == 0))
			{
				void * pPtr = allocatedPointers.back();
				allocatedPointers.pop_back();

				bool success = FSA->free(pPtr);
				assert(success);
			}
		}
		assert(FSA->allocate() == nullptr);
		assert(FSA->AreAllAllocated());
		// Randomize vector
		std::random_shuffle(allocatedPointers.begin(), allocatedPointers.end());
		// Free all
		while (!allocatedPointers.empty()) {
			void* ptr = allocatedPointers.back();
			allocatedPointers.pop_back();
			bool success = FSA->free(ptr);
			assert(success);
		}
		assert(FSA->AreAllFreed());
		delete FSA;
		return true;
	}
}