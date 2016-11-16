#include "../AllocatorTest.h"
using namespace Engine;

bool startAllocatorTest() {
	Actor* actor = new Actor("Test",Vector2D::ZERO);
	assert(actor);
	delete actor;
	Actor* actors = new Actor[20];
	assert(actors);
	delete[] actors;
	Actor* allignedActor = new (16)Actor("Test", Vector2D::ZERO);
	assert(allignedActor);
	delete allignedActor;
	Actor* allignedActors = new (16)Actor[20];
	assert(allignedActors);
	delete[] allignedActors;
	HeapManager* pHeapManager = HeapManager::create(256, 8);
	Actor* heapActor = new (pHeapManager)Actor("Test", Vector2D::ZERO);
	assert(heapActor);
	delete heapActor;
	Actor* heapActors = new (pHeapManager)Actor[20];
	assert(heapActors);
	delete[] heapActors;
	Actor* heapAllignedActor = new (pHeapManager,16)Actor("Test", Vector2D::ZERO);
	assert(heapAllignedActor);
	delete heapAllignedActor;
	Actor* heapAllignedActors = new (pHeapManager,16)Actor[20];
	assert(heapAllignedActors);
	delete[] heapAllignedActors;
	pHeapManager->destroy();
	delete pHeapManager;
	return true;
}