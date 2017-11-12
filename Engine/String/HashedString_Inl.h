#pragma once
namespace Engine {
	namespace String {
		inline unsigned int HashedString::Hash(const char* stringValue) {
			assert(stringValue);
			return Hash(reinterpret_cast<void*>(const_cast<char*>(stringValue)), static_cast<unsigned int>(strlen(StringPool::Instance()->Add(stringValue))));
		}

		inline HashedString::HashedString(const char* stringValue) : hash(Hash(stringValue)) {			
		}

		inline HashedString::HashedString(const HashedString& otherHashedString) : hash(otherHashedString.hash) {
		}

		inline HashedString::HashedString(const PooledString& pooledString) : hash(Hash(pooledString.Get())) {
		}

		inline HashedString& HashedString::operator=(const HashedString& otherHashedString) {
			hash = otherHashedString.hash;
			return *this;
		}

		inline bool HashedString::operator==(const HashedString& otherHashedString) const{
			return hash == otherHashedString.hash;
		}

		inline HashedString::operator bool() const {
			return hash != 0;
		}

		inline const unsigned int HashedString::Get() const {
			return hash;
		}
	}
}