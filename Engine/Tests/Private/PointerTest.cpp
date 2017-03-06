#include "../PointerTest.h"

namespace Engine {
	namespace Test {
		bool TestPointers() {
			Actor* testActor1 = new Actor("test1", Vector::ZERO);
			Pointer::SmartPointer<Actor> smartTest1(testActor1);
			assert(smartTest1);
			assert(smartTest1.getCounter()->smartCount == 1);
			assert(smartTest1.getCounter()->weakCount == 0);
			assert(smartTest1->getNameHash());
			assert((*smartTest1).getNameHash());
			assert(!(smartTest1 == nullptr));
			assert(smartTest1 != nullptr);
			assert(smartTest1 == testActor1);
			assert(!(!smartTest1));			
			Pointer::SmartPointer<Actor> smartTest2(smartTest1);
			assert(smartTest2);
			assert(smartTest2.getCounter()->smartCount == 2);
			assert(smartTest2.getCounter()->weakCount == 0);
			assert(smartTest2 == smartTest1);
			Pointer::SmartPointer<Actor> smartTest3;
			assert(!smartTest3);
			smartTest3 = smartTest2;			
			assert(smartTest3.getCounter()->smartCount == 3);
			assert(smartTest3.getCounter()->weakCount == 0);
			Pointer::SmartPointer<Actor> smartTest4(new Actor("test4", Vector::ZERO));
			assert(smartTest4);
			smartTest4.swap(smartTest3);
			assert(smartTest3.getCounter()->smartCount == 1);
			assert(smartTest3.getCounter()->weakCount == 0);
			assert(smartTest4.getCounter()->smartCount == 3);
			assert(smartTest4.getCounter()->weakCount == 0);
			if (true) {
				Engine::Pointer::WeakPointer<Actor> weakTest1(smartTest4);
				assert(weakTest1);
				assert(smartTest4.getCounter()->weakCount == 1);
				Engine::Pointer::WeakPointer<Actor> weakTest2(weakTest1);
				assert(weakTest2);
				assert(smartTest4.getCounter()->weakCount == 2);
				Engine::Pointer::WeakPointer<Actor> weakTest3;
				assert(!weakTest3);
				weakTest3 = weakTest2;
				assert(weakTest3);
				assert(smartTest4.getCounter()->weakCount == 3);
				assert(weakTest2 == weakTest3);
				assert(weakTest2 == smartTest4);
				Engine::Pointer::WeakPointer<Actor> weakTest4;
				assert(!weakTest4);
				weakTest4.swap(weakTest3);
				assert(weakTest4);
				assert(!weakTest3);
			}
			assert(smartTest4.getCounter()->weakCount == 0);
			Actor* testActor2 = new Actor("test", Vector::ZERO);
			Engine::Pointer::UniquePointer<Actor> uniqueTest1(testActor2);
			assert(uniqueTest1);
			Engine::Pointer::UniquePointer<Actor> uniqueTest2;
			assert(!uniqueTest2);
			uniqueTest2 = uniqueTest1;
			assert(!uniqueTest1);
			assert(uniqueTest2);
			Engine::Pointer::UniquePointer<Actor> uniqueTest3(uniqueTest2);
			assert(!uniqueTest2);
			assert(uniqueTest3);
			assert(uniqueTest3->getNameHash());
			assert((*uniqueTest3).getNameHash());
			assert(uniqueTest3 == testActor2);
			return true;
		}
	}
}