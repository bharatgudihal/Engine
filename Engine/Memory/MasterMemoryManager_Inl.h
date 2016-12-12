#pragma once
namespace Engine {
	inline HeapManager* MasterMemoryManager::DefaultHeapManager() {
		return defaultHeapManager;
	}

	inline MasterMemoryManager* MasterMemoryManager::Instance() {
		return m_Instance;
	}
}