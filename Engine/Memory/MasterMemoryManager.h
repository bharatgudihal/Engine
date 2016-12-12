#pragma once
#include "FixedSizeAllocator.h"
namespace Engine {
	class MasterMemoryManager {
	public:
		static bool Startup();
		inline static MasterMemoryManager* Instance();
		inline HeapManager* DefaultHeapManager();
		FixedSizeAllocator* FindFixedSizeAllocator(size_t i_size);
		bool FreePointerFromFSA(void* i_ptr);
		static void ShutDown();
		~MasterMemoryManager();

	private:
		MasterMemoryManager();
		HeapManager* defaultHeapManager;
		FixedSizeAllocator* FSAArray[4];
		static MasterMemoryManager* m_Instance;
		bool SetupFixedSizeAllocators();
	};
}
#include "MasterMemoryManager_Inl.h"