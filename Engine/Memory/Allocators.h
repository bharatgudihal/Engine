#pragma once
#include <stdint.h>
#include "HeapManager.h"
#include "../Logger/Logger.h"

static const uint8_t HEAP_PATTERN = 0xAA;

void* operator new (size_t i_size);
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