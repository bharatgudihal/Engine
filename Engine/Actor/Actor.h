#ifndef ACTOR_H
#define ACTOR_H
#include "..\Math\Vector2D.h"

namespace Engine {
	class Actor {
	public:
		Actor() {};
		Actor(char *i_name, Vector2D i_position);
		inline char* getName() const;
		inline Vector2D getPosition() const;
		inline void setPosition(const Vector2D newPosition);
	private:
		char *name;
		Vector2D position = Vector2D(0, 0);
	};
}
#include "Actor_Inl.h"
#endif