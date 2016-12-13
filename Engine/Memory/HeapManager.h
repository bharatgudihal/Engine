#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H
#ifdef _DEBUG
	#define GUARD_BAND_SIZE 2	
#else
	#define GUARD_BAND_SIZE 0	
#endif // _DEBUG
#include <stdint.h>
#include <assert.h>
#include <malloc.h>
#include <algorithm>
#include "..\Logger\Logger.h"

#define MIN_BLOCK_SIZE 16

namespace Engine {
	class HeapManager {
	public:
		~HeapManager();
		inline static HeapManager* create(void* i_ptr,const size_t blockSize, const uint16_t numberOfBlockDescriptors);
		void* allocate(const size_t size);
		void* allocate(const size_t size, const uint8_t alignment);
		bool free(void * pointer);
		void runGarbageCollector();
		void ShowFreeBlocks() const;
		void ShowOutstandingAllocations() const;
		inline bool Contains(const void* ptr) const;
		bool IsAllocated(const void* ptr) const;
		size_t GetLargestFreeBlock() const;
		const static size_t s_MinumumToLeave = MIN_BLOCK_SIZE*2;

	private:
		HeapManager(const size_t blockSize, const uint16_t numberOfBlockDescriptors);		
		struct BlockDescriptor {
			BlockDescriptor* next;
			size_t size;
			size_t userSize;
			void* base;
		};
		size_t BLOCK_SIZE;
		uint16_t NUMBER_OF_BLOCKDESCRIPTORS;
		uint8_t GUARD_BAND_FILL = 0xBB;
		uint8_t FREE_BLOCKS_FILL = 0xCD;
		uint16_t availableBlockDescriptorsCount;
		void* BLOCK;
		void* BLOCKDESCRIPTOR_POOL;
		BlockDescriptor* freeBlocksList;
		BlockDescriptor* assignedBlocksList;
		BlockDescriptor* uninitializedBlocksList;
		void* getPointerFromFreeBlocks(const size_t size, const uint8_t alignment);
		BlockDescriptor* splitAndReturnBlock(BlockDescriptor* block, void* splitLocation);
		void initializeBlockDescriptors();
		BlockDescriptor* getUninitializedBlock();
		void returnBlockToUninitializedList(BlockDescriptor* i_blockDescriptor);
		void* padBlockAndReturnPointer(char* assignedPointer, const size_t i_size);
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