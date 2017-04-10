#pragma once
#include <vector>
#include "../GameObject/GameObject.h"
#include "../Math/Matrix.h"
#include "../Logger/Logger.h"
#include "../Math/Vector3_Opt.h"

namespace Engine {
	namespace Physics {
		namespace Collision {
#define MAXCOLLISIONCHECKS 50			
			void Update(std::vector<GameObject::GameObject*>&, float);
			struct CollisionPair {
				float collisionTime;
				Math::Vector3 collisionNormal;
				GameObject::GameObject* collisionObjects[2];
			};
		}
	}
}