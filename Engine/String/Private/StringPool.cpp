#include "../StringPool.h"
namespace Engine {
	namespace String {
		StringPool::StringPool(size_t size) {
			startOfBlock = static_cast<char*>(MasterMemoryManager::Instance()->DefaultHeapManager()->allocate(size));
			poolSize = size;
			currentPosition = startOfBlock;
		}

		void* StringPool::Add(const char* inputString) {
			assert(inputString);
			void* returnPointer = Find(inputString);
			if(returnPointer == nullptr){
				size_t sizeOfString = getStringLength(inputString);
				assert(sizeOfString > 0 && currentPosition + sizeOfString + sizeof(size_t) < startOfBlock + poolSize);
				size_t* tempSizeT = reinterpret_cast<size_t*>(currentPosition);
				*tempSizeT = sizeOfString;
				currentPosition += sizeof(size_t);
				memcpy(currentPosition, inputString, sizeOfString);
				returnPointer = currentPosition;
				currentPosition += sizeOfString;
			}
			return returnPointer;
		}

		void* StringPool::Find(const char* inputString) const{
			if (currentPosition != startOfBlock) {
				assert(inputString);
				size_t sizeOfString = getStringLength(inputString);
				assert(sizeOfString > 0);
				char* walker = startOfBlock;
				while (walker < startOfBlock + poolSize) {
					if (sizeOfString == *walker) {
						walker += sizeof(size_t);
						if (AreEqual(walker, inputString, sizeOfString)) {
							return walker;
						}
						else {
							walker += sizeOfString;
						}
					}
					else {
						walker += sizeof(size_t) + *walker;
					}
				}
			}
			return nullptr;
		}

		size_t StringPool::getStringLength(const char* inputString) const{
			size_t length = 0;
			while (*(inputString + length) != '\0') {
				length++;
			}
			return length;
		}

		bool StringPool::AreEqual(const char* rhs, const char* lhs, size_t size) const{
			for (size_t index = 0; index < size; index++) {
				if (rhs[index] != lhs[index]) {
					return false;
				}
			}
			return true;
		}
	}
}