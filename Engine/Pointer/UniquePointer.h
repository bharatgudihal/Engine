#pragma once
#include <assert.h>

namespace Engine {
	namespace Pointer {
		template<class T>
		class UniquePointer {
		public:
			inline UniquePointer(T* ptr = nullptr);
			inline UniquePointer(UniquePointer&);
			inline UniquePointer(UniquePointer&&);
			inline ~UniquePointer();
			UniquePointer& operator=(UniquePointer&);
			UniquePointer& operator=(UniquePointer&&);
			inline bool operator==(const UniquePointer&) const;
			inline bool operator==(T&) const;
			inline bool operator!() const;
			inline T& operator*() const;
			inline T* operator->() const;
		private:
			T* pointer;
			void TakePointer(UniquePointer&);
		};
	}
}
#include "UniquePointer_Inl.h"