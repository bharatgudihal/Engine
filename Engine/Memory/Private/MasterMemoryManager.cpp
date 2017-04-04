#include "../MasterMemoryManager.h"
#include "../../Logger/Logger.h"

namespace Engine {
	namespace Memory {
		MasterMemoryManager* MasterMemoryManager::m_Instance = nullptr;
		bool MasterMemoryManager::isReady = false;

		bool MasterMemoryManager::Startup() {
			DEBUG_LOG("Starting up MasterMemoryManager\n");
			bool result = false;
			if (m_Instance == nullptr) {
				void* managerMemory = _aligned_malloc(sizeof(MasterMemoryManager), 4);
				m_Instance = new (managerMemory) MasterMemoryManager;
			}
			result = m_Instance->SetupFixedSizeAllocators();
			isReady = true;
			return result;
		}

		MasterMemoryManager::MasterMemoryManager() {
			void* heapManagerMemory = _aligned_malloc(sizeof(HeapManager), 4);
			defaultHeapManager = HeapManager::create(heapManagerMemory, HeapSize, numberOfBlockDescriptors);
		}

		bool MasterMemoryManager::SetupFixedSizeAllocators() {
			// 16 byte allocator
			FSAArray[0] = FixedSizeAllocator::Create(1600, 100, defaultHeapManager);
			// 32 byte allocator
			FSAArray[1] = FixedSizeAllocator::Create(1600, 50, defaultHeapManager);
			// 64 byte allocator
			FSAArray[2] = FixedSizeAllocator::Create(1600, 25, defaultHeapManager);
			// 128 byte allocator
			FSAArray[3] = FixedSizeAllocator::Create(1280, 10, defaultHeapManager);
			return true;
		}

		FixedSizeAllocator* MasterMemoryManager::FindFixedSizeAllocator(size_t i_size) {
			for (uint8_t index = 0; index < 4; index++) {
				if (i_size <= FSAArray[index]->unitSize - FSA_GUARD_BAND_SIZE * 2) {
					return FSAArray[index];
				}
			}
			return nullptr;
		}

		bool MasterMemoryManager::FreePointerFromFSA(void* i_ptr) {
			for (uint8_t index = 0; index < 4; index++) {
				if (FSAArray[index]->free(i_ptr)) {
					return true;
				}
			}
			return false;
		}

		void MasterMemoryManager::ShutDown() {
			if (m_Instance) {
				DEBUG_LOG("Shutting down MasterMemoryManager\n");
				delete m_Instance;
			}
		}

		MasterMemoryManager::~MasterMemoryManager() {
			for (uint8_t index = 0; index < 4; index++) {
				if (FSAArray[index] != nullptr) {
					delete FSAArray[index];
				}
			}
			isReady = false;
			if (defaultHeapManager != nullptr) {
				delete defaultHeapManager;
			}
		}
	}
}