#pragma once
namespace Engine {
	namespace Pointer {

		template<class T>
		inline UniquePointer<T>::UniquePointer(T* ptr = nullptr) :pointer(ptr) {}

		template<class T>
		inline UniquePointer<T>::UniquePointer(UniquePointer& uniquePointer) {
			TakePointer(uniquePointer);
		}

		template<class T>
		inline UniquePointer<T>::UniquePointer(UniquePointer&& uniquePointer) {
			TakePointer(uniquePointer);
		}

		template<class T>
		inline UniquePointer<T>::~UniquePointer() {
			if (pointer) {
				delete pointer;
			}
		}

		template<class T>
		UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer& uniquePointer) {
			TakePointer(uniquePointer);
		}

		template<class T>
		UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer&& uniquePointer) {
			TakePointer(uniquePointer);
		}

		template<class T>
		inline bool UniquePointer<T>::operator==(const UniquePointer& uniquePointer) const {
			return pointer == uniquePointer->pointer;
		}

		template<class T>
		inline bool UniquePointer<T>::operator==(T& ptr) const {
			return pointer == ptr;
		}

		template<class T>
		inline bool UniquePointer<T>::operator!() const {
			return pointer == nullptr;
		}

		template<class T>
		inline T& UniquePointer<T>::operator*() const {
			assert(pointer);
			return *pointer;
		}

		template<class T>
		inline T* UniquePointer<T>::operator->() const {
			assert(pointer);
			return pointer;
		}
	}
}