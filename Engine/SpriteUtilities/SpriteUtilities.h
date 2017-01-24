#pragma once
#include <assert.h>
#include "GLib.h"

namespace Engine {
	namespace SpriteUtilities {
		GLib::Sprites::Sprite * CreateSprite(void* file, size_t sizeOfFile);
	}
}