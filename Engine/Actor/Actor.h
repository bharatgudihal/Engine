#ifndef ACTOR_H
#define ACTOR_H
#include <string.h>
#include <malloc.h>
#include <algorithm>
#include "..\Math\Vector3.h"
#include "..\Logger\Logger.h"
#include "..\String\HashedString.h"

namespace Engine {
	class Actor {
	public:
		Actor();		
		~Actor();
		inline Actor(const char *i_name, Math::Vector3 i_position);
		inline Actor(const Actor& other);
		inline Actor(Actor&& other);
		Actor& operator=(const Actor& rhs);
		inline Actor& operator=(Actor&& rhs);
		inline String::HashedString getNameHash() const;
		inline Math::Vector3 getPosition() const;
		inline void setPosition(const Math::Vector3 newPosition);
		inline Math::Vector3 getDirection() const;
		inline void setDirection(const Math::Vector3 newDirection);
	private:
		String::HashedString name;
		Math::Vector3 position = Math::Vector3::ZERO;
		Math::Vector3 direction = Math::Vector3::ZERO;
	};
}
#include "Actor_Inl.h"
#endif