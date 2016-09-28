#ifndef ACTOR_H
#define ACTOR_H
#include "..\Math\Vector2D.h"

namespace Engine {
	class Actor {
	public:
		Actor() {};
		Actor(char *i_name, Vector2D i_position);
		char* getName();
		Vector2D getPosition();
		void setPosition(const Vector2D newPosition);
	private:
		char *name;
		Vector2D position = Vector2D(0, 0);
	};
}
#endif
