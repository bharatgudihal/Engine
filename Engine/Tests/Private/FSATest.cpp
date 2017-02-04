#include "../FSATest.h"
#include "../../Memory/Allocators.h"
#include <vector>

//#define TESTOVERWRITE

namespace Engine {
	namespace Test {
		bool FSAUnitTest() {
			size_t blockSize = 1600;
			size_t units = 100;
			Memory::FixedSizeAllocator* FSA = Memory::FixedSizeAllocator::Create(blockSize, units, Engine::Memory::MasterMemoryManager::Instance()->DefaultHeapManager());
			size_t defaultAlignment = 4;
			std::vector<void*> allocatedPointers;
			// Allocate all
			for (unsigned int i = 0; i < units; i++) {
				void* ptr = FSA->allocate();
				assert(ptr);
				// Check for alignment
				assert(reinterpret_cast<uintptr_t>(ptr) % defaultAlignment == 0);
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
			while (true) {
				void* ptr = FSA->allocate();
				if (ptr == nullptr) {
					break;
				}
				// Check for alignment
				assert(reinterpret_cast<uintptr_t>(ptr) % defaultAlignment == 0);
				allocatedPointers.push_back(ptr);
#ifdef TESTOVERWRITE
				uint8_t* testptr = static_cast<uint8_t*>(ptr);
				testptr -= 1;
				*testptr = 0xAB;
#endif // TESTOVERWRITE
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
}