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
	void* heapManagerPointer = _aligned_malloc(sizeof(Engine::HeapManager), 4);
	// Create heap manager
	Engine::HeapManager* testHeapManager = Engine::HeapManager::create(heapManagerPointer, 1024, 16);
	// Actor with heap manager
	Actor* heapActor = new (testHeapManager)Actor("Test", Vector2D::ZERO);
	assert(heapActor);
	delete heapActor;
	// Actor array with heap manager
	Actor* heapActors = new (testHeapManager)Actor[20];
	assert(heapActors);
	delete[] heapActors;
	// Actor with heap manager and alignment
	Actor* heapAllignedActor = new (testHeapManager,16)Actor("Test", Vector2D::ZERO);
	assert(heapAllignedActor);
	delete heapAllignedActor;
	// Actor array with heap manager and alignment
	Actor* heapAllignedActors = new (testHeapManager,16)Actor[20];
	assert(heapAllignedActors);
	delete[] heapAllignedActors;
	delete testHeapManager;
	return true;
}