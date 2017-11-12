#include "../PooledString.h"
namespace Engine {
	namespace String {
		PooledString::PooledString(const char* i_string) :stringValue(StringPool::Instance()->Add(i_string)) {
		}

		PooledString::PooledString(const PooledString& pooledString) : stringValue(pooledString.stringValue){
		}

		PooledString& PooledString::operator=(const PooledString& pooledString) {
			stringValue = pooledString.stringValue;
			return *this;
		}

		bool PooledString::operator==(const PooledString& pooledString) const {
			return stringValue == pooledString.stringValue;
		}
	}
}