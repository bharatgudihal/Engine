#pragma once
#include "SmartPointer.h"
namespace Engine {
	namespace Pointer {
		template<class T>
		class WeakPointer {
		public:

			WeakPointer(SmartPointer<T>* smartPtr = nullptr) :smartPointer(smartPtr) {
				if (smartPointer) {
					counter = smartPointer->getCounter();
					counter->weakCount++;
				}
			}

			WeakPointer(const WeakPointer& weakPointer) {				
				decrementCounter();
				smartPointer = weakPointer.smartPointer;
				counter = weakPointer.counter;
				counter->weakCount++;
			}

			WeakPointer(WeakPointer&& weakPointer) {				
				decrementCounter();
				smartPointer = weakPointer.smartPointer;
				weakPointer.smartPointer = nullptr;
				counter = weakPointer.counter;
				weakPointer.counter = nullptr;
			}

			inline ~WeakPointer();

			WeakPointer& operator=(const WeakPointer& weakPointer) {
				//Check for self assignment
				assert(smartPointer != weakPointer.smartPointer);
				decrementCounter();
				smartPointer = weakPointer.smartPointer;
				counter = weakPointer.counter;
				counter->weakCount++;
				return *this;
			}

			WeakPointer& operator=(WeakPointer&& weakPointer) {
				//Check for self assignment
				assert(smartPointer != weakPointer.smartPointer);
				decrementCounter();
				smartPointer = weakPointer.smartPointer;
				weakPointer.smartPointer = nullptr;
				counter = weakPointer.counter;
				weakPointer.counter = nullptr;
				return *this;
			}

			inline bool operator==(const WeakPointer&) const;
			inline bool operator==(T*) const;
			inline bool operator!() const;

			void swap(WeakPointer& weakPointer) {
				SmartPointer<T>* tempPointer = weakPointer.smartPointer;
				Counter* tempCounter = weakPointer.counter;
				weakPointer.smartPointer = smartPointer;
				weakPointer.counter = counter;
				smartPointer = tempPointer;
				counter = tempCounter;
			}

			inline SmartPointer<T>* Acquire() const;
		private:
			SmartPointer<T>* smartPointer;
			Counter* counter = nullptr;

			void decrementCounter() {
				if (counter) {
					counter->weakCount--;
					if (counter->smartCount == 0 && counter->weakCount == 0) {
						delete counter;
					}
				}
			}
		};
	}
}
#include "WeakPointer_Inl.h"