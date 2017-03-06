#include "../MoveCopyTest.h"

namespace Engine {
	namespace Test {
		bool MoveCopyTest() {
			// Testing normal constructor
			Actor test1("Test1", Vector::ZERO);
			// Testing copy constructor
			Actor test2 = test1;
			// Testing copy assignment operator
			Actor test3("Test2", Vector::ZERO);
			test3 = test2;
			// Testing move copy constructor
			Actor test4 = std::move(test1);
			return true;
		}
	}
}