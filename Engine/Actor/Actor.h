#ifndef ACTOR_H
#define ACTOR_H
#include <string.h>
#include <malloc.h>
#include <algorithm>
#include "..\Math\Vector2D.h"
#include "..\Logger\Logger.h"

namespace Engine {
	class Actor {
	public:
		Actor();		
		~Actor();
		inline Actor(char *i_name, Vector2D i_position);
		inline Actor(const Actor& other);
		inline Actor(Actor&& other);
		Actor& operator=(const Actor& rhs);
		inline Actor& operator=(Actor&& rhs);
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