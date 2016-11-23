#include "..\Math\Vector2D.h"

namespace Engine {
	inline Actor::Actor(char *i_name, Vector2D i_position) :name(_strdup(i_name?i_name:"Default")), position(i_position) {}
	inline char* Actor::getName() const { return name; }
	inline Vector2D Actor::getPosition() const { return position; }
	inline void Actor::setPosition(const Vector2D newPosition) { position = newPosition; }
	inline Vector2D Actor::getDirection() const { return direction; }
	inline void Actor::setDirection(const Vector2D newDirection) { direction = newDirection; }
}