#pragma once
#include "../Memory/MasterMemoryManager.h"
namespace Engine {
	namespace String {
		class StringPool {
		public:
			inline static StringPool* Create(const size_t);
			inline ~StringPool();
			void* Add(const char*);
			void* Find(const char*) const;
		private:
			StringPool(size_t size);
			size_t poolSize;
			char* startOfBlock;
			char* currentPosition;
			size_t getStringLength(const char*) const;
			bool AreEqual(const char*, const char*, size_t) const;
		};
	}
}
#include "StringPool_Inl.h"