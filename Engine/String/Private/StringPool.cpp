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
				if (currentPosition + sizeOfString + sizeof(size_t) < startOfBlock + poolSize) {
					size_t* tempSizeT = reinterpret_cast<size_t*>(currentPosition);
					*tempSizeT = sizeOfString;
					currentPosition += sizeof(size_t);
					memcpy(currentPosition, inputString, sizeOfString);
					currentPosition += sizeOfString;
				}
			}
			return returnPointer;
		}

		void* StringPool::Find(const char* inputString) {
			assert(inputString);
			void* result;
			size_t sizeOfString = getStringLength(inputString);
			char* walker = startOfBlock;
			while (walker < startOfBlock + poolSize) {
				if (sizeOfString == *walker) {
					size_t tempSize = *walker;
					sizeOfString += tempSize;

				}
			}
			return result;
		}

		size_t StringPool::getStringLength(const char* inputString) {
			size_t length = 0;
			while (*(inputString + length) != '\0') {
				length++;
			}
			return length;
		}

		bool StringPool::AreEqual(const char* rhs, const char* lhs) {
			size_t count = 0;
		}
	}
}