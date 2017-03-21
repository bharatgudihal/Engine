#include "../Physics.h"

namespace Engine {
	namespace Physics {
		void UpdateAll(std::vector<GameObject::GameObject*>& sceneObjects, float deltaTime) {
			for (int i = 0; i < sceneObjects.size(); i++) {
				if (sceneObjects[i]->GetPhysicsBody() != nullptr) {
					sceneObjects[i]->GetPhysicsBody()->PhysicsUpdate(deltaTime);
				}
			}
		}
	}
}