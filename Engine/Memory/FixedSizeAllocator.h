#pragma once
#include <stdint.h>
namespace Engine {
	class HeapManager;
	class BitArray;
	class FixedSizeAllocator {
	public:
		inline static FixedSizeAllocator* Create(size_t i_blockSize, size_t i_units, HeapManager* i_heapManager);
		~FixedSizeAllocator();
		void* allocate();
		void free(void* ptr);
		size_t unitSize;		

	private:
		FixedSizeAllocator(size_t i_blockSize, size_t i_units, HeapManager* i_heapManager);
		size_t blockSize;
		uintptr_t* workingBase;
		void* blockBase;
		size_t units;
		BitArray* bitArray;
		HeapManager* heapManager;
		bool isValid(void* ptr, size_t& o_index);
	};
}
#include "FixedSizeAllocator_Inl.h"