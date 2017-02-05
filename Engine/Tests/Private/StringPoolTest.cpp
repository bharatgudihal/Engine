#include "../StringPoolTest.h"
#include <stdlib.h>
#include <ctime>

namespace Engine {
	namespace Test {
		bool TestStringPool() {
			const char characterSet[] = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			//StringPool test cases
			char* first = "Test";
			const char* pointer1 = String::StringPool::Instance()->Add(first);
			assert(pointer1);
			assert(String::StringPool::Instance()->Find(first) == pointer1);
			char* second = "Test";
			assert(pointer1 == String::StringPool::Instance()->Add(second));
			char* third = "Third";
			const char* pointer2 = String::StringPool::Instance()->Add(third);
			//Exhaust pool
			const char* testPointer;
			std::srand(static_cast<unsigned int>(std::time(0)));
			do {
				int size = 0;
				while (size == 0) {
					size = std::rand() % 20;
				}
				char* randomString = new char[size];
				for (int i = 0; i < size-1; i++) {
					randomString[i] = characterSet[std::rand() % (sizeof(characterSet) - 1)];
				}
				randomString[size - 1] = '\0';
				testPointer = String::StringPool::Instance()->Add(randomString);
				delete randomString;
			} while (testPointer);
			//PooledString test cases
			String::PooledString pooledString1("Test");
			assert(pooledString1);
			String::PooledString pooledString2("Test");
			assert(pooledString1 == pooledString2);
			assert(pooledString1.Get() == pooledString2.Get());;
			String::PooledString pooledString3(pooledString1);
			assert(pooledString1 == pooledString3);
			String::PooledString pooledString4("Third");
			pooledString4 = pooledString3;
			assert(pooledString4 == pooledString1);
			assert(pooledString4.Get() == pointer1);
			//HashedString test cases
			String::HashedString hash1("Test");
			assert(hash1);
			String::HashedString hash2(hash1);
			assert(hash2);
			assert(hash1 == hash2);
			String::HashedString hash3(pooledString1);
			assert(hash3);
			assert(hash1 == hash3);
			String::HashedString hash4 = hash3;
			assert(hash4);
			assert(hash1 == hash4);
			assert(hash1.Get() != 0);
			assert(hash1.Get() == hash4.Get());
			return true;
		}
	}
}