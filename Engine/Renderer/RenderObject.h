#pragma once
#include "GLib.h"
#include "../Pointer/WeakPointer.h"
#include "../Actor/Actor.h"
#include "Renderer.h"

namespace Engine {	
	namespace Renderer {
		class RenderObject {
		public:
			inline static RenderObject* Create(const Pointer::SmartPointer<Actor> smartPointer, void* file, size_t fileSize);
			~RenderObject();
			inline Pointer::WeakPointer<Actor> GetPointer() const;
			inline GLib::Sprites::Sprite* Sprite() const;
		private:
			RenderObject();
			inline RenderObject(Pointer::SmartPointer<Actor> smartPointer, void* file, size_t fileSize);
			GLib::Sprites::Sprite* sprite;
			Pointer::WeakPointer<Actor> weakPointer;
		};
	}
}
#include "RenderObject_Inl.h"