#include "../StringPool.h"
namespace Engine {
	namespace String {

		StringPool* StringPool::instance = nullptr;

		StringPool::StringPool(size_t size) {
			startOfBlock = static_cast<char*>(Memory::MasterMemoryManager::Instance()->DefaultHeapManager()->allocate(size));
			poolSize = size;
			currentPosition = startOfBlock;
			FillPool();
		}

		void StringPool::FillPool() {
			for (size_t index = 0; index < poolSize; index++) {
				startOfBlock[index] = DEFAULTFILL;
			}
		}

		const char* StringPool::Add(const char* inputString) {
			assert(inputString);
			const char* returnPointer = Find(inputString);
			if(returnPointer == nullptr){
				uint8_t sizeOfString = getStringLength(inputString);
				if (sizeOfString > 0 && currentPosition + sizeOfString + sizeof(uint8_t) < startOfBlock + poolSize) {
					uint8_t* tempSizeT = reinterpret_cast<uint8_t*>(currentPosition);
					*tempSizeT = sizeOfString;
					currentPosition += sizeof(uint8_t);
					memcpy(currentPosition, inputString, sizeOfString);
					returnPointer = currentPosition;
					currentPosition += sizeOfString;
				}
			}
			return returnPointer;
		}

		const char* StringPool::Find(const char* inputString) const{
			if (currentPosition != startOfBlock) {
				assert(inputString);
				uint8_t sizeOfString = getStringLength(inputString);
				assert(sizeOfString > 0);
				char* walker = startOfBlock;
				while (walker < startOfBlock + poolSize) {
					if (*walker == static_cast<char>(DEFAULTFILL)) {
						break;
					}
					if (sizeOfString == *walker) {
						walker += sizeof(uint8_t);
						if (AreEqual(walker, inputString, sizeOfString)) {
							return walker;
						}
						else {
							walker += sizeOfString;
						}
					}
					else {
						walker += sizeof(uint8_t) + *walker;
					}
				}
			}
			return nullptr;
		}

		uint8_t StringPool::getStringLength(const char* inputString) const{
			uint8_t length = 0;
			while (*(inputString + length) != '\0') {
				length++;
			}
			return length + 1;
		}

		bool StringPool::AreEqual(const char* rhs, const char* lhs, uint8_t size) const{
			for (uint8_t index = 0; index < size; index++) {
				if (rhs[index] != lhs[index]) {
					return false;
				}
			}
			return true;
		}
	}
}