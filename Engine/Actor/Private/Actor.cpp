#include "..\Actor.h"

namespace Engine {
	Actor::Actor():name(nullptr){}

	Actor::~Actor(){}

	Actor& Actor::operator=(const Actor& rhs) {		
		name = rhs.name;
		position = rhs.position;
		DEBUG_LOG("Actor copy assignment operator called duplicating char at location %p into location %p\n", rhs.name, name);
		return *this;
	}
}