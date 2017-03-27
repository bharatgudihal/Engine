#include "..\Math\Vector3.h"

namespace Engine {
	inline Actor::Actor(const char *i_name, Math::Vector3 i_position, Math::AABB i_bounds) :name(i_name), position(i_position), bounds(i_bounds) {
		DEBUG_LOG("Actor constructor called duplicating char at location %p into location %p\n",i_name,name); 
	}

	inline Actor::Actor(const Actor& other) : name(other.name), position(other.position) {
		DEBUG_LOG("Actor copy constructor called duplicating char at location %p into location %p\n", other.name, name);
	}	
	inline String::HashedString Actor::GetNameHash() const { return name; }

	inline Math::Vector3 Actor::GetPosition() const { return position; }

	inline void Actor::SetPosition(const Math::Vector3& newPosition) { position = newPosition; }

	inline Math::Vector3 Actor::GetForward() const { return forward; }

	inline void Actor::SetForward(const Math::Vector3& newForward) { forward = newForward; }

	inline Math::Vector3 Actor::GetRotation() const { return rotation; }

	inline void Actor::SetRotation(const Math::Vector3& newRotation) { rotation = newRotation; }

	inline const Math::AABB Actor::GetBounds() const { return bounds; };

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