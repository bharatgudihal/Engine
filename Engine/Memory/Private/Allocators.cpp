#include "../Allocators.h"

void* operator new (size_t i_size) {
	DEBUG_LOG("Allocated for size %d\n", i_size);
	return _aligned_malloc(i_size, 4);
}

void operator delete (void* i_ptr) {
	assert(i_ptr);
	DEBUG_LOG("Freeing pointer %p\n", i_ptr);
	uint8_t* pointer = static_cast<uint8_t*>(i_ptr);
	pointer -= sizeof(HEAP_PATTERN);
	if (*pointer == HEAP_PATTERN) {
		pointer -= sizeof(Engine::HeapManager*);
		Engine::HeapManager* pHeapManager = reinterpret_cast<Engine::HeapManager*>(*pointer);
		pHeapManager->free(pointer);
	}
	else {
		_aligned_free(i_ptr);
	}	
}

void* operator new (size_t i_size, uint8_t alignment) {
	DEBUG_LOG("Allocated for size %d and alignment %d\n", i_size, alignment);
	return _aligned_malloc(i_size, alignment);
}

void operator delete (void* i_ptr, uint8_t alignment) {
	assert(i_ptr);
	DEBUG_LOG("Freeing pointer %p\n", i_ptr);
	_aligned_free(i_ptr);
}

void* operator new[](size_t i_size) {
	return _aligned_malloc(i_size, 4);
}

void operator delete[](void* i_ptr) {
	assert(i_ptr);
	_aligned_free(i_ptr);
}

void* operator new (size_t i_size, Engine::HeapManager* pHeapManager) {
	size_t totalSize = i_size + sizeof(pHeapManager) + sizeof(HEAP_PATTERN);
	uint8_t* pointer = static_cast<uint8_t*>(pHeapManager->allocate(i_size));
	Engine::HeapManager** temp = reinterpret_cast<Engine::HeapManager**>(pointer);
	*temp = pHeapManager;
	pointer += sizeof(pHeapManager);
	*pointer = HEAP_PATTERN;
	pointer += sizeof(HEAP_PATTERN);
	return pointer;
}

void operator delete (void* i_ptr, Engine::HeapManager* pHeapManager) {
	assert(i_ptr);
	pHeapManager->free(i_ptr);
}

void* operator new (size_t i_size, Engine::HeapManager* pHeapManager, uint8_t alignment) {
	size_t totalSize = i_size + sizeof(pHeapManager) + sizeof(HEAP_PATTERN);
	uint8_t* pointer = static_cast<uint8_t*>(pHeapManager->allocate(i_size));
	pointer = reinterpret_cast<uint8_t*>(pHeapManager);
	pointer += sizeof(pHeapManager);
	*pointer = HEAP_PATTERN;
	pointer += sizeof(HEAP_PATTERN);
	return pointer;
}

void operator delete (void* i_ptr, Engine::HeapManager* pHeapManager, uint8_t alignment) {
	assert(i_ptr);
	pHeapManager->free(i_ptr);
}