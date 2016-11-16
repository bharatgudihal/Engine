namespace Engine {
	inline bool HeapManager::Contains(const void* ptr) const {
		return (ptr >= BLOCK && ptr <= static_cast<char*>(BLOCK) + BLOCK_SIZE);
	}

	inline HeapManager* HeapManager::create(const size_t blockSize, const uint16_t numberOfBlockDescriptors) {
		return new HeapManager(blockSize, numberOfBlockDescriptors);
	}

	inline void HeapManager::destroy() {
		_aligned_free(BLOCK);
	}
}