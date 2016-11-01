#include "..\Math\Vector2D.h"

namespace Engine {
	inline char* Actor::getName() const { return name; }
	inline Vector2D Actor::getPosition() const { return position; }
	inline void Actor::setPosition(const Vector2D newPosition) { position = newPosition; }
}