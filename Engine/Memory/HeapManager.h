#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H
#define GUARD_BAND_SIZE 2
#define MIN_BLOCK_SIZE 16

namespace Engine {
	class HeapManager {
	public:
		HeapManager(const size_t blockSize, const unsigned int numberOfBlockDescriptors);
		~HeapManager();
		void* allocate(const size_t size);
		bool free(void * pointer);
		void runGarbageCollector();
		void ShowFreeBlocks() const;
		void ShowOutstandingAllocations() const;
		inline bool Contains(const void* ptr) const;
		bool IsAllocated(const void* ptr) const;
		size_t GetLargestFreeBlock() const;
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
		void* getPointerFromFreeBlocks(const size_t size);
		BlockDescriptor* splitAndReturnBlock(BlockDescriptor* block, void* splitLocation);
		void initializeBlockDescriptors();
		BlockDescriptor* getUninitializedBlock();
		void returnBlockToUninitializedList(BlockDescriptor* i_blockDescriptor);
		void* padBlockAndReturnPointer(BlockDescriptor* assignedBlock, const size_t i_size);
		void putBlockInAssignedBlockList(BlockDescriptor* assignedBlock);
		void removeBlockFromFreeBlocksList(const BlockDescriptor* assignedBlock);
		BlockDescriptor* findBlockForPointer(const void* ptr);
		void checkGuardBands(void* ptr, const BlockDescriptor* assignedBlock);
		void addBlockToFreeBlocksList(BlockDescriptor* assignedBlock);		
		BlockDescriptor* joinBlocks(BlockDescriptor* firstBlock, BlockDescriptor* secondBlock, BlockDescriptor* previousBlock);
		void LogHeaps() const;
	};
}
#include "HeapManager_Inl.h"
#endif // !MEMORY_ALLOCATOR_H