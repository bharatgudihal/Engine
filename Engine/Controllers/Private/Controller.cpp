#include "../Controller.h"

namespace Engine {
	namespace Controller {
		void UpdateAll(std::vector<GameObject::GameObject*>& sceneObjects, float deltaTime) {
			for (int i = 0; i < sceneObjects.size(); i++) {
				if (sceneObjects[i]->GetController() != nullptr) {
					sceneObjects[i]->GetController()->Update(deltaTime);
				}
			}
		}
	}
}