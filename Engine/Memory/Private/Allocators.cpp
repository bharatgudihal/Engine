#include "../Allocators.h"

Engine::HeapManager* getDefaultHeapManager(Engine::HeapManager* i_heapManager) {
	static Engine::HeapManager* m_heapManager = nullptr;
	if (!m_heapManager) {
		m_heapManager = i_heapManager;
	}
	return m_heapManager;
}

void* operator new (const size_t i_size) {
	DEBUG_LOG("Allocating pointer for size %d\n", i_size);
	Engine::HeapManager* m_heapManager = getDefaultHeapManager(nullptr);
	size_t totalSize = i_size + sizeof(m_heapManager) + sizeof(HEAP_PATTERN);
	uint8_t* pointer = static_cast<uint8_t*>(m_heapManager->allocate(totalSize,DEFAULT_ALIGNMENT));
	if (!pointer) {
		m_heapManager->runGarbageCollector();
		pointer = static_cast<uint8_t*>(m_heapManager->allocate(totalSize));
		assert(pointer);
	}
	Engine::HeapManager** temp = reinterpret_cast<Engine::HeapManager**>(pointer);
	*temp = m_heapManager;
	pointer += sizeof(m_heapManager);
	*pointer = HEAP_PATTERN;
	pointer += sizeof(HEAP_PATTERN);
	return pointer;
}

void operator delete (void* i_ptr) {
	assert(i_ptr);
	DEBUG_LOG("Freeing pointer %p\n", i_ptr);
	uint8_t* pointer = static_cast<uint8_t*>(i_ptr);
	pointer -= sizeof(HEAP_PATTERN);
	if (*pointer == HEAP_PATTERN) {
		pointer -= sizeof(Engine::HeapManager*);
		Engine::HeapManager** pHeapManager = reinterpret_cast<Engine::HeapManager**>(pointer);
		(*pHeapManager)->free(pointer);
	}
	else {
		_aligned_free(i_ptr);
	}	
}

void* operator new[](size_t i_size) {
	DEBUG_LOG("Allocating array pointer for size %d\n", i_size);
	Engine::HeapManager* m_heapManager = getDefaultHeapManager(nullptr);
	size_t totalSize = i_size + sizeof(m_heapManager) + sizeof(HEAP_PATTERN);
	uint8_t* pointer = static_cast<uint8_t*>(m_heapManager->allocate(totalSize, DEFAULT_ALIGNMENT));
	if (!pointer) {
		m_heapManager->runGarbageCollector();
		pointer = static_cast<uint8_t*>(m_heapManager->allocate(totalSize));
		assert(pointer);
	}
	Engine::HeapManager** temp = reinterpret_cast<Engine::HeapManager**>(pointer);
	*temp = m_heapManager;
	pointer += sizeof(m_heapManager);
	*pointer = HEAP_PATTERN;
	pointer += sizeof(HEAP_PATTERN);
	return pointer;
}

void operator delete[](void* i_ptr) {
	assert(i_ptr);
	DEBUG_LOG("Freeing array pointer %p\n", i_ptr);
	uint8_t* pointer = static_cast<uint8_t*>(i_ptr);
	pointer -= sizeof(HEAP_PATTERN);
	if (*pointer == HEAP_PATTERN) {
		pointer -= sizeof(Engine::HeapManager*);
		Engine::HeapManager** pHeapManager = reinterpret_cast<Engine::HeapManager**>(pointer);
		(*pHeapManager)->free(pointer);
	}
	else {
		_aligned_free(i_ptr);
	}
}

void* operator new (size_t i_size, uint8_t alignment) {
	DEBUG_LOG("Allocating pointer for size %d and alignment %d\n", i_size, alignment);
	Engine::HeapManager* m_heapManager = getDefaultHeapManager(nullptr);
	size_t totalSize = i_size + sizeof(m_heapManager) + sizeof(HEAP_PATTERN);
	uint8_t* pointer = static_cast<uint8_t*>(m_heapManager->allocate(totalSize, alignment));
	if (!pointer) {
		m_heapManager->runGarbageCollector();
		pointer = static_cast<uint8_t*>(m_heapManager->allocate(totalSize));
		assert(pointer);
	}
	Engine::HeapManager** temp = reinterpret_cast<Engine::HeapManager**>(pointer);
	*temp = m_heapManager;
	pointer += sizeof(m_heapManager);
	*pointer = HEAP_PATTERN;
	pointer += sizeof(HEAP_PATTERN);
	return pointer;
}

void operator delete (void* i_ptr, uint8_t alignment) {
	assert(i_ptr);
	DEBUG_LOG("Freeing pointer %p with alignment %d. Should never execute!\n", i_ptr, alignment);
	_aligned_free(i_ptr);
}

void* operator new[](size_t i_size, uint8_t alignment) {
	DEBUG_LOG("Allocating array pointer for size %d and alignment %d\n", i_size, alignment);
	Engine::HeapManager* m_heapManager = getDefaultHeapManager(nullptr);
	size_t totalSize = i_size + sizeof(m_heapManager) + sizeof(HEAP_PATTERN);
	uint8_t* pointer = static_cast<uint8_t*>(m_heapManager->allocate(totalSize, alignment));
	if (!pointer) {
		m_heapManager->runGarbageCollector();
		pointer = static_cast<uint8_t*>(m_heapManager->allocate(totalSize));
		assert(pointer);
	}
	Engine::HeapManager** temp = reinterpret_cast<Engine::HeapManager**>(pointer);
	*temp = m_heapManager;
	pointer += sizeof(m_heapManager);
	*pointer = HEAP_PATTERN;
	pointer += sizeof(HEAP_PATTERN);
	return pointer;
}

