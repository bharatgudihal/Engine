#include "../FixedSizeAllocator.h"
#include "../../Logger/Logger.h"

namespace Engine {
	namespace Memory {
		FixedSizeAllocator::FixedSizeAllocator(size_t i_blockSize, size_t i_units, HeapManager* i_heapManager) {
			blockSize = i_blockSize + FSA_GUARD_BAND_SIZE * i_units * 2;
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
			assert(blockBase);
			uint8_t* ptr = static_cast<uint8_t*>(blockBase);
			uint8_t* bitArrayPointer = ptr;
			bitArray = BitArray::Create(units, bitArrayPointer, bitArrayPointer + sizeof(BitArray));
			ptr += sizeof(BitArray) + (sizeof(size_t) * arraySize);
			workingBase = ptr;
			DEBUG_LOG("FSA created for size %zd bytes\n", unitSize);
		}

		FixedSizeAllocator::~FixedSizeAllocator() {
			if (!bitArray->AreAllSet()) {
				DEBUG_LOG("FSA FOR SIZE %zd BYTES HAS ALLOCATIONS PENDING!\n", unitSize);
			}
			DEBUG_LOG("FSA destroyed for size %zd bytes\n", unitSize);
			heapManager->free(blockBase);
		}

		void FixedSizeAllocator::AddGuardBands(uint8_t* userPointer) const {
			for (uint8_t count = 0; count < FSA_GUARD_BAND_SIZE; count++) {
				*(userPointer) = FSA_GUARD_BAND_FILL;
				userPointer++;
			}
			userPointer += unitSize - FSA_GUARD_BAND_SIZE * 2;
			for (uint8_t count = 0; count < FSA_GUARD_BAND_SIZE; count++) {
				*(userPointer) = FSA_GUARD_BAND_FILL;
				userPointer++;
			}
		}

		void* FixedSizeAllocator::allocate() {
			//DEBUG_LOG("Allocating from FSA for size %zd bytes\n", unitSize);
			size_t index = 0;
			if (bitArray->GetFirstSetBit(index)) {
				bitArray->ClearBit(index);
				uint8_t* userPointer = reinterpret_cast<uint8_t*>(workingBase) + (unitSize * index);
				AddGuardBands(userPointer);
				return userPointer + FSA_GUARD_BAND_SIZE;
			}
			else {
				return nullptr;
			}
		}

		bool FixedSizeAllocator::free(void* ptr) {
			size_t index = 0;
			if (isValid(ptr, index)) {
				bitArray->SetBit(index);
				//DEBUG_LOG("Freeing from FSA for size %zd bytes\n", unitSize);
				return true;
			}
			else {
				return false;
			}
		}

		void FixedSizeAllocator::CheckGuardBands(void* i_ptr) const {
			uint8_t* checkPointer = static_cast<uint8_t*>(i_ptr);
			for (uint8_t count = 0; count < FSA_GUARD_BAND_SIZE; count++) {
				assert(*checkPointer == FSA_GUARD_BAND_FILL);
				checkPointer++;
			}
			checkPointer += unitSize - FSA_GUARD_BAND_SIZE * 2;
			for (uint8_t count = 0; count < FSA_GUARD_BAND_SIZE; count++) {
				assert(*checkPointer == FSA_GUARD_BAND_FILL);
				checkPointer++;
			}
		}

		bool FixedSizeAllocator::isValid(void* ptr, size_t& o_index) const {
			uint8_t* address = static_cast<uint8_t*>(ptr);
			address -= FSA_GUARD_BAND_SIZE;
			ptrdiff_t addressDiff = address - workingBase;
			if (addressDiff >= 0 && addressDiff % unitSize == 0) {
				o_index = addressDiff / unitSize;
				if (bitArray->IsBitClear(o_index)) {
					CheckGuardBands(address);
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
}