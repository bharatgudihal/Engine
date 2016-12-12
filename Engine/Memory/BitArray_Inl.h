#pragma once
namespace Engine {
	inline BitArray* BitArray::Create(size_t i_numberOfBits, bool i_startClear, HeapManager* heapManager) {
		return new BitArray(i_numberOfBits, i_startClear, heapManager);
	}

	inline BitArray* BitArray::Create(size_t i_numberOfBits) {		
		return new BitArray(i_numberOfBits);
	}

	inline void BitArray::ClearAll() {
		memset(bits, 0, bitsPerUnit/bitsPerByte*arraySize);
	}

	inline bool BitArray::IsBitClear(size_t i_bitNumber) const {
		return !IsBitSet(i_bitNumber);
	}
}