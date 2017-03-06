#ifndef ACTOR_H
#define ACTOR_H
#include <string.h>
#include <malloc.h>
#include <algorithm>
#include "..\Math\Vector.h"
#include "..\Logger\Logger.h"
#include "..\String\HashedString.h"

namespace Engine {
	class Actor {
	public:
		Actor();		
		~Actor();
		inline Actor(const char *i_name, Vector i_position);
		inline Actor(const Actor& other);
		inline Actor(Actor&& other);
		Actor& operator=(const Actor& rhs);
		inline Actor& operator=(Actor&& rhs);
		inline String::HashedString getNameHash() const;
		inline Vector getPosition() const;
		inline void setPosition(const Vector newPosition);
		inline Vector getDirection() const;
		inline void setDirection(const Vector newDirection);
	private:
		String::HashedString name;
		Vector position = Vector::ZERO;
		Vector direction = Vector::ZERO;
	};
}
#include "Actor_Inl.h"
#endif