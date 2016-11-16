#ifndef ACTOR_H
#define ACTOR_H
#include "..\Math\Vector2D.h"
#include <string.h>
#include <malloc.h>

namespace Engine {
	class Actor {
	public:
		Actor();
		~Actor();
		inline Actor(char *i_name, Vector2D i_position);
		inline char* getName() const;
		inline Vector2D getPosition() const;
		inline void setPosition(const Vector2D newPosition);
		inline Vector2D getDirection() const;
		inline void setDirection(const Vector2D newDirection);
	private:
		char *name;
		Vector2D position = Vector2D::ZERO;
		Vector2D direction = Vector2D::ZERO;
	};
}
#include "Actor_Inl.h"
#endif