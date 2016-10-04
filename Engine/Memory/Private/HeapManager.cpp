#include "..\HeapManager.h"
#include <assert.h>

void HeapManager::initializeBlockDescriptors() {
	char* startingPointer = (char*)BLOCK;
	startingPointer += BLOCK_SIZE;
	uninitializedBlocksList = (BlockDescriptor*)startingPointer;
	BlockDescriptor* head = (BlockDescriptor*)startingPointer;
	for (int i = 0; i < NUMBER_OF_BLOCKDESCRIPTORS; i++) {
		head->base = nullptr;
		head->size = 0;
		head->userSize = 0;
		startingPointer += sizeof(BlockDescriptor);
		if (i != NUMBER_OF_BLOCKDESCRIPTORS - 1) {
			head->next = (BlockDescriptor*)startingPointer;
			head = head->next;
		}
		else {
			head->next = nullptr;
		}
	}
}

HeapManager::BlockDescriptor* HeapManager::getUninitializedBlock() {
	assert(uninitializedBlocksList != nullptr);
	BlockDescriptor* head = uninitializedBlocksList;
	uninitializedBlocksList = head->next;
	return head;
}

void HeapManager::returnBlockToUninitializedList(BlockDescriptor* i_blockDescriptor) {
	BlockDescriptor* head = uninitializedBlocksList;
	i_blockDescriptor->next = nullptr;
	i_blockDescriptor->base = nullptr;
	i_blockDescriptor->size = 0;
	i_blockDescriptor->userSize = 0;
	uninitializedBlocksList = i_blockDescriptor;
	uninitializedBlocksList->next = head;
}

HeapManager::HeapManager() {
	BLOCK = _aligned_malloc(BLOCK_SIZE + sizeof(BlockDescriptor)*NUMBER_OF_BLOCKDESCRIPTORS, 4);
	initializeBlockDescriptors();
	// Initialize free blocks list
	freeBlocksList = getUninitializedBlock();
	freeBlocksList->next = nullptr;
	freeBlocksList->base = BLOCK;
	freeBlocksList->size = BLOCK_SIZE;
	availableBlockDescriptorsCount = NUMBER_OF_BLOCKDESCRIPTORS - 1;
	assignedBlocksList = nullptr;
}

HeapManager::BlockDescriptor* HeapManager::splitAndReturnBlock(BlockDescriptor* block, void* splitLocation) {
	int newSize = (char*)splitLocation - (char*)block->base;
	BlockDescriptor* newBlockDescriptor = getUninitializedBlock();
	newBlockDescriptor->next = nullptr;
	newBlockDescriptor->base = splitLocation;
	newBlockDescriptor->size = block->size - newSize;
	block->size = newSize;
	return newBlockDescriptor;
}

void* HeapManager::padBlockAndReturnPointer(BlockDescriptor* assignedBlock, int i_size) {
	char* pointer = (char*)assignedBlock->base;
	for (int i = 0; i < GUARD_BAND_SIZE; i++) {
		*pointer = GUARD_BAND_FILL;
		pointer++;
	}
	pointer += i_size;
	for (int i = 0; i < GUARD_BAND_SIZE; i++) {
		*pointer = GUARD_BAND_FILL;
		pointer++;
	}
	pointer = (char*)assignedBlock->base;
	return pointer + GUARD_BAND_SIZE;
}

void HeapManager::putBlockInAssignedBlockList(BlockDescriptor* assignedBlock) {
	assignedBlock->next = nullptr;
	BlockDescriptor* head = assignedBlocksList;
	assignedBlocksList = assignedBlock;
	assignedBlocksList->next = head;
}

void HeapManager::removeBlockFromFreeBlocksList(BlockDescriptor* assignedBlock) {
	BlockDescriptor* head = freeBlocksList;
	while (head != nullptr) {
		if (head == assignedBlock) {
			freeBlocksList = head->next;
			break;
		}
		if (head->next == assignedBlock) {
			head->next = assignedBlock->next;
			break;
		}
		head = head->next;
	}
}

void* HeapManager::getPointerFromFreeBlocks(size_t i_size) {
	void* memoryLocation = nullptr;
	BlockDescriptor* current = freeBlocksList;
	do {
		if (current->size > i_size + GUARD_BAND_SIZE * 2) {
			char* pointer = (char*)current->base + current->size - GUARD_BAND_SIZE * 2 - i_size;
			pointer = *pointer % 4 == 0 ? pointer : pointer - (4 - *pointer % 4);
			if (pointer > current->base) {
				BlockDescriptor* assignedBlock;
				if (pointer - (char*)current->base >= MIN_BLOCK_SIZE) {
					assignedBlock = splitAndReturnBlock(current, pointer);
				}
				else {
					assignedBlock = current;
				}
				memoryLocation = padBlockAndReturnPointer(assignedBlock, i_size);
				removeBlockFromFreeBlocksList(assignedBlock);
				assignedBlock->userSize = i_size;
				putBlockInAssignedBlockList(assignedBlock);
				break;
			}
		}
	} while (current->next != nullptr);
	return memoryLocation;
}

void * HeapManager::allocate(size_t i_size) {
	assert((int)i_size <= BLOCK_SIZE);
	assert(availableBlockDescriptorsCount != 0);
	void* ptr;
	ptr = getPointerFromFreeBlocks(i_size);
	assert(ptr != nullptr);
	return ptr;
}

void HeapManager::checkGuardBands(void* i_ptr, BlockDescriptor* assignedBlock) {
	char* pointer = (char*)i_ptr;
	pointer -= GUARD_BAND_SIZE;
	int i;
	for (i = 0; i < GUARD_BAND_SIZE; i++) {
		assert((unsigned char)*pointer == GUARD_BAND_FILL);
		*pointer = FREE_BLOCKS_FILL;
		pointer++;
	}
	for (i = 0; i < assignedBlock->userSize; i++) {
		*pointer = FREE_BLOCKS_FILL;
		pointer++;
	}
	for (i = 0; i < GUARD_BAND_SIZE; i++) {
		assert((unsigned char)*pointer == GUARD_BAND_FILL);
		*pointer = FREE_BLOCKS_FILL;
		pointer++;
	}
}

HeapManager::BlockDescriptor* HeapManager::findBlockForPointer(void* ptr) {
	BlockDescriptor* assignedBlock = nullptr;
	BlockDescriptor* head = assignedBlocksList;
	BlockDescriptor* previousHead = nullptr;
	while (head != nullptr) {
		if (ptr >= head->base && ptr <= (char*)head->base + head->size) {
			assignedBlock = head;
			// Remove block from assigned blocks list
			if (previousHead == nullptr) {
				assignedBlocksList = head->next;
			}
			else {
				previousHead->next = head->next;
			}
			break;
		}
		else {
			previousHead = head;
			head = head->next;
		}
	}
	return assignedBlock;
}

void HeapManager::addBlockToFreeBlocksList(BlockDescriptor* assignedBlock) {
	assignedBlock->userSize = 0;
	BlockDescriptor* head = freeBlocksList;
	freeBlocksList = assignedBlock;
	freeBlocksList->next = head;
}

void HeapManager::free(void* ptr) {
	BlockDescriptor* assignedBlock = findBlockForPointer(ptr);
	assert(assignedBlock != nullptr);
	checkGuardBands(ptr, assignedBlock);
	addBlockToFreeBlocksList(assignedBlock);
}