#pragma once
#include "GLib.h"
#include "../Actor/Actor.h"
#include "Renderer.h"

namespace Engine {	
	namespace Renderer {
		class RenderObject {
		public:
			inline static RenderObject* Create(Actor* i_actor, void* file, size_t fileSize);
			~RenderObject();
			inline Actor* GetActor() const;
			inline GLib::Sprites::Sprite* Sprite() const;
		private:
			RenderObject();
			inline RenderObject(Actor* i_actor, void* file, size_t fileSize);
			GLib::Sprites::Sprite* sprite;
			Actor* actor;
		};
	}
}
#include "RenderObject_Inl.h"