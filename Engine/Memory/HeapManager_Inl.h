namespace Engine {
	inline bool HeapManager::Contains(const void* ptr) const {
		return (ptr >= BLOCK && ptr <= static_cast<char*>(BLOCK) + BLOCK_SIZE);
	}
}