#pragma once
#include "StringPool.h"

namespace Engine {
	namespace String {
		class PooledString {
		public:			
			inline explicit PooledString(const char*);
			inline PooledString(const PooledString&);
			inline PooledString& operator=(const PooledString&);
			inline bool operator==(const PooledString&) const;
			inline operator bool() const;
			inline const char* Get() const;
		private:
			const char* stringValue;
		};
	}
}
#include "PooledString_Inl.h"