#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H
#define GUARD_BAND_SIZE 2
#define NUMBER_OF_BLOCKDESCRIPTORS 4
#define BLOCK_SIZE 52
#define MIN_BLOCK_SIZE 16
#include <malloc.h>
class HeapManager {
	public:
		HeapManager();
		void * allocate(size_t size);
		void free(void * pointer);

	private:
		struct BlockDescriptor {
			BlockDescriptor* next;
			void* base;
			size_t size;
		};
		unsigned char GUARD_BAND_FILL = 0xBB;
		int availableBlockDescriptorsCount;
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
		void* padBlockAndReturnPointer(BlockDescriptor* assignedBlock, int i_size);
		void putBlockInAssignedBlockList(BlockDescriptor* assignedBlock);
		void removeBlockFromFreeBlocksList(BlockDescriptor* assignedBlock);
};
#endif // !MEMORY_ALLOCATOR_H
