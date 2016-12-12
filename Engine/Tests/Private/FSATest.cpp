#include "../FSATest.h"
#include "../../Memory/FixedSizeAllocator.h"
#include "../../Memory/Allocators.h"

namespace Engine {
	bool FSAUnitTest() {		
		FixedSizeAllocator* FSA = FixedSizeAllocator::Create(1600, 100, DefaultHeapManager(nullptr));
		void* pointerArray[100];
		for (int i = 0; i < 100; i++) {
			void* ptr = FSA->allocate();
			assert(ptr);
			pointerArray[i] = ptr;
		}
		assert(FSA->allocate() == nullptr);
		for (int i = 0; i < 100; i++) {
			FSA->free(pointerArray[i]);
		}
		delete FSA;
		return true;
	}
}