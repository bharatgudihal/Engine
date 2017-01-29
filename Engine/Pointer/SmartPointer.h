#pragma once
#include <assert.h>
#include "Counter.h"

namespace Engine {
	namespace Pointer {		
		template<class T>
		class SmartPointer {
		public:
			SmartPointer(T* ptr = nullptr):pointer(ptr) {				
				if (ptr) {
					counter = new Counter();
					counter->smartCount++;
				}
			}

			SmartPointer(const SmartPointer& smartPtr) {
				checkCountersAndDelete();
				pointer = smartPtr.pointer;
				counter = smartPtr.counter;
				counter->smartCount++;
			}

			SmartPointer(SmartPointer&& smartPtr) {				
				checkCountersAndDelete();
				pointer = smartPtr.pointer;
				counter = smartPtr.counter;
			}

			inline ~SmartPointer();

			SmartPointer& operator=(const SmartPointer& smartPtr) {
				//Check for self assignment			
				assert(pointer != smartPtr.pointer);
				checkCountersAndDelete();
				counter = smartPtr.counter;
				counter->smartCount++;
				pointer = smartPtr.pointer;
				return *this;
			}

			SmartPointer& operator=(SmartPointer&& smartPtr) {
				//Check for self assignment
				assert(pointer != smartPtr.pointer);
				checkCountersAndDelete();
				pointer = smartPtr.pointer;
				smartPtr.pointer = nullptr;
				counter = smartPtr.counter;
				smartPtr.counter = nullptr;
				return *this;
			}

			inline bool operator==(const SmartPointer&) const;
			inline bool operator!=(const SmartPointer&) const;
			inline bool operator==(T*) const;
			inline bool operator!=(T*) const;
			inline bool operator!() const;
			inline T& operator*() const;
			inline T* operator->() const;

			void swap(SmartPointer& swapPointer) {				
				T* tempPointer = swapPointer.pointer;
				Counter* tempCounter = swapPointer.counter;
				swapPointer.pointer = pointer;
				swapPointer.counter = counter;
				pointer = tempPointer;
				counter = tempCounter;
			}

			inline Counter* getCounter();

		private:
			T* pointer;
			Counter* counter = nullptr;

			void checkCountersAndDelete() {
				if (counter) {
					if (counter->weakCount == 0 && counter->smartCount == 1) {
						counter->smartCount--;
						delete counter;
						delete pointer;
					}
					else if (counter->smartCount > 1) {
						counter->smartCount--;
					}
					else {
						delete pointer;
					}
				}
			}
		};
	}
}
#include "SmartPointer_Inl.h"