void operator delete[](void* i_ptr, uint8_t alignment) {
	assert(i_ptr);
	DEBUG_LOG("Freeing array pointer %p and alignment %d. Should never execute!\n", i_ptr,alignment);
	_aligned_free(i_ptr);
}


void* operator new (size_t i_size, Engine::HeapManager* pHeapManager) {
	DEBUG_LOG("Allocating pointer for size %d and heap manager %p\n", i_size, pHeapManager);
	size_t totalSize = i_size + sizeof(pHeapManager) + sizeof(HEAP_PATTERN);
	uint8_t* pointer = static_cast<uint8_t*>(pHeapManager->allocate(totalSize));
	if (!pointer) {
		pHeapManager->runGarbageCollector();
		pointer = static_cast<uint8_t*>(pHeapManager->allocate(totalSize));
		assert(pointer);
	}
	Engine::HeapManager** temp = reinterpret_cast<Engine::HeapManager**>(pointer);
	*temp = pHeapManager;
	pointer += sizeof(pHeapManager);
	*pointer = HEAP_PATTERN;
	pointer += sizeof(HEAP_PATTERN);
	return pointer;
}

void operator delete (void* i_ptr, Engine::HeapManager* pHeapManager) {
	DEBUG_LOG("Freeing pointer for pointer %p and heap manager %p. Should never execute!\n", i_ptr, pHeapManager);
	assert(i_ptr);
	pHeapManager->free(i_ptr);
}

void* operator new[](size_t i_size, Engine::HeapManager* pHeapManager) {
	DEBUG_LOG("Allocating array pointer for size %d and heap manager %p\n", i_size, pHeapManager);
	size_t totalSize = i_size + sizeof(pHeapManager) + sizeof(HEAP_PATTERN);
	uint8_t* pointer = static_cast<uint8_t*>(pHeapManager->allocate(totalSize));
	if (!pointer) {
		pHeapManager->runGarbageCollector();
		pointer = static_cast<uint8_t*>(pHeapManager->allocate(totalSize));
		assert(pointer);
	}
	Engine::HeapManager** temp = reinterpret_cast<Engine::HeapManager**>(pointer);
	*temp = pHeapManager;
	pointer += sizeof(pHeapManager);
	*pointer = HEAP_PATTERN;
	pointer += sizeof(HEAP_PATTERN);
	return pointer;
}

void operator delete[](void* i_ptr, Engine::HeapManager* pHeapManager) {
	DEBUG_LOG("Freeing pointer for pointer %p and heap manager %p. Should never execute!\n", i_ptr, pHeapManager);
	assert(i_ptr);
	pHeapManager->free(i_ptr);
}

void* operator new (size_t i_size, Engine::HeapManager* pHeapManager, uint8_t alignment) {
	DEBUG_LOG("Allocating pointer for size %d, heap manager %p and alignment %d\n", i_size, pHeapManager, alignment);
	size_t totalSize = i_size + sizeof(pHeapManager) + sizeof(HEAP_PATTERN);
	uint8_t* pointer = static_cast<uint8_t*>(pHeapManager->allocate(totalSize, alignment));
	if (!pointer) {
		pHeapManager->runGarbageCollector();
		pointer = static_cast<uint8_t*>(pHeapManager->allocate(totalSize, alignment));
		assert(pointer);
	}
	Engine::HeapManager** temp = reinterpret_cast<Engine::HeapManager**>(pointer);
	*temp = pHeapManager;
	pointer += sizeof(pHeapManager);
	*pointer = HEAP_PATTERN;
	pointer += sizeof(HEAP_PATTERN);
	return pointer;
}

void operator delete (void* i_ptr, Engine::HeapManager* pHeapManager, uint8_t alignment) {
	DEBUG_LOG("Freeing pointer for pointer %p, heap manager %p and alignment %d. Should never execute!\n", i_ptr, pHeapManager,alignment);
	assert(i_ptr);
	pHeapManager->free(i_ptr);
}

void* operator new[](size_t i_size, Engine::HeapManager* pHeapManager, uint8_t alignment) {
	DEBUG_LOG("Allocating array pointer for size %d, heap manager %p and alignment %d\n", i_size, pHeapManager, alignment);
	size_t totalSize = i_size + sizeof(pHeapManager) + sizeof(HEAP_PATTERN);
	uint8_t* pointer = static_cast<uint8_t*>(pHeapManager->allocate(totalSize, alignment));
	if (!pointer) {
		pHeapManager->runGarbageCollector();
		pointer = static_cast<uint8_t*>(pHeapManager->allocate(totalSize, alignment));
		assert(pointer);
	}
	Engine::HeapManager** temp = reinterpret_cast<Engine::HeapManager**>(pointer);
	*temp = pHeapManager;
	pointer += sizeof(pHeapManager);
	*pointer = HEAP_PATTERN;
	pointer += sizeof(HEAP_PATTERN);
	return pointer;
}
void operator delete[](void* i_ptr, Engine::HeapManager* pHeapManager, uint8_t alignment) {
	DEBUG_LOG("Freeing array pointer for pointer %p, heap manager %p and alignment %d. Should never execute!\n", i_ptr, pHeapManager, alignment);
	assert(i_ptr);
	pHeapManager->free(i_ptr);
}