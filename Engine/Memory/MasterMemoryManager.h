#pragma once
#include "FixedSizeAllocator.h"
namespace Engine {
	namespace Memory {
		class MasterMemoryManager {
		public:
			static bool Startup();
			inline static MasterMemoryManager* Instance();
			inline HeapManager* DefaultHeapManager();
			FixedSizeAllocator* FindFixedSizeAllocator(size_t i_size);
			bool FreePointerFromFSA(void* i_ptr);
			static void ShutDown();
			~MasterMemoryManager();
			static bool isReady;

		private:
			MasterMemoryManager();
			HeapManager* defaultHeapManager;
			FixedSizeAllocator* FSAArray[4];
			static MasterMemoryManager* m_Instance;
			bool SetupFixedSizeAllocators();
			const size_t HeapSize = 1024*1000;
			const uint16_t numberOfBlockDescriptors = 400;
		};
	}
}
#include "MasterMemoryManager_Inl.h"