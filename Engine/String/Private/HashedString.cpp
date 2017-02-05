#include "../HashedString.h"
namespace Engine {
	namespace String {

		unsigned int HashedString::Hash(const void* value, unsigned int length) {
			const uint8_t * p = static_cast<const uint8_t *>(value);
			unsigned int hash = 2166136261;
			for (unsigned int i = 0; i < length; ++i) {
				hash = 16777619 * (hash ^ p[i]);
			}
			return hash ^ (hash >> 16);
		}		
	}
}