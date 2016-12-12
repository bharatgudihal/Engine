#pragma once
namespace Engine {
	inline FixedSizeAllocator* FixedSizeAllocator::Create(size_t i_blockSize, size_t i_units, HeapManager* i_heapManager) {
		return new FixedSizeAllocator(i_blockSize, i_units, i_heapManager);
	}

	inline bool FixedSizeAllocator::AreAllAllocated() {
		return bitArray->AreAllClear();
	}

	inline bool FixedSizeAllocator::AreAllFreed() {
		return bitArray->AreAllSet();
	}
}