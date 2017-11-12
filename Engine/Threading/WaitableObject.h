#pragma once
#include <Windows.h>
namespace Engine {
	namespace Threading {
		class WaitableObject {
		public:
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