#include "../Event.h"

namespace Engine {
	namespace Threading {
		ManualEvent::ManualEvent(bool initialState, const char* name) {
			handle = CreateEvent(NULL, TRUE, initialState, name);
			assert(handle != NULL);
		}

		ManualEvent::~ManualEvent() {
			BOOL result = CloseHandle(handle);
			assert(result == TRUE);
		}

		void ManualEvent::Reset() {
			BOOL result = ResetEvent(handle);
			assert(result == TRUE);
		}

		bool ManualEvent::Wait(DWORD timeInMilliseconds) {
			DWORD result = WaitForSingleObject(handle, timeInMilliseconds);
			assert((timeInMilliseconds == INFINITE && result == WAIT_OBJECT_0) || result == WAIT_TIMEOUT);
			return result == WAIT_OBJECT_0;
		}

		void ManualEvent::Trigger() {
			BOOL result = SetEvent(handle);
			assert(result == TRUE);
		}

		AutoEvent::AutoEvent(bool initialState, const char* name) {
			handle = CreateEvent(NULL, FALSE, initialState, name);
			assert(handle != NULL);
		}

		AutoEvent::~AutoEvent() {
			BOOL result = CloseHandle(handle);
			assert(result == TRUE);
		}

		bool AutoEvent::Wait(DWORD timeInMilliseconds) {
			DWORD result = WaitForSingleObject(handle, timeInMilliseconds);
			assert((timeInMilliseconds == INFINITE && result == WAIT_OBJECT_0) || result == WAIT_TIMEOUT);
			return result == WAIT_OBJECT_0;
		}

		void AutoEvent::Trigger() {
			BOOL result = SetEvent(handle);
			assert(result == TRUE);
		}
	}
}