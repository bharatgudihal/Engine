#include "../IsNANTest.h"

bool Engine::TestNAN() {
	DEBUG_LOG("Float Test Started\n");
	float test1 = 0.00000000000000001f;
	assert(!Engine::IsNAN(test1));
	float test2 = nanf("1");
	assert(Engine::IsNAN(test2));
	float test3 = 0.001f;
	float test4 = 1 / 1000;
	assert(!Engine::AreAboutEqual(test3, test4));
	float test5 = 0.000001f;
	float test6 = 1 / 100000;
	assert(Engine::AreAboutEqual(test5, test6));
	DEBUG_LOG("Float Test Ended\n");
	return true;
}