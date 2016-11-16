#include "..\Actor.h"

namespace Engine {
	Actor::Actor(char *i_name, Vector2D i_position) :name(_strdup(i_name)), position(i_position) {}
}