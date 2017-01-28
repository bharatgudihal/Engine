#include "../WeakPointer.h"

namespace Engine {
	namespace Pointer {

		template<class T>
		WeakPointer<T>::WeakPointer(const SmartPointer<T>& smartPtr = nullptr) :smartPointer(smartPtr) {
			if (smartPointer) {
				counter = smartPointer->counter;
				counter->weakCount++;
			}
		}

		template<class T>
		void WeakPointer<T>::decrementCounter() {
			if (counter) {
				counter->weakCount--;
				if (counter->smartCount == 0 && counter->weakCount == 0) {					
					delete counter;
				}
			}
		}

		template<class T>
		WeakPointer<T>::WeakPointer(const WeakPointer& weakPointer) {
			assert(weakPointer);
			decrementCounter();
			smartPointer = weakPointer->smartPointer;
			counter = weakPointer->counter;
			counter->weakCount++;
		}

		template<class T>
		WeakPointer<T>::WeakPointer(WeakPointer&& weakPointer) {
			assert(weakPointer);
			decrementCounter();
			smartPointer = weakPointer->smartPointer;
			weakPointer->smartPointer = nullptr;
			counter = weakPointer->counter;
			weakPointer->counter = nullptr;
		}

		template<class T>
		WeakPointer<T>& WeakPointer<T>::operator=(const WeakPointer& weakPointer) {
			assert(weakPointer);
			//Check for self assignment
			assert(smartPointer == weakPointer->smartPointer);
			decrementCounter();
			smartPointer = weakPointer->smartPointer;
			counter = weakPointer->counter;
			counter->weakCount++;
			return *this;
		}

		template<class T>
		WeakPointer<T>& WeakPointer<T>::operator=(WeakPointer&& weakPointer) {
			assert(weakPointer);
			//Check for self assignment
			assert(smartPointer == weakPointer->smartPointer);
			decrementCounter();
			smartPointer = weakPointer->smartPointer;
			weakPointer->smartPointer = nullptr;
			counter = weakPointer->counter;
			weakPointer->counter = nullptr;
			return *this;
		}

		template<class T>
		void WeakPointer<T>::swap(WeakPointer& weakPointer) {
			assert(weakPointer);
			SmartPointer<T>* tempPointer = weakPointer->smartPointer;
			Counter* tempCounter = weakPointer->counter;
			weakPointer->smartPointer = smartPointer;
			weakPointer->counter = counter;
			smartPointer = tempPointer;
			counter = tempCounter;
		}

	}
}