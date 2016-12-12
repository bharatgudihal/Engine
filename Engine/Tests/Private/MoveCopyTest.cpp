#include "../MoveCopyTest.h"
using namespace Engine;

bool MoveCopyTest() {
	// Testing normal constructor
	Actor test1("Test1", Vector2D::ZERO);
	// Testing copy constructor
	Actor test2 = test1;
	// Testing copy assignment operator
	Actor test3("Test2", Vector2D::ZERO);
	test3 = test2;
	// Testing move copy constructor
	Actor test4 = std::move(test1);
	return true;
}