#include "../Renderer.h"

namespace Engine {
	namespace Renderer {
		GLib::Sprites::Sprite * CreateSprite(void* file, size_t sizeOfFile) {
			GLib::Texture * texture = file ? GLib::CreateTexture(file, sizeOfFile) : nullptr;			
			if (texture == nullptr) {
				return nullptr;
			}
			unsigned int width = 0;
			unsigned int height = 0;
			unsigned int depth = 0;
			bool result = GLib::GetDimensions(texture, width, height, depth);
			assert(result);
			assert((width > 0) && (height > 0));
			GLib::Sprites::SpriteEdges edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
			GLib::Sprites::SpriteUVs UVs = { { 0.0f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f } };
			GLib::RGBA Color = { 255, 255, 255, 255 };
			GLib::Sprites::Sprite * sprite = GLib::Sprites::CreateSprite(edges, 0.1f, Color, UVs);
			if (sprite == nullptr)
			{
				GLib::Release(texture);
				return nullptr;
			}
			GLib::Sprites::SetTexture(*sprite, *texture);
			return sprite;
		}

		void Draw(Actor* actor, GLib::Sprites::Sprite* sprite) {
			GLib::BeginRendering();
			GLib::Sprites::BeginRendering();
			GLib::Point2D position = { actor->getPosition().X(), actor->getPosition().Y() };
			GLib::Sprites::RenderSprite(*sprite, position, 0.0f);
			GLib::Sprites::EndRendering();
			GLib::EndRendering();
		}
	}
}