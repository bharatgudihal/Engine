#pragma once
#include <vector>
#include "../GameObject/GameObject.h"

namespace Engine{	
	namespace Controller {
		void UpdateAll(std::vector<GameObject::GameObject*>&,float);
	}
}