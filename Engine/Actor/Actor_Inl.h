#include "..\Math\Vector2D.h"

namespace Engine {
	inline char* Actor::getName() { return name; }
	inline Vector2D Actor::getPosition() { return position; }
	inline void Actor::setPosition(const Vector2D newPosition) { position = newPosition; }
}