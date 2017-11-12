#pragma once
#include "PooledString.h"
namespace Engine {
	namespace String {
		class HashedString {
		public:
			inline HashedString(const char*);
			inline HashedString(const HashedString&);
			inline HashedString(const PooledString&);
			inline HashedString& operator=(const HashedString&);
			inline bool operator==(const HashedString&) const;
			inline operator bool() const;
			inline const unsigned int Get() const;
		private:
			inline static unsigned int Hash(const char*);
			static unsigned int Hash(const void*, unsigned int);
			unsigned int hash;
		};
	}
}
#include "HashedString_Inl.h"