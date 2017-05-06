#include "../BitArray.h"
namespace Engine {
	namespace Memory {
		BitArray::BitArray(const size_t i_numberOfBits, const bool i_startClear, HeapManager* heapManager) {
			assert(i_numberOfBits > 0);
			numberOfBits = i_numberOfBits;
			remainder = numberOfBits % bitsPerUnit;
			arraySize = numberOfBits / bitsPerUnit;
			if (remainder != 0) {
				arraySize += 1;
			}
			bits = new (heapManager) size_t[arraySize];
			assert(bits);
			if (i_startClear) {
				ClearAll();
			}
			else {
				SetAll();
			}
		}

		BitArray::BitArray(const size_t i_numberOfBits) {
			numberOfBits = i_numberOfBits;
			remainder = numberOfBits % bitsPerUnit;
			arraySize = numberOfBits / bitsPerUnit;
			if (remainder != 0) {
				arraySize += 1;
			}
			bits = new size_t[arraySize];
			assert(bits);
			ClearAll();
		}

		BitArray::BitArray(const size_t i_numberOfBits, void* i_ptr) {
			numberOfBits = i_numberOfBits;
			remainder = numberOfBits % bitsPerUnit;
			arraySize = numberOfBits / bitsPerUnit;
			if (remainder != 0) {
				arraySize += 1;
			}
			bits = new (i_ptr) size_t[arraySize];
			assert(bits);
			SetAll();
		}

		BitArray::~BitArray() {
			delete[] bits;
		}

		void BitArray::SetAll() {
			bitArrayMutex.Acquire();
			if (remainder == 0) {
				memset(bits, MAX_SET, bitsPerUnit / bitsPerByte * arraySize);
			}
			else {
				memset(bits, MAX_SET, bitsPerUnit / bitsPerByte * (arraySize - 1));
				for (size_t index = 0; index < remainder; index++) {
					bits[arraySize - 1] = bits[arraySize - 1] | (maskUnit << index);
				}
			}
			bitArrayMutex.Release();
		}

		bool BitArray::AreAllClear() const {
			unsigned long bitIndex;
			bitArrayMutex.Acquire();
			if (remainder == 0) {
				for (size_t index = 0; index < arraySize; index++) {
					unsigned long bitIndex;
					if (BITSCAN(&bitIndex, bits[index])) {
						bitArrayMutex.Release();
						return false;
					}
				}
			}
			else {
				for (size_t index = 0; index < arraySize - 1; index++) {
					if (BITSCAN(&bitIndex, bits[index])) {
						bitArrayMutex.Release();
						return false;
					}
				}
				for (size_t bitIndex = 0; bitIndex < remainder; bitIndex++) {
					if ((bits[arraySize - 1] & (maskUnit << bitIndex))) {
						bitArrayMutex.Release();
						return false;
					}
				}
			}
			bitArrayMutex.Release();
			return true;
		}

		bool BitArray::AreAllSet() const {
			unsigned long bitIndex;
			bitArrayMutex.Acquire();
			if (remainder == 0) {
				unsigned long bitIndex;
				for (size_t index = 0; index < arraySize; index++) {
					if (BITSCAN(&bitIndex, ~bits[index])) {
						bitArrayMutex.Release();
						return false;
					}
				}
			}
			else {
				for (size_t index = 0; index < arraySize - 1; index++) {
					if (BITSCAN(&bitIndex, ~bits[index])) {
						bitArrayMutex.Release();
						return false;
					}
				}
				for (size_t bitIndex = 0; bitIndex < remainder; bitIndex++) {
					if (!(bits[arraySize - 1] & (maskUnit << bitIndex))) {
						bitArrayMutex.Release();
						return false;
					}
				}
			}
			bitArrayMutex.Release();
			return true;
		}

		bool BitArray::IsBitSet(const size_t i_bitNumber) const {
			bitArrayMutex.Acquire();
			size_t arrayIndex = i_bitNumber / bitsPerUnit;
			size_t bitRemainder = i_bitNumber % bitsPerUnit;
			bool result = (bits[arrayIndex] & (maskUnit << bitRemainder)) != 0;
			bitArrayMutex.Release();
			return result;
		}

		void BitArray::SetBit(const size_t i_bitNumber) {
			bitArrayMutex.Acquire();
			size_t arrayIndex = i_bitNumber / bitsPerUnit;
			size_t bitRemainder = i_bitNumber % bitsPerUnit;
			bits[arrayIndex] = bits[arrayIndex] | (maskUnit << bitRemainder);
			bitArrayMutex.Release();
		}

		void BitArray::ClearBit(const size_t i_bitNumber) {
			bitArrayMutex.Acquire();
			size_t arrayIndex = i_bitNumber / bitsPerUnit;
			size_t bitRemainder = i_bitNumber % bitsPerUnit;
			bits[arrayIndex] = bits[arrayIndex] & ~(maskUnit << bitRemainder);
			bitArrayMutex.Release();
		}

		bool BitArray::GetFirstClearBit(size_t& o_bitNumber) const {
			unsigned long longBitIndex;
			bitArrayMutex.Acquire();
			if (remainder == 0) {
				for (size_t index = 0; index < arraySize; index++) {
					if (BITSCAN(&longBitIndex, ~(bits[index]))) {
						o_bitNumber = longBitIndex + index*bitsPerUnit;
						bitArrayMutex.Release();
						return true;
					}
				}
			}
			else {
				for (size_t index = 0; index < arraySize - 1; index++) {
					if (BITSCAN(&longBitIndex, ~(bits[index]))) {
						o_bitNumber = longBitIndex + index*bitsPerUnit;
						bitArrayMutex.Release();
						return true;
					}
				}
				size_t bitIndex = 0;
				while ((bits[arraySize - 1] & (maskUnit << bitIndex)) && (bitIndex < remainder)) {
					bitIndex++;
				}
				o_bitNumber = bitIndex + (arraySize - 1) * bitsPerUnit;
				if (o_bitNumber == numberOfBits) {
					bitArrayMutex.Release();
					return false;
				}
				else {
					bitArrayMutex.Release();
					return true;
				}
			}
			bitArrayMutex.Release();
			return false;
		}

		bool BitArray::GetFirstSetBit(size_t& o_bitNumber) const {
			unsigned long longBitIndex;
			bitArrayMutex.Acquire();
			if (remainder == 0) {
				for (size_t index = 0; index < arraySize; index++) {
					if (bits[index] != 0) {
						if (BITSCAN(&longBitIndex, bits[index])) {
							o_bitNumber = longBitIndex + index * bitsPerUnit;
							bitArrayMutex.Release();
							return true;
						}
						else {
							bitArrayMutex.Release();
							return false;
						}
					}
				}
			}
			else {
				for (size_t index = 0; index < arraySize - 1; index++) {
					if (bits[index] != 0) {
						if (BITSCAN(&longBitIndex, bits[index])) {
							o_bitNumber = longBitIndex + index * bitsPerUnit;
							bitArrayMutex.Release();
							return true;
						}
						else {
							bitArrayMutex.Release();
							return false;
						}
					}
				}
				size_t bitIndex = 0;
				while (!(bits[arraySize - 1] & (maskUnit << bitIndex)) && (bitIndex < remainder)) {
					bitIndex++;
				}
				o_bitNumber = bitIndex + (arraySize - 1) * bitsPerUnit;
				if (o_bitNumber == numberOfBits) {
					bitArrayMutex.Release();
					return false;
				}
				else {
					bitArrayMutex.Release();
					return true;
				}
			}
			bitArrayMutex.Release();
			return false;
		}
	}
}