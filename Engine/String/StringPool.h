#pragma once
#include <string>
#include "../Memory/MasterMemoryManager.h"
namespace Engine {
	namespace String {
		class StringPool {
		public:
			static StringPool* Create(size_t size);
			~StringPool();
			void* Add(const char*);
			void* Find(const char*);
		private:
			StringPool(size_t size);
			size_t poolSize;
			char* startOfBlock;
			char* currentPosition;
			size_t getStringLength(const char*);
			bool AreEqual(const char*, const char*);
		};
	}
}