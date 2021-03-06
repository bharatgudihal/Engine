#ifndef ALLOCATORS_H
#define ALLOCATORS_H
#include "MasterMemoryManager.h"

void* operator new (const size_t i_size);
void operator delete(void* i_ptr);

void* operator new[](size_t i_size);
void operator delete[](void* i_ptr);

void* operator new (size_t i_size, uint8_t alignment);
void operator delete (void* i_ptr, uint8_t alignment);

void* operator new[](size_t i_size, uint8_t alignment);
void operator delete[](void* i_ptr, uint8_t alignment);

void* operator new (size_t i_size, Engine::Memory::HeapManager* pHeapManager);
void operator delete (void* i_ptr, Engine::Memory::HeapManager* pHeapManager);

void* operator new[](size_t i_size, Engine::Memory::HeapManager* pHeapManager);
void operator delete[](void* i_ptr, Engine::Memory::HeapManager* pHeapManager);

void* operator new (size_t i_size, Engine::Memory::HeapManager* pHeapManager, uint8_t alignment);
void operator delete (void* i_ptr, Engine::Memory::HeapManager* pHeapManager, uint8_t alignment);

void* operator new[](size_t i_size, Engine::Memory::HeapManager* pHeapManager, uint8_t alignment);
void operator delete[](void* i_ptr, Engine::Memory::HeapManager* pHeapManager, uint8_t alignment);

static const uint8_t HEAP_PATTERN = 0xAA;
static const uint8_t DEFAULT_ALIGNMENT = 4;

#endif