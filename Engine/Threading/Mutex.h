#pragma once
#include <assert.h>
#include "WaitableObject.h"
namespace Engine {
	namespace Threading {
		class Mutex :public WaitableObject {
		public:
			Mutex(bool takeOwnerShip = false, const char* name = nullptr);
			~Mutex();
			bool TryToAcquire();
			void Acquire();
			bool Acquire(DWORD timeInMilliseconds);
			void Release();
		};
	}
}