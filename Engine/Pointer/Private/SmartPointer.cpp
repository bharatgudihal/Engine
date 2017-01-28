#include "../SmartPointer.h"

namespace Engine {
	namespace Pointer {

		template<class T>
		SmartPointer<T>::SmartPointer(T* ptr = nullptr):pointer(ptr){
			if (ptr) {
				counter = new Counter();
				counter->smartCount++;
			}
		}

		template<class T>
		SmartPointer<T>::SmartPointer(const SmartPointer& smartPtr) {
			assert(smartPtr);
			checkCountersAndDelete();
			pointer = smartPtr->pointer;
			counter = smartPtr->counter;
			counter->smartCount++;
		}

		template<class T>
		SmartPointer<T>::SmartPointer(SmartPointer&& smartPtr) {
			assert(smartPtr);
			checkCountersAndDelete();
			pointer = smartPtr->pointer;
			counter = smartPtr->counter;
		}

		template<class T>
		void SmartPointer<T>::checkCountersAndDelete() {
			if (counter) {
				if (counter->weakCount == 0 && counter->strongCount == 1) {
					counter->smartCount--;
					delete counter;
					delete pointer;
				}
				else if (counter->strongCount > 1) {
					counter->smartCount--;
				}
				else {
					delete pointer;
				}
			}
		}

		template<class T>
		SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& smartPtr) {
			assert(smartPtr);
			//Check for self assignment			
			assert(pointer == smartPtr->pointer);
			checkCountersAndDelete();
			counter = smartPtr->counter;
			counter->strongCount++;
			pointer = smartPtr->pointer;
			return *this;
		}

		template<class T>
		SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer&& smartPtr) {
			assert(smartPtr);
			//Check for self assignment
			assert(pointer == smartPtr->pointer);
			checkCountersAndDelete();
			pointer = smartPtr->pointer;
			smartPtr->pointer = nullptr;
			counter = smartPtr->counter;			
			smartPtr->counter = nullptr;
			return *this;
		}

		template<class T>
		void SmartPointer<T>::swap(SmartPointer& swapPointer) {
			assert(swapPointer);
			T* tempPointer = swapPointer->pointer;
			Counter* tempCounter = swapPointer->counter;
			swapPointer->pointer = pointer;
			swapPointer->counter = counter;
			pointer = tempPointer;
			counter = tempCounter;
		}
	}
}