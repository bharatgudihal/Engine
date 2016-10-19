#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H
#define GUARD_BAND_SIZE 2
#define MIN_BLOCK_SIZE 16

namespace Engine {
	class HeapManager {
	public:
		HeapManager(size_t blockSize, int numberOfBlockDescriptors);
		void* allocate(size_t size);
		void free(void * pointer);

	private:
		struct BlockDescriptor {
			BlockDescriptor* next;
			size_t size;
			size_t userSize;
			void* base;
		};
		size_t BLOCK_SIZE;
		int NUMBER_OF_BLOCKDESCRIPTORS;
		unsigned char GUARD_BAND_FILL = 0xBB;
		unsigned char FREE_BLOCKS_FILL = 0xCD;
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
		void* padBlockAndReturnPointer(BlockDescriptor* assignedBlock, size_t i_size);
		void putBlockInAssignedBlockList(BlockDescriptor* assignedBlock);
		void removeBlockFromFreeBlocksList(BlockDescriptor* assignedBlock);
		BlockDescriptor* findBlockForPointer(void* ptr);
		void checkGuardBands(void* ptr, BlockDescriptor* assignedBlock);
		void addBlockToFreeBlocksList(BlockDescriptor* assignedBlock);
		void runGarbageCollector();
		BlockDescriptor* joinBlocks(BlockDescriptor* firstBlock, BlockDescriptor* secondBlock, BlockDescriptor* previousBlock);
		void LogHeaps();
	};
}
#endif // !MEMORY_ALLOCATOR_H
