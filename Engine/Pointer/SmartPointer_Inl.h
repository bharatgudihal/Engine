#pragma once
namespace Engine {
	namespace Pointer {

		template<class T>
		inline SmartPointer<T>::~SmartPointer() {
			checkCountersAndDelete();
		}

		template<class T>
		inline bool SmartPointer<T>::operator==(const SmartPointer& smartPtr) const{
			return pointer == smartPtr.pointer;
		}

		template<class T>
		inline bool SmartPointer<T>::operator!=(const SmartPointer& smartPtr) const {
			return pointer != smartPtr.pointer;
		}

		template<class T>
		inline bool SmartPointer<T>::operator==(T* ptr) const{
			return pointer == ptr;
		}

		template<class T>
		inline bool SmartPointer<T>::operator!=(T* ptr) const {
			return pointer != ptr;
		}

		template<class T>
		inline bool SmartPointer<T>::operator!() const{
			return pointer == nullptr;
		}

		template<class T>
		inline T& SmartPointer<T>::operator*() const {
			assert(pointer);
			return *pointer;
		}

		template<class T>
		inline T* SmartPointer<T>::operator->() const {
			assert(pointer);
			return pointer;
		}

		template<class T>
		inline Counter* SmartPointer<T>::getCounter() {
			return counter;
		}
	}
}