#pragma once
#include <stdint.h>
#include "BitArray.h"
namespace Engine {
	#ifdef _DEBUG
	#define FSA_GUARD_BAND_SIZE 4
	#else
	#define FSA_GUARD_BAND_SIZE 0
	#endif // _DEBUG
	class FixedSizeAllocator {
	public:
		inline static FixedSizeAllocator* Create(size_t i_blockSize, size_t i_units, HeapManager* i_heapManager);
		~FixedSizeAllocator();
		void* allocate();
		bool free(void* ptr);
		size_t unitSize;
		inline bool AreAllAllocated();
		inline bool AreAllFreed();

	private:
		FixedSizeAllocator(size_t i_blockSize, size_t i_units, HeapManager* i_heapManager);
		size_t blockSize;
		uint8_t* workingBase;
		void* blockBase;
		size_t units;
		BitArray* bitArray;
		HeapManager* heapManager;
		bool isValid(void* ptr, size_t& o_index);
		const uint8_t GUARD_BAND_FILL = 0xAA;
		void AddGuardBands(uint8_t*);
		void CheckGuardBands(void*);
	};
}
#include "FixedSizeAllocator_Inl.h"