#include "../FixedSizeAllocator.h"

namespace Engine {
	FixedSizeAllocator::FixedSizeAllocator(size_t i_blockSize, size_t i_units, HeapManager* i_heapManager) {
		blockSize = i_blockSize + GUARD_BAND_SIZE * i_units * 2;
		units = i_units;
		heapManager = i_heapManager;
		assert(blockSize % i_units == 0);
		unitSize = blockSize / units;
		size_t arraySize = units / BitArray::BitsPerUnit();
		if (units % BitArray::BitsPerUnit() != 0) {
			arraySize += 1;
		}
		// Total Size = blockSize + size of BitArray object + size of bit array inside BitArrayObject
		size_t totalSize = blockSize + sizeof(BitArray) + (sizeof(size_t) * arraySize);
		blockBase = heapManager->allocate(totalSize);
		uint8_t* ptr = static_cast<uint8_t*>(blockBase);
		uint8_t* bitArrayPointer = ptr;
		bitArray = BitArray::Create(units, bitArrayPointer, bitArrayPointer + sizeof(BitArray));
		ptr += sizeof(BitArray) + (sizeof(size_t) * arraySize);
		workingBase = ptr;
	}

	FixedSizeAllocator::~FixedSizeAllocator() {
		assert(bitArray->AreAllSet());
		heapManager->free(blockBase);
	}

	void FixedSizeAllocator::AddGuardBands(uint8_t* userPointer) {		
		for (uint8_t count = 0; count < GUARD_BAND_SIZE; count++) {
			*(userPointer) = GUARD_BAND_FILL;
			userPointer++;
		}
		userPointer += unitSize - GUARD_BAND_SIZE * 2;
		for (uint8_t count = 0; count < GUARD_BAND_SIZE; count++) {
			*(userPointer) = GUARD_BAND_FILL;
			userPointer++;
		}
	}

	void* FixedSizeAllocator::allocate() {
		size_t index = 0;
		if (bitArray->GetFirstSetBit(index)) {
			bitArray->ClearBit(index);
			uint8_t* userPointer = reinterpret_cast<uint8_t*>(workingBase) + (unitSize * index);
			AddGuardBands(userPointer);
			return userPointer;
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

	void FixedSizeAllocator::CheckGuardBands(void* i_ptr) {
		uint8_t* checkPointer = static_cast<uint8_t*>(i_ptr);
		for (uint8_t count = 0; count < GUARD_BAND_SIZE; count++) {
			assert(*checkPointer == GUARD_BAND_FILL);
			checkPointer++;
		}
		checkPointer += unitSize - GUARD_BAND_SIZE * 2;
		for (uint8_t count = 0; count < GUARD_BAND_SIZE; count++) {
			assert(*checkPointer == GUARD_BAND_FILL);
			checkPointer++;
		}
	}

	bool FixedSizeAllocator::isValid(void* ptr, size_t& o_index) {
		uint8_t* address = static_cast<uint8_t*>(ptr);
		ptrdiff_t addressDiff = address - workingBase;
		if (addressDiff % unitSize == 0) {
			o_index = addressDiff / unitSize;			
			if (bitArray->IsBitClear(o_index)) {
				CheckGuardBands(ptr);
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
}