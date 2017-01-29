#pragma once
namespace Engine {
	namespace Pointer {

		template<class T>
		inline WeakPointer<T>::~WeakPointer() {
			decrementCounter();
		}

		template<class T>
		inline bool WeakPointer<T>::operator==(const WeakPointer& weakPointer) const {
			return smartPointer == weakPointer.smartPointer;
		}

		template<class T>
		inline bool WeakPointer<T>::operator==(T* smartPtr) const {
			return smartPointer == smartPtr;
		}

		template<class T>
		inline bool WeakPointer<T>::operator!() const {
			return smartPointer == nullptr;
		}

		template<class T>
		inline SmartPointer<T>* WeakPointer<T>::Acquire() const{
			return smartPointer;
		}
	}
}