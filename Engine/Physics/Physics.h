#pragma once
#include <vector>
#include "../GameObject/GameObject.h"

namespace Engine {
	namespace Physics {
		void UpdateAll(std::vector<GameObject::GameObject*>&, float);
	}
}