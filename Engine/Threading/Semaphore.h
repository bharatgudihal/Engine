#pragma once
#include <assert.h>
#include "WaitableObject.h"
namespace Engine {
	namespace Threading {
		class Semaphore :public WaitableObject {
		public:
			Semaphore(unsigned int initValue, unsigned int maxValue, const char* name = nullptr);
			~Semaphore();
			void Increment(unsigned int count = 1);
			void Decrement();
			bool Decrement(DWORD timeInMilliseconds);
		};
	}
}