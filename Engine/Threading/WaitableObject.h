#pragma once
#include <Windows.h>
namespace Engine {
	namespace Threading {
		class WaitableObject {
		public:
			static const DWORD InfiniteWait = INFINITE;
			WaitableObject() :handle(INVALID_HANDLE_VALUE) {}
			virtual ~WaitableObject() {};
			HANDLE GetHandle() { return handle; }
		protected:
			HANDLE handle;
		private:
			WaitableObject(WaitableObject&);
			WaitableObject& operator=(WaitableObject&);
		};
	}
}