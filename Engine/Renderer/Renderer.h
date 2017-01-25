#pragma once
#include <assert.h>
#include "GLib.h"
#include "../Actor/Actor.h"

namespace Engine {
	namespace Renderer {
		GLib::Sprites::Sprite * CreateSprite(void* file, size_t sizeOfFile);
		void Draw(Actor* actor, GLib::Sprites::Sprite* sprite);
	}
}