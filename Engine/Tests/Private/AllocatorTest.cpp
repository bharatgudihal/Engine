#include "../AllocatorTest.h"
using namespace Engine;

bool startAllocatorTest() {
	// Pure actor
	Actor* actor = new Actor("Test",Vector2D::ZERO);
	assert(actor);
	delete actor;
	// Actor array
	Actor* actors = new Actor[20];
	assert(actors);
	delete[] actors;
	// Actor with alignment
	Actor* allignedActor = new (16)Actor("Test", Vector2D::ZERO);
	assert(allignedActor);
	delete allignedActor;
	// Actor array with alignment
	Actor* allignedActors = new (16)Actor[20];
	assert(allignedActors);
	delete[] allignedActors;
	// Create heap manager
	HeapManager* pHeapManager = HeapManager::create(1024, 16);
	// Actor with heap manager
	Actor* heapActor = new (pHeapManager)Actor("Test", Vector2D::ZERO);
	assert(heapActor);
	delete heapActor;
	// Actor array with heap manager
	Actor* heapActors = new (pHeapManager)Actor[20];
	assert(heapActors);
	delete[] heapActors;
	// Actor with heap manager and alignment
	Actor* heapAllignedActor = new (pHeapManager,16)Actor("Test", Vector2D::ZERO);
	assert(heapAllignedActor);
	delete heapAllignedActor;
	// Actor array with heap manager and alignment
	Actor* heapAllignedActors = new (pHeapManager,16)Actor[20];
	assert(heapAllignedActors);
	delete[] heapAllignedActors;
	delete pHeapManager;
	return true;
}