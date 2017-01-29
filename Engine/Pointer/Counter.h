#pragma once
#include <assert.h>
namespace Engine {
	namespace Pointer {
		class Counter {
		public:
			long smartCount;
			long weakCount;
			~Counter() { assert(smartCount == 0); assert(weakCount == 0); };
		};
	}
}