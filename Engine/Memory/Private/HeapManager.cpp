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
	head->next = i_blockDescriptor;
}

HeapManager::HeapManager() {
	BLOCK = _aligned_malloc(BLOCK_SIZE+ sizeof(BlockDescriptor)*NUMBER_OF_BLOCKDESCRIPTORS, 4);
	initializeBlockDescriptors();
	// Initialize free blocks list
	freeBlocksList = getUninitializedBlock();
	freeBlocksList->next = nullptr;
	freeBlocksList->base = BLOCK;
	freeBlocksList->size = BLOCK_SIZE;
	availableBlockDescriptorsCount = NUMBER_OF_BLOCKDESCRIPTORS-1;
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
	if (assignedBlocksList == nullptr) {
		assignedBlocksList = assignedBlock;
	}
	else {
		BlockDescriptor* head = assignedBlocksList;
		while (head->next != nullptr) {
			head = head->next;
		}
		head->next = assignedBlock;
	}
}

void HeapManager::removeBlockFromFreeBlocksList(BlockDescriptor* assignedBlock) {
	BlockDescriptor* head = freeBlocksList;
	while (head->next != nullptr) {
		if (head->next == assignedBlock) {
			head->next = assignedBlock->next;			
		}
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
				removeBlockFromFreeBlocksList(current);				
				putBlockInAssignedBlockList(current);
				break;
			}
		}
	} while (current->next != nullptr);
	return memoryLocation;
}

void * HeapManager::allocate(size_t i_size) {
	assert((int)i_size <= BLOCK_SIZE);	
	assert(NUMBER_OF_BLOCKDESCRIPTORS != 0);
	void* ptr;
	ptr = getPointerFromFreeBlocks(i_size);
	assert(ptr != nullptr);
	return ptr;
}