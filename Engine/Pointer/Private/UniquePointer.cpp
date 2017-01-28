#include "../UniquePointer.h"
namespace Engine {
	namespace Pointer {		
		
		template<class T>
		void UniquePointer<T>::TakePointer(UniquePointer& uniquePointer) {
			pointer = uniquePointer->pointer;
			uniquePointer->pointer = nullptr;
		}
	}
}