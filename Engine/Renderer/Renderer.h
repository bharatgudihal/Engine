#pragma once
#include <assert.h>
#include "GLib.h"

namespace Engine {
	namespace Renderer {
		class RenderObject;
		GLib::Sprites::Sprite * CreateSprite(void* file, size_t sizeOfFile);
		void Draw(const RenderObject* renderObject);
	}
}