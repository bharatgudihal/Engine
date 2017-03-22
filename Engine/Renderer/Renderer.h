#pragma once
#include <assert.h>
#include <vector>
#include "GLib.h"

namespace Engine {
	namespace GameObject {
		class GameObject;
	}
	namespace Renderer {
#define DEGREES2RADIANS 0.0174533f
		class RenderObject;
		GLib::Sprites::Sprite * CreateSprite(void* file, size_t sizeOfFile);
		void DrawAll(std::vector<GameObject::GameObject*>&);
		void Draw(const RenderObject* renderObject);
	}
}