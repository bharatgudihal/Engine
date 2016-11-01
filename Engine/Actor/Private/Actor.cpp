#include "..\Actor.h"
#include "..\..\Math\Vector2D.h"

namespace Engine {
	Actor::Actor(char *i_name, Vector2D i_position) :name(i_name), position(i_position) {}
}