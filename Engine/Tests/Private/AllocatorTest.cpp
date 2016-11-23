#include "../AllocatorTest.h"
using namespace Engine;

bool startAllocatorTest() {
	int arraySize = 20;
	int defaultAlignment = 4;
	int alignment = 16;
	int heapSize = 1024;
	// Pure actor
	Actor* actor = new Actor("Test",Vector2D::ZERO);
	assert(actor);
	delete actor;	
	// Actor array
	Actor* actors = new Actor[arraySize];
	assert(actors);
	delete[] actors;	
	// Actor with alignment
	Actor* allignedActor = new (alignment)Actor("Test", Vector2D::ZERO);
	assert(allignedActor);
	delete allignedActor;
	// Actor array with alignment
	Actor* allignedActors = new (alignment)Actor[arraySize];
	assert(allignedActors);
	delete[] allignedActors;
	void* heapManagerPointer = _aligned_malloc(sizeof(Engine::HeapManager), defaultAlignment);	
	// Create heap manager
	Engine::HeapManager* testHeapManager = Engine::HeapManager::create(heapManagerPointer, heapSize, alignment);
	// Actor with heap manager
	Actor* heapActor = new (testHeapManager)Actor("Test", Vector2D::ZERO);
	assert(heapActor);
	delete heapActor;
	// Actor array with heap manager
	Actor* heapActors = new (testHeapManager)Actor[arraySize];
	assert(heapActors);
	delete[] heapActors;
	// Actor with heap manager and alignment
	Actor* heapAllignedActor = new (testHeapManager, alignment)Actor("Test", Vector2D::ZERO);
	assert(heapAllignedActor);
	delete heapAllignedActor;
	// Actor array with heap manager and alignment
	Actor* heapAllignedActors = new (testHeapManager, alignment)Actor[arraySize];
	assert(heapAllignedActors);
	delete[] heapAllignedActors;
	delete testHeapManager;
	return true;
}