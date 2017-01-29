#pragma once
namespace Engine {
	namespace Renderer {
		inline RenderObject* RenderObject::Create(const Pointer::SmartPointer<Actor> smartPointer, void* file, size_t fileSize) {
			return new RenderObject(smartPointer, file, fileSize);
		}

		inline RenderObject::RenderObject(Pointer::SmartPointer<Actor> smartPtr, void* file, size_t fileSize):weakPointer(smartPtr){
			sprite = CreateSprite(file, fileSize);
		}

		inline RenderObject::~RenderObject() {
			if (sprite) {
				GLib::Sprites::Release(sprite);
			}
		}

		inline Pointer::WeakPointer<Actor> RenderObject::GetPointer() const {
			return weakPointer;
		}

		inline GLib::Sprites::Sprite* RenderObject::Sprite() const {
			return sprite;
		}
 	}
}