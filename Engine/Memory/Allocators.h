#ifndef ALLOCATORS_H
#define ALLOCATORS_H
#include <stdint.h>
#include <assert.h>
#include "HeapManager.h"

void* operator new (const size_t i_size);
void operator delete(void* i_ptr);

void* operator new[](size_t i_size);
void operator delete[](void* i_ptr);

void* operator new (size_t i_size, uint8_t alignment);
void operator delete (void* i_ptr, uint8_t alignment);

void* operator new[](size_t i_size, uint8_t alignment);
void operator delete[](void* i_ptr, uint8_t alignment);

void* operator new (size_t i_size, Engine::HeapManager* pHeapManager);
void operator delete (void* i_ptr, Engine::HeapManager* pHeapManager);

void* operator new[](size_t i_size, Engine::HeapManager* pHeapManager);
void operator delete[](void* i_ptr, Engine::HeapManager* pHeapManager);

void* operator new (size_t i_size, Engine::HeapManager* pHeapManager, uint8_t alignment);
void operator delete (void* i_ptr, Engine::HeapManager* pHeapManager, uint8_t alignment);

void* operator new[](size_t i_size, Engine::HeapManager* pHeapManager, uint8_t alignment);
void operator delete[](void* i_ptr, Engine::HeapManager* pHeapManager, uint8_t alignment);

static const uint8_t HEAP_PATTERN = 0xAA;
static const uint8_t DEFAULT_ALIGNMENT = 4;

Engine::HeapManager* getDefaultHeapManager(Engine::HeapManager* i_heapManager);
//inline void setDefaultHeapManager(Engine::HeapManager* i_heapManager);

#include "Allocators_Inl.h"
#endif