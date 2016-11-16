#include "..\Actor.h"

namespace Engine {
	Actor::Actor():name(nullptr){}

	Actor::~Actor(){
		if (name) {
			free(name);
		}
	}
}