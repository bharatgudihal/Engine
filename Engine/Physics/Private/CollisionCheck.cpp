#include "../CollisionCheck.h"

namespace Engine {
	namespace Physics {
		namespace Collision {

			bool TestCollisionOfBInA(GameObject::GameObject* objectA, GameObject::GameObject* objectB) {
				bool isSeparated;
				Math::Matrix ATranslationMatrix = Math::Matrix::GetTranslationMatrix((*(objectA->GetActorReference()))->getPosition());
				Math::Matrix ARotationMatrix = Math::Matrix::GetZRotationMatrix((*(objectA->GetActorReference()))->getRotation().Z());
				Math::Matrix AtoWorld = ATranslationMatrix * ARotationMatrix;
				Math::Matrix BTranslationMatrix = Math::Matrix::GetTranslationMatrix((*(objectB->GetActorReference()))->getPosition());
				Math::Matrix BRotationMatrix = Math::Matrix::GetZRotationMatrix((*(objectB->GetActorReference()))->getRotation().Z());
				Math::Matrix BtoWorld = BTranslationMatrix * BRotationMatrix;
				Math::Matrix BtoA = AtoWorld.GetInverse() * BtoWorld;
				Math::Matrix AtoB = BtoWorld.GetInverse() * AtoWorld;
				Math::Vector4 BCenterInA = BtoA * (*(objectB->GetActorReference()))->getBounds().Center;
				Math::Vector4 BExtentsXInA = BtoA * Math::Vector4((*(objectB->GetActorReference()))->getBounds().Extents.X(), 0.0f, 0.0f, 0.0f);
				Math::Vector4 BExtentsYInA = BtoA * Math::Vector4(0.0f, (*(objectB->GetActorReference()))->getBounds().Extents.Y(), 0.0f, 0.0f);
				float BProjectionOnA_X = fabs(BExtentsXInA.X()) + fabs(BExtentsYInA.X());
				isSeparated = fabs(BCenterInA.X() - (*(objectA->GetActorReference()))->getBounds().Center.X()) > (*(objectA->GetActorReference()))->getBounds().Extents.X() + BProjectionOnA_X;
				if (!isSeparated) {
					float BProjectionOnA_Y = fabs(BExtentsXInA.Y()) + fabs(BExtentsYInA.Y());
					isSeparated = fabs(BCenterInA.Y() - (*(objectA->GetActorReference()))->getBounds().Center.Y()) > (*(objectA->GetActorReference()))->getBounds().Extents.Y() + BProjectionOnA_Y;
				}
				return !isSeparated;
			}

			bool CheckCollision(GameObject::GameObject* objectA, GameObject::GameObject* objectB) {
				bool result = false;				
				result = TestCollisionOfBInA(objectA, objectB);
				if (result) {
					result = TestCollisionOfBInA(objectB, objectA);
				}
				return result;
			}

			void CheckCollisions(std::vector<GameObject::GameObject*>& sceneObjects) {				
				for (int i = 0; i < sceneObjects.size(); i++) {
					for (int j = 0; j < sceneObjects.size(); j++) {
						if (i != j) {
							if (CheckCollision(sceneObjects[i], sceneObjects[j])) {
								DEBUG_LOG("Collision!\n");
								break;
							}
						}
					}
				}
			}
		}
	}
}