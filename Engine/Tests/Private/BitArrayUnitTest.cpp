#include "../../Memory/BitArray.h"
#include "../BitArrayUnitTest.h"

namespace Engine {	

	void TestBitArray(size_t bitCount) {
		Engine::BitArray* pMyArray = Engine::BitArray::Create(bitCount);
		size_t bitNumber = rand() % bitCount;
		pMyArray->SetBit(bitNumber);

		size_t firstSetBit = 0;
		size_t firstClearBit = 0;

		bool foundSetBit = pMyArray->GetFirstSetBit(firstSetBit);
		assert(foundSetBit && (firstSetBit == bitNumber));

		pMyArray->ClearBit(bitNumber);
		foundSetBit = pMyArray->GetFirstSetBit(firstSetBit);
		assert(foundSetBit == false);

		for (unsigned int i = 0; i < bitCount; i++)
		{
			assert(pMyArray->IsBitClear(i) == true);
			assert(pMyArray->IsBitSet(i) == false);

			size_t bit = 0;

			pMyArray->GetFirstClearBit(bit);
			assert(bit == i);

			pMyArray->SetBit(i);

			assert(pMyArray->IsBitClear(i) == false);
			assert(pMyArray->IsBitSet(i) == true);

			bool success = pMyArray->GetFirstClearBit(bit);
			assert(((i < (bitCount - 1)) && success && (bit == (i + 1))) || ((i == (bitCount - 1)) && !success));
		}

		pMyArray->SetAll();
		assert(pMyArray->GetFirstClearBit(firstClearBit) == false);

		pMyArray->ClearAll();
		assert(pMyArray->GetFirstSetBit(firstSetBit) == false);

		delete pMyArray;
	}

	void BitArray_UnitTest()
	{		
		for (size_t i = 1; i < 33; i++) {
			TestBitArray(i);
		}
		TestBitArray(1000);
	}
}