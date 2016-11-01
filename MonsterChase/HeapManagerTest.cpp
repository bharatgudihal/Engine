#include <assert.h>
#include <algorithm>
#include <vector>
#include "Memory\HeapManager.h"
#define TEST_SINGLE_LARGE_ALLOCATION
#define __TRACK_ALLOCATIONS
using namespace Engine;

bool HeapManager_UnitTest()
{

	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;

	// Create a heap manager for my test heap.
	HeapManager pHeapManager(sizeHeap, numDescriptors);


#ifdef TEST_SINGLE_LARGE_ALLOCATION
	// This is a test I wrote to check to see if using the whole block if it was almost consumed by 
	// an allocation worked. Also helped test my ShowFreeBlocks() and ShowOutstandingAllocations().
	{
		pHeapManager.ShowFreeBlocks();

		size_t largestBeforeAlloc = pHeapManager.GetLargestFreeBlock();
		void * pPtr = pHeapManager.allocate(largestBeforeAlloc - HeapManager::s_MinumumToLeave);

		if (pPtr)
		{
			pHeapManager.ShowFreeBlocks();
			printf("\n");
#ifdef __TRACK_ALLOCATIONS
			pHeapManager.ShowOutstandingAllocations();
#endif // __TRACK_ALLOCATIONS
			printf("\n");

			size_t largestAfterAlloc = pHeapManager.GetLargestFreeBlock();
			pHeapManager.free(pPtr);

			pHeapManager.ShowFreeBlocks();
#ifdef __TRACK_ALLOCATIONS
			pHeapManager.ShowOutstandingAllocations();
#endif // __TRACK_ALLOCATIONS
			printf("\n");

			pHeapManager.runGarbageCollector();

			pHeapManager.ShowFreeBlocks();
#ifdef __TRACK_ALLOCATIONS
			pHeapManager.ShowOutstandingAllocations();
#endif // __TRACK_ALLOCATIONS
			printf("\n");

			size_t largestAfterCollect = pHeapManager.GetLargestFreeBlock();
		}
	}
#endif

	std::vector<void *> AllocatedAddresses;

	long	numAllocs = 0;
	long	numFrees = 0;
	long	numCollects = 0;

	bool	done = false;

	// allocate memory of random sizes up to 1024 bytes from the heap manager
	// until it runs out of memory
	do
	{
		const size_t		maxTestAllocationSize = 1024;

		//const unsigned int	alignments[] = { 4, 8, 16, 32, 64 };

		//unsigned int	index = rand() % (sizeof(alignments) / sizeof(alignments[0]));

		//unsigned int	alignment = alignments[index];
		unsigned int	alignment = 4;

		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));

		void * pPtr = pHeapManager.allocate(sizeAlloc);

		assert((reinterpret_cast<uintptr_t>(pPtr) & (alignment - 1)) == 0);

		if (pPtr == nullptr)
		{
			pHeapManager.runGarbageCollector();

			pPtr = pHeapManager.allocate(sizeAlloc);

			if (pPtr == NULL)
			{
				done = true;
				break;
			}
		}

		AllocatedAddresses.push_back(pPtr);
		numAllocs++;

		const unsigned int freeAboutEvery = 10;
		const unsigned int garbageCollectAboutEvery = 40;

		if (!AllocatedAddresses.empty() && ((rand() % freeAboutEvery) == 0))
		{
			void * pPtr = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			bool success = pHeapManager.free(pPtr);
			assert(success);

			numFrees++;
		}

		if ((rand() % garbageCollectAboutEvery) == 0)
		{
			pHeapManager.runGarbageCollector();

			numCollects++;
		}

	} while (1);

	printf("After exhausting allocations:\n");
	pHeapManager.ShowFreeBlocks();

#ifdef __TRACK_ALLOCATIONS
	pHeapManager.ShowOutstandingAllocations();
#endif // __TRACK_ALLOCATIONS
	printf("\n");

	// now free those blocks in a random order
	if (!AllocatedAddresses.empty())
	{
		// randomize the addresses
		std::random_shuffle(AllocatedAddresses.begin(), AllocatedAddresses.end());
		// return them back to the heap manager
		while (!AllocatedAddresses.empty())
		{
			void * pPtr = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			bool success = pHeapManager.Contains(pPtr);
			assert(success);

			success = pHeapManager.IsAllocated(pPtr);
			assert(success);

			success = pHeapManager.free(pPtr);
			assert(success);
		}

		printf("After freeing allocations:\n");

		pHeapManager.ShowFreeBlocks();
#ifdef __TRACK_ALLOCATIONS
		pHeapManager.ShowOutstandingAllocations();
#endif // __TRACK_ALLOCATIONS

		// do garbage collection
		pHeapManager.runGarbageCollector();		
		// our heap should be one single block, all the memory it started with

		printf("After garbage collection:\n");

		pHeapManager.ShowFreeBlocks();
#ifdef __TRACK_ALLOCATIONS
		pHeapManager.ShowOutstandingAllocations();
#endif // __TRACK_ALLOCATIONS

		printf("\n");		// do a large test allocation to see if garbage collection worked
		void * pPtr = pHeapManager.allocate(sizeHeap / 2);
		assert(pPtr);

		if (pPtr)
		{
			bool success = pHeapManager.free(pPtr);
			assert(success);

		}
	}
	// we succeeded	
	return true;
}
