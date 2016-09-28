#include "..\Actor.h"
#include "..\..\Math\Vector2D.h"

namespace Engine {
	Actor::Actor(char *i_name, Vector2D i_position) :name(i_name), position(i_position) {}
	char* Actor::getName() { return name; }
	Vector2D Actor::getPosition() { return position; }
	void Actor::setPosition(const Vector2D newPosition) { position = newPosition; }
}