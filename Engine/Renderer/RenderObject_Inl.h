#pragma once
namespace Engine {
	namespace Renderer {
		inline RenderObject* RenderObject::Create(Actor* i_actor, void* file, size_t fileSize) {
			return new RenderObject(i_actor, file, fileSize);
		}

		inline RenderObject::RenderObject(Actor* i_actor, void* file, size_t fileSize) :actor(i_actor) {
			sprite = CreateSprite(file, fileSize);
		}

		inline RenderObject::~RenderObject() {
			if (sprite) {
				GLib::Sprites::Release(sprite);
			}
		}

		inline Actor* RenderObject::GetActor() const {
			return actor;
		}

		inline GLib::Sprites::Sprite* RenderObject::Sprite() const {
			return sprite;
		}
 	}
}