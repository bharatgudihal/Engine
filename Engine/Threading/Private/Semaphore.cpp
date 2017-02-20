#include "../Semaphore.h"

namespace Engine {
	namespace Threading {
		Semaphore::Semaphore(unsigned int initValue, unsigned int maxValue, const char* name) {
			assert(initValue <= maxValue);
			handle = CreateSemaphore(NULL, initValue, maxValue, name);
			assert(handle != NULL);
		}

		Semaphore::~Semaphore() {
			CloseHandle(handle);
		}

		void Semaphore::Increment(unsigned int count) {
			BOOL result = ReleaseSemaphore(handle, count, NULL);
			assert(result == TRUE);
		}

		void Semaphore::Decrement() {
			DWORD result = WaitForSingleObject(handle, INFINITE);
			assert(result == WAIT_OBJECT_0);
		}

		bool Semaphore::Decrement(DWORD timeInMilliseconds) {
			DWORD result = WaitForSingleObject(handle, timeInMilliseconds);
			assert((timeInMilliseconds == INFINITE && result == WAIT_OBJECT_0) || result == WAIT_TIMEOUT);
			return result == WAIT_OBJECT_0;
		}
	}
}