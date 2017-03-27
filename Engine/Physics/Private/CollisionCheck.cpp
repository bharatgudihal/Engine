#include "../CollisionCheck.h"

namespace Engine {
	namespace Physics {
		namespace Collision {

			bool TestCollisionOfBInA(GameObject::GameObject* objectA, GameObject::GameObject* objectB, float deltaTime, float& o_latestTClose, float& o_earliestTOpen) {
				bool isSeparated;
				float tStart = 0.0f;
				float tEnd = deltaTime;
				Math::Matrix ATranslationMatrix = Math::Matrix::GetTranslationMatrix((*(objectA->GetActorReference()))->GetPosition());
				Math::Matrix ARotationMatrix = Math::Matrix::GetZRotationMatrix((*(objectA->GetActorReference()))->GetRotation().Z());
				Math::Matrix AtoWorld = ATranslationMatrix * ARotationMatrix;
				Math::Matrix WorldToA = AtoWorld.GetInverse();
				Math::Matrix BTranslationMatrix = Math::Matrix::GetTranslationMatrix((*(objectB->GetActorReference()))->GetPosition());
				Math::Matrix BRotationMatrix = Math::Matrix::GetZRotationMatrix((*(objectB->GetActorReference()))->GetRotation().Z());
				Math::Matrix BtoWorld = BTranslationMatrix * BRotationMatrix;
				Math::Matrix WorldToB = BtoWorld.GetInverse();
				Math::Matrix BtoA = WorldToA * BtoWorld;
				Math::Matrix AtoB = WorldToB * AtoWorld;
				Math::Vector4 BCenterInA = BtoA * Math::Vector4((*(objectB->GetActorReference()))->GetBounds().Center, 1.0f);
				Math::Vector4 BExtentsXInA = BtoA * Math::Vector4((*(objectB->GetActorReference()))->GetBounds().Extents.X(), 0.0f, 0.0f, 0.0f);
				Math::Vector4 BExtentsYInA = BtoA * Math::Vector4(0.0f, (*(objectB->GetActorReference()))->GetBounds().Extents.Y(), 0.0f, 0.0f);
				Math::Vector3 VelA = Math::Vector3::ZERO;
				Math::Vector3 VelB = Math::Vector3::ZERO;
				if (objectA->GetPhysicsBody() != nullptr) {
					VelA = objectA->GetPhysicsBody()->GetVelocity();
				}
				if (objectB->GetPhysicsBody() != nullptr) {
					VelB = objectB->GetPhysicsBody()->GetVelocity();
				}
				Math::Vector3 VelBRelToA = VelB - VelA;
				Math::Vector4 VelBInA = WorldToA * Math::Vector4(VelBRelToA,0.0f);				
				float BProjectionOnA_X = fabs(BExtentsXInA.X()) + fabs(BExtentsYInA.X());
				float AExtents_X = (*(objectA->GetActorReference()))->GetBounds().Extents.X() + BProjectionOnA_X;
				float ALeft = (*(objectA->GetActorReference()))->GetBounds().Center.X() - AExtents_X;
				float ARight = (*(objectA->GetActorReference()))->GetBounds().Center.X() + AExtents_X;
				if (VelBInA.X() != 0) {
					float DClose_X = ALeft - BCenterInA.X();
					float DOpen_X = ARight - BCenterInA.X();
					float tClose = DClose_X / VelBInA.X();
					float tOpen = DOpen_X / VelBInA.X();
					if (tOpen < tClose) {
						//Moving in opposite direction
						float temp = tOpen;
						tOpen = tClose;
						tClose = temp;
					}
					o_latestTClose = tClose;
					o_earliestTOpen = tOpen;
					isSeparated = tClose > tEnd || tOpen < 0.0f;
				}
				else {
					isSeparated = BCenterInA.X() < ALeft || BCenterInA.X() > ARight;
				}
				if (!isSeparated) {
					float BProjectionOnA_Y = fabs(BExtentsXInA.Y()) + fabs(BExtentsYInA.Y());
					float AExtents_Y = (*(objectA->GetActorReference()))->GetBounds().Extents.Y() + BProjectionOnA_Y;
					float ABottom = (*(objectA->GetActorReference()))->GetBounds().Center.Y() - AExtents_Y;
					float ATop = (*(objectA->GetActorReference()))->GetBounds().Center.Y() + AExtents_Y;
					if (VelBInA.Y() != 0) {
						float DClose_Y = ABottom - BCenterInA.Y();
						float DOpen_Y = ATop - BCenterInA.Y();
						float tClose = DClose_Y / VelBInA.Y();
						float tOpen = DOpen_Y / VelBInA.Y();
						if (tOpen < tClose) {
							//Moving in opposite direction
							float temp = tOpen;
							tOpen = tClose;
							tClose = temp;
						}
						if (o_latestTClose < tClose) {
							o_latestTClose = tClose;
						}
						if (o_earliestTOpen > tOpen) {
							o_earliestTOpen = tOpen;
						}
						isSeparated = tClose > tEnd || tOpen < 0.0f;
					}
					else {
						isSeparated = BCenterInA.Y() < ABottom || BCenterInA.X() > ATop;
					}
				}
				return !isSeparated;
			}

			bool CheckCollision(GameObject::GameObject* objectA, GameObject::GameObject* objectB, float deltaTime, float& o_collisionTime, Math::Vector3& o_collisionNormal) {
				bool result = false;
				float latestTCloseAB = 0.0f;
				float earliestTOpenAB = 0.0f;
				float latestTCloseBA = 0.0f;
				float earliestTOpenBA = 0.0f;
				result = TestCollisionOfBInA(objectA, objectB, deltaTime, latestTCloseAB, earliestTOpenAB);
				if (result) {
					result = TestCollisionOfBInA(objectB, objectA, deltaTime, latestTCloseBA, earliestTOpenBA);
					if (result) {
						float latestClose = latestTCloseAB > latestTCloseBA ? latestTCloseAB : latestTCloseBA;
						float earliestOpen = earliestTOpenAB > earliestTOpenBA ? earliestTOpenAB : earliestTOpenBA;
						result = latestClose < earliestOpen;						
					}
				}
				return result;
			}

			void ResolveCollision(CollisionPair& collisionPair) {

			}			

			CollisionPair CheckCollisions(std::vector<GameObject::GameObject*>& sceneObjects, float deltaTime) {
				CollisionPair earlierCollision;
				if (sceneObjects.size() > 0) {
					for (int i = 0; i < sceneObjects.size() - 1; i++) {
						for (int j = i + 1; j < sceneObjects.size(); j++) {
							float collisionTime;
							Math::Vector3 collisionNormal;
							if (CheckCollision(sceneObjects[i], sceneObjects[j], deltaTime, collisionTime, collisionNormal)) {
								DEBUG_LOG("Collision! between %d and %d\n", (*(sceneObjects[i]->GetActorReference()))->GetNameHash() && (*(sceneObjects[j]->GetActorReference()))->GetNameHash());
								break;
							}
						}
					}
				}
				return earlierCollision;
			}

			void Update(std::vector<GameObject::GameObject*>& sceneObjects, float deltaTime) {
				int collisionCheckIterationCount = 0;
				while (collisionCheckIterationCount < MAXCOLLISIONCHECKS) {
					CollisionPair earliestCollision = CheckCollisions(sceneObjects, deltaTime);
					if (earliestCollision.collisionNormal == Math::Vector3::ZERO) {
						break;
					}
					else {
						ResolveCollision(earliestCollision);
					}
					collisionCheckIterationCount++;
				}
			}
		}
	}
}