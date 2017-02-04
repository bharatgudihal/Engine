#pragma once
#include "../Memory/MasterMemoryManager.h"
namespace Engine {
	namespace String {
		class StringPool {
		public:
			inline static bool Startup(const size_t);
			inline static StringPool* Instance();
			inline static void ShutDown();
			const char* Add(const char*);
			const char* Find(const char*) const;
		private:
			StringPool(size_t size);
			inline ~StringPool();
			static StringPool* instance;
			size_t poolSize;
			char* startOfBlock;
			char* currentPosition;
			uint8_t getStringLength(const char*) const;
			bool AreEqual(const char*, const char*, uint8_t) const;
			const uint8_t DEFAULTFILL = 0xAA;
			void FillPool();
		};
	}
}
#include "StringPool_Inl.h"