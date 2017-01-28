#pragma once
#include <assert.h>
#include "Counter.h"

namespace Engine {
	namespace Pointer {		
		template<class T>
		class SmartPointer {
		public:
			SmartPointer(T* ptr = nullptr);
			SmartPointer(const SmartPointer&);
			SmartPointer(SmartPointer&&);
			inline ~SmartPointer();
			SmartPointer& operator=(const SmartPointer&);
			SmartPointer& operator=(SmartPointer&&);
			inline bool operator==(const SmartPointer&) const;
			inline bool operator==(T&) const;
			inline bool operator!() const;
			inline T& operator*() const;
			inline T* operator->() const;
			void swap(SmartPointer&);
		private:
			T* pointer;
			Counter* counter;
			void checkCountersAndDelete();
		};
	}
}
#include "SmartPointer_Inl.h"