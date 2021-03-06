#include "../Mutex.h"
namespace Engine {
	namespace Threading {
		Mutex::Mutex(bool takeOwnerShip, const char* name) {
			handle = CreateMutex(NULL, takeOwnerShip, name);
			assert(handle != NULL);
		}

		Mutex::~Mutex() {
			BOOL result = CloseHandle(handle);
			assert(result == TRUE);
		}

		bool Mutex::TryToAcquire() {
			DWORD result = WaitForSingleObject(handle, 0);
			return result == WAIT_OBJECT_0;
		}

		bool Mutex::Acquire(DWORD timeInMilliseconds) {
			DWORD result = WaitForSingleObject(handle, timeInMilliseconds);
			assert((timeInMilliseconds == INFINITE && result == WAIT_OBJECT_0) || result == WAIT_TIMEOUT);
			return result == WAIT_OBJECT_0;
		}

		void Mutex::Acquire() {
			DWORD result = WaitForSingleObject(handle, INFINITE);
			assert(result == WAIT_OBJECT_0);
		}

		void Mutex::Release() {
			BOOL result = ReleaseMutex(handle);
			assert(result == TRUE);
		}
	}
}