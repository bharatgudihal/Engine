#pragma once
#include "SmartPointer.h"
namespace Engine {
	namespace Pointer {
		template<class T>
		class WeakPointer {
		public:
			WeakPointer(const SmartPointer<T>& smartPtr = nullptr);
			WeakPointer(const WeakPointer&);
			WeakPointer(WeakPointer&&);
			inline ~WeakPointer();
			WeakPointer& operator=(const WeakPointer&);
			WeakPointer& operator=(WeakPointer&&);
			inline bool operator==(const WeakPointer&) const;
			inline bool operator==(T&) const;
			inline bool operator!() const;
			inline T& operator*() const;
			inline T* operator->() const;
			void swap(WeakPointer&);
			inline SmartPointer* Acquire() const;
		private:
			SmartPointer* smartPointer;
			Counter* counter;
			void decrementCounter();
		};
	}
}
#include "WeakPointer_Inl.h"