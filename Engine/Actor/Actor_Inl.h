#include "..\Math\Vector3.h"

namespace Engine {
	inline Actor::Actor(const char *i_name, Math::Vector3 i_position) :name(i_name), position(i_position) {
		DEBUG_LOG("Actor constructor called duplicating char at location %p into location %p\n",i_name,name); 
	}

	inline Actor::Actor(const Actor& other) : name(other.name), position(other.position) {
		DEBUG_LOG("Actor copy constructor called duplicating char at location %p into location %p\n", other.name, name);
	}	
	inline String::HashedString Actor::getNameHash() const { return name; }
	inline Math::Vector3 Actor::getPosition() const { return position; }
	inline void Actor::setPosition(const Math::Vector3 newPosition) { position = newPosition; }
	inline Math::Vector3 Actor::getDirection() const { return direction; }
	inline void Actor::setDirection(const Math::Vector3 newDirection) { direction = newDirection; }

	inline Actor::Actor(Actor&& other) : name(other.name), position(other.position) {
		DEBUG_LOG("Actor move copy constructor called\n", other.name, name);
		other.name = nullptr;
	}

	inline Actor& Actor::operator=(Actor&& rhs) {		
		std::swap(name, rhs.name);
		std::swap(position, rhs.position);
		DEBUG_LOG("Actor move assignment operator called swapping chars at location %p with location %p\n", rhs.name, name);
		return *this;
	}
}