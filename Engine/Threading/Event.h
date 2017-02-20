#pragma once
#include <assert.h>
#include "WaitableObject.h"

namespace Engine {
	namespace Threading {
		class ManualEvent :public WaitableObject {
		public:
			ManualEvent(bool initialState, const char* name = nullptr);
			~ManualEvent();
			void Reset();
			bool Wait(DWORD timeInMilliseconds);
			void Trigger();
		};

		class AutoEvent :public WaitableObject {
		public:
			AutoEvent(bool initialState, const char* name = nullptr);
			~AutoEvent();
			bool Wait(DWORD timeInMilliseconds);
			void Trigger();
		};
	}
}