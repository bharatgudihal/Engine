#include "../BitArray.h"
namespace Engine {

	BitArray::BitArray(size_t i_numberOfBits, bool i_startClear, HeapManager* heapManager) {
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

	BitArray::BitArray(size_t i_numberOfBits) {
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

	BitArray::BitArray(size_t i_numberOfBits, void* i_ptr) {
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
 		if (remainder == 0) {
			memset(bits, MAX_SET, bitsPerUnit / bitsPerByte * arraySize);
		}
		else {
			memset(bits, MAX_SET, bitsPerUnit / bitsPerByte * (arraySize-1));
			for (size_t index = 0; index < remainder; index++) {
				bits[arraySize - 1] = bits[arraySize-1] | (maskUnit << index);
			}
		}
	}

	bool BitArray::AreAllClear() const{
		if (remainder == 0) {
			for (size_t index = 0; index < arraySize; index++) {
				if (bits[index] != 0) {
					return false;
				}
			}
		}
		else {
			for (size_t index = 0; index < arraySize - 1; index++) {
				if (bits[index] != 0) {
					return false;
				}
			}
			for (size_t bitIndex = 0; bitIndex < remainder; bitIndex++) {
				if ((bits[arraySize - 1] & (maskUnit << bitIndex))) {
					return false;
				}
			}
		}
		return true;
	}

	bool BitArray::AreAllSet() const {
		if (remainder == 0) {
			for (size_t index = 0; index < arraySize; index++) {
				if (bits[index] != MAX) {
					return false;
				}
			}
		}
		else {
			for (size_t index = 0; index < arraySize-1; index++) {
				if (bits[index] != MAX) {
					return false;
				}
			}
			for (size_t bitIndex = 0; bitIndex < remainder; bitIndex++) {
				if (!(bits[arraySize - 1] & (maskUnit << bitIndex))) {
					return false;
				}
			}
		}
		return true;
	}

	bool BitArray::IsBitSet(size_t i_bitNumber) const {
		size_t arrayIndex = i_bitNumber / bitsPerUnit;
		size_t bitRemainder = i_bitNumber % bitsPerUnit;
		return (bits[arrayIndex] & (maskUnit << bitRemainder)) != 0;
	}

	void BitArray::SetBit(size_t i_bitNumber) {
		size_t arrayIndex = i_bitNumber / bitsPerUnit;
		size_t bitRemainder = i_bitNumber % bitsPerUnit;
		bits[arrayIndex] = bits[arrayIndex] | (maskUnit << bitRemainder);
	}

	void BitArray::ClearBit(size_t i_bitNumber) {
		size_t arrayIndex = i_bitNumber / bitsPerUnit;
		size_t bitRemainder = i_bitNumber % bitsPerUnit;
		bits[arrayIndex] = bits[arrayIndex] & ~(maskUnit << bitRemainder);
	}

	bool BitArray::GetFirstClearBit(size_t& o_bitNumber) const{
		for (size_t index = 0; index < arraySize; index++) {
			size_t lmax = index != arraySize - 1 ? MAX : static_cast<size_t>(pow(2.0f, remainder)-1);
			if (bits[index] != lmax) {
				size_t bitIndex = 0;
				while ((bits[index] & (maskUnit << bitIndex)) && (bitIndex < (index != arraySize-1?bitsPerUnit:remainder))) {
					bitIndex++;
				}
				o_bitNumber = bitIndex + index*bitsPerUnit;
				return true;
			}
		}
		return false;
	}

	bool BitArray::GetFirstSetBit(size_t& o_bitNumber) const {
		for (size_t index = 0; index < arraySize - 1; index++) {
			if (bits[index] != 0) {
				unsigned long bitIndex;
				if (BITSCAN(&bitIndex, bits[index])) {
					o_bitNumber = bitIndex + index * bitsPerUnit;
					return true;
				}
				else {
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
			return false;
		}
		else {
			return true;
		}		
	}
}