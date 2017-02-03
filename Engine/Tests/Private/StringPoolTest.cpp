#include "../StringPoolTest.h"
namespace Engine {
	namespace Test {
		bool TestStringPool() {
			String::StringPool* stringPool = String::StringPool::Create(1024);
			char* first = "Test";
			void* pointer = stringPool->Add(first);
			assert(pointer);
			assert(stringPool->Find(first) == pointer);
			char* second = "Test";
			assert(pointer == stringPool->Add(second));
			return true;
		}
	}
}