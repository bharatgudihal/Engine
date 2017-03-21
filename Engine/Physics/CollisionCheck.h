#pragma once
#include <vector>
#include "../GameObject/GameObject.h"

namespace Engine {
	namespace Physics {
		namespace Collision {
			void CheckCollisions(std::vector<GameObject::GameObject*>&);
		}
	}
}