#pragma once
namespace Engine {
	namespace String {
		inline PooledString::PooledString(const char* i_string) :stringValue(StringPool::Instance()->Add(i_string)) {
		}

		inline PooledString::PooledString(const PooledString& pooledString) : stringValue(pooledString.stringValue) {
		}

		inline PooledString& PooledString::operator=(const PooledString& pooledString) {
			stringValue = pooledString.stringValue;
			return *this;
		}

		inline bool PooledString::operator==(const PooledString& pooledString) const {
			return stringValue == pooledString.stringValue;
		}

		inline PooledString::operator bool() const {
			return stringValue != nullptr;
		}

		inline const char* PooledString::Get() const {
			return stringValue;
		}
	}
}