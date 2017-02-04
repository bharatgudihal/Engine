#pragma once
namespace Engine {
	namespace Memory {
		inline HeapManager* MasterMemoryManager::DefaultHeapManager() {
			return defaultHeapManager;
		}

		inline MasterMemoryManager* MasterMemoryManager::Instance() {
			return m_Instance;
		}
	}
}