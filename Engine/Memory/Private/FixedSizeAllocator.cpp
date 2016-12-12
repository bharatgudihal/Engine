#include "../FixedSizeAllocator.h"

namespace Engine {
	FixedSizeAllocator::FixedSizeAllocator(size_t i_blockSize, size_t i_units, HeapManager* i_heapManager) {
		blockSize = i_blockSize;
		units = i_units;
		heapManager = i_heapManager;
		assert(blockSize % i_units == 0);
		unitSize = blockSize / units;
		size_t arraySize = units / BitArray::BitsPerUnit();
		if (units % BitArray::BitsPerUnit() != 0) {
			arraySize += 1;
		}
		size_t totalSize = blockSize + sizeof(BitArray) + (sizeof(size_t) * arraySize);
		blockBase = heapManager->allocate(totalSize);
		uintptr_t* ptr = static_cast<uintptr_t*>(blockBase);
		uintptr_t* bitArrayPointer = ptr;
		bitArray = BitArray::Create(units, bitArrayPointer, bitArrayPointer + sizeof(BitArray));
		ptr += sizeof(BitArray) + (sizeof(size_t) * arraySize);
		workingBase = static_cast<uintptr_t*>(ptr);
	}

	FixedSizeAllocator::~FixedSizeAllocator() {
		assert(bitArray->AreAllSet());
		heapManager->free(blockBase);
	}

	void* FixedSizeAllocator::allocate() {
		size_t index = 0;
		if (bitArray->GetFirstSetBit(index)) {
			bitArray->ClearBit(index);
			return workingBase + (unitSize * index);
		}
		else {
			return nullptr;
		}
	}

	bool FixedSizeAllocator::free(void* ptr) {
		size_t index = 0;
		if (isValid(ptr, index)) {
			bitArray->SetBit(index);
			return true;
		}
		else {
			return false;
		}
	}

	bool FixedSizeAllocator::isValid(void* ptr, size_t& o_index) {
		uintptr_t* address = static_cast<uintptr_t*>(ptr);
		ptrdiff_t addressDiff = address - workingBase;
		if (addressDiff % unitSize == 0) {
			o_index = addressDiff / unitSize;			
			return bitArray->IsBitClear(o_index);
		}
		else {
			return false;
		}
	}
}