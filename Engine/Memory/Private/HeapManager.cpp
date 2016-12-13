#include "..\HeapManager.h"


namespace Engine {
	void HeapManager::initializeBlockDescriptors() {
		char* startingPointer = static_cast<char*>(BLOCK);
		startingPointer += BLOCK_SIZE;
		uninitializedBlocksList = (BlockDescriptor*)startingPointer;
		BlockDescriptor* head = (BlockDescriptor*)startingPointer;		
		for (uint16_t i = 0; i < NUMBER_OF_BLOCKDESCRIPTORS; i++) {
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
		availableBlockDescriptorsCount--;
		return head;
	}

	void HeapManager::returnBlockToUninitializedList(BlockDescriptor* i_blockDescriptor) {
		BlockDescriptor* head = uninitializedBlocksList;
		i_blockDescriptor->next = head;
		i_blockDescriptor->base = nullptr;
		i_blockDescriptor->size = 0;
		i_blockDescriptor->userSize = 0;
		uninitializedBlocksList = i_blockDescriptor;
		availableBlockDescriptorsCount++;
	}

	HeapManager::HeapManager(const size_t blockSize, const uint16_t numberOfBlockDescriptors) {
		size_t alignment = 4;
		BLOCK_SIZE = blockSize;
		NUMBER_OF_BLOCKDESCRIPTORS = numberOfBlockDescriptors;
		BLOCK = _aligned_malloc(BLOCK_SIZE + sizeof(BlockDescriptor)*NUMBER_OF_BLOCKDESCRIPTORS, alignment);
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
		ptrdiff_t newSize = static_cast<char*>(splitLocation) - static_cast<char*>(block->base);
		BlockDescriptor* newBlockDescriptor = getUninitializedBlock();
		newBlockDescriptor->next = nullptr;
		newBlockDescriptor->base = splitLocation;
		newBlockDescriptor->size = block->size - newSize;
		block->size = newSize;
		return newBlockDescriptor;
	}

	void* HeapManager::padBlockAndReturnPointer(char* assignedPointer, const size_t i_size) {
		char* pointer = assignedPointer;
		for (uint8_t i = 0; i < GUARD_BAND_SIZE; i++) {
			*pointer = GUARD_BAND_FILL;
			pointer++;
		}
		pointer += i_size;
		for (uint8_t i = 0; i < GUARD_BAND_SIZE; i++) {
			*pointer = GUARD_BAND_FILL;
			pointer++;
		}
		pointer = assignedPointer;
		return pointer + GUARD_BAND_SIZE;
	}

	void HeapManager::putBlockInAssignedBlockList(BlockDescriptor* assignedBlock) {
		assignedBlock->next = nullptr;
		BlockDescriptor* head = assignedBlocksList;
		assignedBlocksList = assignedBlock;
		assignedBlocksList->next = head;
	}

	void HeapManager::removeBlockFromFreeBlocksList(const BlockDescriptor* assignedBlock) {
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

	void* HeapManager::getPointerFromFreeBlocks(const size_t i_size, const uint8_t alignment) {
		void* memoryLocation = nullptr;
		BlockDescriptor* head = freeBlocksList;
		do {
			if (head->size > i_size + GUARD_BAND_SIZE * 2) {
				char* pointer = static_cast<char*>(head->base) + head->size - 1 - GUARD_BAND_SIZE - i_size;				
				pointer = reinterpret_cast<size_t>(pointer) % alignment == 0 ? pointer : pointer - ((reinterpret_cast<size_t>(pointer) % alignment));
				pointer -= GUARD_BAND_SIZE;
				ptrdiff_t blockSize = static_cast<char*>(head->base) + head->size - 1 - static_cast<char*>(pointer);
				if (pointer > head->base && (pointer + blockSize) < (static_cast<char*>(head->base) + head->size)) {
					BlockDescriptor* assignedBlock;
					if (pointer - static_cast<char*>(head->base) >= MIN_BLOCK_SIZE) {
						assignedBlock = splitAndReturnBlock(head, pointer);
						memoryLocation = padBlockAndReturnPointer(static_cast<char*>(assignedBlock->base), i_size);
					}
					else {
						assignedBlock = head;
						memoryLocation = padBlockAndReturnPointer(pointer, i_size);
					}
					assert(!IsAllocated(memoryLocation));
					removeBlockFromFreeBlocksList(assignedBlock);
					assignedBlock->userSize = i_size;					
					putBlockInAssignedBlockList(assignedBlock);
					break;
				}
				else {
					head = head->next;
				}
			}
			else {
				head = head->next;
			}
		} while (head != nullptr);
		return memoryLocation;
	}

	HeapManager::BlockDescriptor* HeapManager::joinBlocks(BlockDescriptor* sourceBlock, BlockDescriptor* blockToBeJoined, BlockDescriptor* previousBlock) {
		BlockDescriptor* returnBlock = blockToBeJoined->next;
		sourceBlock->size += blockToBeJoined->size;
		// If first block in the freeBlocksList is to be joined with the source block
		if (previousBlock == nullptr) {
			freeBlocksList = blockToBeJoined->next;
		}
		else {
			previousBlock->next = blockToBeJoined->next;
		}
		returnBlockToUninitializedList(blockToBeJoined);
		return returnBlock;
	}

	void HeapManager::runGarbageCollector() {
		BlockDescriptor* outerHead = freeBlocksList;
		while (outerHead != nullptr) {
			char* endOfBlock = static_cast<char*>(outerHead->base) + outerHead->size;
			BlockDescriptor* innerHead = freeBlocksList;
			BlockDescriptor* previousBlock = nullptr;
			while (innerHead != nullptr) {
				if (endOfBlock == innerHead->base) {
					innerHead = joinBlocks(outerHead, innerHead, previousBlock);
					endOfBlock = static_cast<char*>(outerHead->base) + outerHead->size;					
				}
				else {
					previousBlock = innerHead;
					innerHead = innerHead->next;					
				}
			}
			outerHead = outerHead->next;			
		}
	}

	void * HeapManager::allocate(const size_t i_size, const uint8_t alignment) {
		void* ptr = nullptr;
		assert(i_size <= BLOCK_SIZE);
		if (availableBlockDescriptorsCount == 0) {
			return ptr;
		}		
		ptr = getPointerFromFreeBlocks(i_size, alignment);
		return ptr;
	}

	void * HeapManager::allocate(const size_t i_size) {
		uint8_t alignment = 4;
		return allocate(i_size, alignment);
	}

	void HeapManager::checkGuardBands(void* i_ptr, const BlockDescriptor* assignedBlock) {
		char* pointer = static_cast<char*>(i_ptr);
		pointer -= GUARD_BAND_SIZE;
		size_t i;
		for (i = 0; i < GUARD_BAND_SIZE; i++) {
			assert(static_cast<uint8_t>(*pointer) == GUARD_BAND_FILL);
			*pointer = FREE_BLOCKS_FILL;
			pointer++;
		}
		for (i = 0; i < assignedBlock->userSize; i++) {
			*pointer = FREE_BLOCKS_FILL;
			pointer++;
		}
		for (i = 0; i < GUARD_BAND_SIZE; i++) {
			assert(static_cast<uint8_t>(*pointer) == GUARD_BAND_FILL);
			*pointer = FREE_BLOCKS_FILL;
			pointer++;
		}
	}

	HeapManager::BlockDescriptor* HeapManager::findBlockForPointer(const void* ptr) {
		BlockDescriptor* assignedBlock = nullptr;
		BlockDescriptor* head = assignedBlocksList;
		BlockDescriptor* previousHead = nullptr;
		while (head != nullptr) {
			if (ptr >= head->base && ptr <= static_cast<char*>(head->base) + head->size - 1) {
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
		BlockDescriptor* previous = nullptr;
		bool isInserted = false;
		while (head != nullptr) {
			if (head->base > assignedBlock->base) {
				if (previous != nullptr) {
					previous->next = assignedBlock;
					assignedBlock->next = head;
					isInserted = true;
					break;
				}
				else {
					freeBlocksList = assignedBlock;
					freeBlocksList->next = head;
					isInserted = true;
					break;
				}
			}
			else {
				previous = head;
				head = head->next;
			}
		}
		// If this block is the last block
		if (!isInserted) {
			previous->next = assignedBlock;
			assignedBlock->next = head;
		}
	}

	bool HeapManager::free(void* ptr) {
		assert(IsAllocated(ptr));
		bool result = false;
		BlockDescriptor* assignedBlock = findBlockForPointer(ptr);
		assert(assignedBlock != nullptr);
		checkGuardBands(ptr, assignedBlock);
		addBlockToFreeBlocksList(assignedBlock);		
		result = true;
		return result;
	}

	void HeapManager::LogHeaps() const {		
		uint16_t count = 0;
		DEBUG_LOG("==============Log Started==============\n");
		DEBUG_LOG("Number of available block descriptors: %d\n", availableBlockDescriptorsCount);
		BlockDescriptor* head = freeBlocksList;
		count = 0;
		DEBUG_LOG("Free blocks:\n");
		while (head != nullptr) {
			count++;
			DEBUG_LOG("Free block number: %d \n", count);
			DEBUG_LOG("Free block size: %d \n", head->size);
			head = head->next;
		}
		head = assignedBlocksList;
		count = 0;
		DEBUG_LOG("Assigned blocks:\n");
		while (head != nullptr) {
			count++;
			DEBUG_LOG("Assigned block number: %d \n", count);
			DEBUG_LOG("Assigned block size: %d \n", head->size);
			DEBUG_LOG("Assigned block user size: %d \n", head->userSize);
			head = head->next;
		}
		DEBUG_LOG("==============Log Ended==============\n");
	}

	void HeapManager::ShowFreeBlocks() const {
		size_t totalSize = 0;
		BlockDescriptor* head = freeBlocksList;
		uint16_t count = 0;
		while (head != nullptr) {
			count++;
			printf("Free block number: %d \n", count);
			printf("Free block size: %zd \n", head->size);
			totalSize += head->size;
			head = head->next;
		}
		printf("Total size of free blocks: %zd\n", totalSize);
		if (count == 0) {
			printf("No Free blocks left\n");
		}
	}

	void HeapManager::ShowOutstandingAllocations() const {
		BlockDescriptor* head = assignedBlocksList;
		size_t totalSize = 0;
		uint16_t count = 0;
		while (head != nullptr) {
			count++;
			printf("Assigned block number: %d \n", count);
			printf("Assigned block size: %zd \n", head->size);
			printf("Assigned block user size: %zd \n", head->userSize);
			totalSize += head->size;
			head = head->next;
		}
		printf("Total size of allocated blocks: %zd\n", totalSize);
	}	

	bool HeapManager::IsAllocated(const void* ptr) const {
		bool result = false;		
		BlockDescriptor* head = assignedBlocksList;		
		while (head != nullptr) {
			if (ptr >= head->base && ptr <= static_cast<char*>(head->base) + head->size) {								
				result = true;
				break;
			}
			else {				
				head = head->next;
			}
		}
		return result;
	}

	size_t HeapManager::GetLargestFreeBlock() const {
		size_t maxSize = 0;
		BlockDescriptor* head = freeBlocksList;
		while (head != nullptr) {
			if (head->size > maxSize) {
				maxSize = head->size;
			}
			head = head->next;
		}
		return maxSize;
	}

	HeapManager::~HeapManager() {
		if (assignedBlocksList != nullptr) {
			DEBUG_LOG("There are still outstanding allocations!\n");
		}
		_aligned_free(BLOCK);
	}
}