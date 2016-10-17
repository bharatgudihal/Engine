#include "HeapManagerTest.h"
#include "Memory\HeapManager.h"
using namespace Engine;

void StartTest() {
	HeapManager heapManager(1024,16);
	char* test1 = (char*)heapManager.allocate(100);
	char* test2 = (char*)heapManager.allocate(50);
	char* test3 = (char*)heapManager.allocate(200);
	char* test4 = (char*)heapManager.allocate(300);
	heapManager.free(test1);
	heapManager.free(test2);
	heapManager.free(test4);
	test4 = (char*)heapManager.allocate(400);
	heapManager.free(test3);
	heapManager.free(test4);
}