namespace Engine {
	inline bool HeapManager::Contains(const void* ptr) const {
		return (ptr >= BLOCK && ptr <= static_cast<char*>(BLOCK) + BLOCK_SIZE);
	}

	inline HeapManager* HeapManager::create(void* i_ptr, const size_t blockSize, const uint16_t numberOfBlockDescriptors) {
		return new (i_ptr) HeapManager(blockSize, numberOfBlockDescriptors);
	}
}