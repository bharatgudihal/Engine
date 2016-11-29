#include "..\Actor.h"

namespace Engine {
	Actor::Actor():name(nullptr){}

	Actor::~Actor(){
		if (name) {
			DEBUG_LOG("Actor destructor called freeing char at location %p\n", name);
			free(name);
		}
	}

	Actor& Actor::operator=(const Actor& rhs) {
		if (name) {
			free(name);
		}
		name = _strdup(rhs.name);
		position = rhs.position;
		DEBUG_LOG("Actor copy assignment operator called duplicating char at location %p into location %p\n", rhs.name, name);
		return *this;
	}
}