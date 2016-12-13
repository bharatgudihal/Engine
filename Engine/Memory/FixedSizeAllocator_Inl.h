#pragma once
namespace Engine {
	inline FixedSizeAllocator* FixedSizeAllocator::Create(const size_t i_blockSize, const size_t i_units, HeapManager* i_heapManager) {
		return new FixedSizeAllocator(i_blockSize, i_units, i_heapManager);
	}

	inline bool FixedSizeAllocator::AreAllAllocated() const{
		return bitArray->AreAllClear();
	}

	inline bool FixedSizeAllocator::AreAllFreed() const{
		return bitArray->AreAllSet();
	}
}