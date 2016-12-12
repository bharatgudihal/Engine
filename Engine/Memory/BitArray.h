#pragma once
#include "HeapManager.h"
namespace Engine {
	class BitArray {
	#ifdef _WIN64
	#define BITSCAN(index,mask) _BitScanForward64(index,mask)	
	#else
	#define BITSCAN(index,mask) _BitScanForward(index,mask)	
	#endif
	public:
		inline static BitArray* Create(size_t i_numberOfBits, bool i_startClear, HeapManager* heapManager);
		inline static BitArray* Create(size_t i_numberOfBits);
		~BitArray();
		inline void ClearAll();
		void SetAll();
		bool AreAllClear() const;
		bool AreAllSet() const;
		bool IsBitSet(size_t i_bitNumber) const;
		inline bool IsBitClear(size_t i_bitNumber) const;
		void SetBit(size_t i_bitNumber);
		void ClearBit(size_t i_bitNumber);
		bool GetFirstClearBit(size_t& o_bitNumber) const;
		bool GetFirstSetBit(size_t& o_bitNumber) const;

	private:
		BitArray(size_t i_numberOfBits, bool i_startClear, HeapManager* heapManager);
		BitArray(size_t i_numberOfBits);
		size_t* bits;
		size_t arraySize;
		size_t numberOfBits;
		size_t remainder;
		const size_t bitsPerByte = 8;
		const size_t bitsPerUnit = (sizeof(size_t)*bitsPerByte);
		const size_t maskUnit = 1;
		#ifdef _WIN64
		const size_t MAX = UINT64_MAX;
		#else
		const size_t MAX = UINT32_MAX;
		#endif
	};
}
#include "BitArray_Inl.h"