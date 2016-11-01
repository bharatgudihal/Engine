#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H
#define GUARD_BAND_SIZE 2
#define MIN_BLOCK_SIZE 16

namespace Engine {
	class HeapManager {
	public:
		HeapManager(size_t blockSize, unsigned int numberOfBlockDescriptors);
		~HeapManager();
		void* allocate(size_t size);
		bool free(void * pointer);
		void runGarbageCollector();
		void ShowFreeBlocks();
		void ShowOutstandingAllocations();
		inline bool Contains(void* ptr);
		bool IsAllocated(void* ptr);
		size_t GetLargestFreeBlock();
		const static size_t s_MinumumToLeave = MIN_BLOCK_SIZE*2;

	private:
		struct BlockDescriptor {
			BlockDescriptor* next;
			size_t size;
			size_t userSize;
			void* base;
		};
		size_t BLOCK_SIZE;
		unsigned int NUMBER_OF_BLOCKDESCRIPTORS;
		unsigned char GUARD_BAND_FILL = 0xBB;
		unsigned char FREE_BLOCKS_FILL = 0xCD;
		unsigned int availableBlockDescriptorsCount;
		void* BLOCK;
		void* BLOCKDESCRIPTOR_POOL;
		BlockDescriptor* freeBlocksList;
		BlockDescriptor* assignedBlocksList;
		BlockDescriptor* uninitializedBlocksList;
		void* getPointerFromFreeBlocks(size_t size);
		BlockDescriptor* splitAndReturnBlock(BlockDescriptor* block, void* splitLocation);
		void initializeBlockDescriptors();
		BlockDescriptor* getUninitializedBlock();
		void returnBlockToUninitializedList(BlockDescriptor* i_blockDescriptor);
		void* padBlockAndReturnPointer(BlockDescriptor* assignedBlock, size_t i_size);
		void putBlockInAssignedBlockList(BlockDescriptor* assignedBlock);
		void removeBlockFromFreeBlocksList(BlockDescriptor* assignedBlock);
		BlockDescriptor* findBlockForPointer(void* ptr);
		void checkGuardBands(void* ptr, BlockDescriptor* assignedBlock);
		void addBlockToFreeBlocksList(BlockDescriptor* assignedBlock);		
		BlockDescriptor* joinBlocks(BlockDescriptor* firstBlock, BlockDescriptor* secondBlock, BlockDescriptor* previousBlock);
		void LogHeaps();
	};
}
#include "HeapManager_Inl.h"
#endif // !MEMORY_ALLOCATOR_H