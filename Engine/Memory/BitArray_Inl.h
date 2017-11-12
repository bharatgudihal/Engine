#pragma once
namespace Engine {
	namespace Memory {
		inline BitArray* BitArray::Create(const size_t i_numberOfBits, const bool i_startClear, HeapManager* heapManager) {
			return new BitArray(i_numberOfBits, i_startClear, heapManager);
		}

		inline BitArray* BitArray::Create(const size_t i_numberOfBits) {
			return new BitArray(i_numberOfBits);
		}

		inline BitArray* BitArray::Create(const size_t i_numberOfBits, void* i_ptr, void* i_arrayPtr) {
			return new (i_ptr) BitArray(i_numberOfBits, i_arrayPtr);
		}

		inline void BitArray::ClearAll() {
			memset(bits, 0, bitsPerUnit / bitsPerByte*arraySize);
		}

		inline bool BitArray::IsBitClear(const size_t i_bitNumber) const {
			return !IsBitSet(i_bitNumber);
		}

		inline size_t BitArray::BitsPerUnit() {
			return bitsPerUnit;
		}
	}
}