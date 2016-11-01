namespace Engine {
	inline bool HeapManager::Contains(void* ptr) {
		return (ptr >= BLOCK && ptr <= static_cast<char*>(BLOCK) + BLOCK_SIZE);
	}
}