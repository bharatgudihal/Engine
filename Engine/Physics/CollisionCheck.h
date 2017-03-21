#pragma once
#include <vector>
#include "../GameObject/GameObject.h"
#include "../Math/Matrix.h"
#include "../Logger/Logger.h"

namespace Engine {
	namespace Physics {
		namespace Collision {
			void CheckCollisions(std::vector<GameObject::GameObject*>&);
		}
	}
}