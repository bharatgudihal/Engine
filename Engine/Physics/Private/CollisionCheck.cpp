#include "../CollisionCheck.h"

namespace Engine {
	namespace Physics {
		namespace Collision {

			bool TestCollisionOfBInA(GameObject::GameObject* objectA, GameObject::GameObject* objectB, float deltaTime, float& o_latestTClose, float& o_earliestTOpen, 
				float& o_collisionTime, Math::Vector4& o_collisionNormal) {

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
				Math::Vector4 VelBInA = WorldToA * Math::Vector4(VelBRelToA, 0.0f);				
				float BProjectionOnA_X = fabs(BExtentsXInA.X()) + fabs(BExtentsYInA.X());
				float AExtents_X = (*(objectA->GetActorReference()))->GetBounds().Extents.X() + BProjectionOnA_X;
				float ALeft = (*(objectA->GetActorReference()))->GetBounds().Center.X() - AExtents_X;
				float ARight = (*(objectA->GetActorReference()))->GetBounds().Center.X() + AExtents_X;
				if (VelBInA.X() != 0.0f) {
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
					if (!isSeparated && tClose > 0.0f && o_collisionTime > tClose) {
						o_collisionTime = tClose;						
						o_collisionNormal = AtoWorld * Math::Vector4(1.0f,0.0f,0.0f,0.0f);
					}
				}
				else {
					isSeparated = BCenterInA.X() < ALeft || BCenterInA.X() > ARight;
					if (!isSeparated) {
						o_collisionNormal = AtoWorld * Math::Vector4(1.0f, 0.0f, 0.0f, 0.0f);
					}
				}
				if (!isSeparated) {
					float BProjectionOnA_Y = fabs(BExtentsXInA.Y()) + fabs(BExtentsYInA.Y());
					float AExtents_Y = (*(objectA->GetActorReference()))->GetBounds().Extents.Y() + BProjectionOnA_Y;
					float ABottom = (*(objectA->GetActorReference()))->GetBounds().Center.Y() - AExtents_Y;
					float ATop = (*(objectA->GetActorReference()))->GetBounds().Center.Y() + AExtents_Y;
					if (VelBInA.Y() != 0.0f) {
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
						if (!isSeparated && tClose > 0.0f && o_collisionTime > tClose) {
							o_collisionTime = tClose;
							o_collisionNormal = AtoWorld * Math::Vector4(0.0f, 1.0f, 0.0f, 0.0f);
						}
					}
					else {
						isSeparated = BCenterInA.Y() < ABottom || BCenterInA.Y() > ATop;
						if (!isSeparated) {
							o_collisionNormal = AtoWorld * Math::Vector4(0.0f, 1.0f, 0.0f, 0.0f);
						}
					}
				}
				return !isSeparated;
			}

			bool CheckCollision(GameObject::GameObject* objectA, GameObject::GameObject* objectB, float deltaTime, float& o_collisionTime, Math::Vector4& o_collisionNormal) {
				bool result = false;
				float latestTCloseAB = 0.0f;
				float earliestTOpenAB = 0.0f;
				float latestTCloseBA = 0.0f;
				float earliestTOpenBA = 0.0f;
				result = TestCollisionOfBInA(objectA, objectB, deltaTime, latestTCloseAB, earliestTOpenAB, o_collisionTime, o_collisionNormal);
				if (result) {
					result = TestCollisionOfBInA(objectB, objectA, deltaTime, latestTCloseBA, earliestTOpenBA, o_collisionTime, o_collisionNormal);
					if (result) {
						float latestClose = latestTCloseAB > latestTCloseBA ? latestTCloseAB : latestTCloseBA;
						float earliestOpen = earliestTOpenAB > earliestTOpenBA ? earliestTOpenAB : earliestTOpenBA;
						result = latestClose < earliestOpen;						
					}
				}
				return result;
			}

			void ResolveCollision(CollisionPair& collisionPair) {
				Math::Vector3 normal = collisionPair.collisionNormal;
				normal.Normalize();
				Math::Vector3 velocityA;
				Math::Vector3 velocityB;
				if (collisionPair.collisionObjects[0]->GetPhysicsBody()) {
					velocityA = collisionPair.collisionObjects[0]->GetPhysicsBody()->GetVelocity();
				}
				if (collisionPair.collisionObjects[1]->GetPhysicsBody()) {
					Math::Vector3 velocityB = collisionPair.collisionObjects[1]->GetPhysicsBody()->GetVelocity();
				}
				Math::Vector3 forwardA = (*(collisionPair.collisionObjects[0]->GetActorReference()))->GetForward();
				Math::Vector3 forwardB = (*(collisionPair.collisionObjects[1]->GetActorReference()))->GetForward();
				Math::Vector3 reflectionVelocityA = velocityA - normal*2.0f*Math::dot(normal, velocityA);
				//Math::Vector3 reflectionVelocityA = Math::Vector3::ZERO;
				Math::Vector3 reflectionVelocityB = velocityB - normal*2.0f*Math::dot(normal, velocityB);
				//Math::Vector3 reflectionVelocityB = Math::Vector3::ZERO;
				Math::Vector3 reflectionForwardA = forwardA - normal*2.0f*Math::dot(normal, forwardA);
				//Math::Vector3 reflectionForwardA = Math::Vector3::ZERO;
				Math::Vector3 reflectionForwardB = forwardB - normal*2.0f*Math::dot(normal, forwardB);
				//Math::Vector3 reflectionForwardB = Math::Vector3::ZERO;
				if (collisionPair.collisionObjects[0]->GetPhysicsBody()) {
					collisionPair.collisionObjects[0]->GetPhysicsBody()->SetVelocity(reflectionVelocityA);
				}
				if (collisionPair.collisionObjects[1]->GetPhysicsBody()) {
					collisionPair.collisionObjects[1]->GetPhysicsBody()->SetVelocity(reflectionVelocityB);
				}
				(*(collisionPair.collisionObjects[0]->GetActorReference()))->SetForward(reflectionForwardA);
				(*(collisionPair.collisionObjects[1]->GetActorReference()))->SetForward(reflectionForwardB);
			}

			void ResolveCollisions(std::vector<CollisionPair>& collisions) {
				for (int i = 0; i < collisions.size(); i++) {
					ResolveCollision(collisions[i]);
				}
			}

			void CheckCollisions(std::vector<GameObject::GameObject*>& sceneObjects, float deltaTime, std::vector<CollisionPair>& collisions) {				
				if (sceneObjects.size() > 0) {
					for (int i = 0; i < sceneObjects.size() - 1; i++) {
						for (int j = i + 1; j < sceneObjects.size(); j++) {
							float collisionTime = deltaTime;
							Math::Vector4 collisionNormal;
							CollisionPair collisionPair;
							if (CheckCollision(sceneObjects[i], sceneObjects[j], deltaTime, collisionTime, collisionNormal)) {
								DEBUG_LOG("Collision!\n");								
								collisionPair.collisionTime = collisionTime;
								collisionPair.collisionNormal = collisionNormal.GetVector3();
								collisionPair.collisionObjects[0] = sceneObjects[i];
								collisionPair.collisionObjects[1] = sceneObjects[j];
								collisions.push_back(collisionPair);
								//DEBUG_LOG("Collision! between %d and %d\n", (*(sceneObjects[i]->GetActorReference()))->GetNameHash() && (*(sceneObjects[j]->GetActorReference()))->GetNameHash());
								//break;
							}
						}
					}
				}
			}

			void SimulateObjects(std::vector<GameObject::GameObject*>& sceneObjects, float time) {
				for (int i = 0; i < sceneObjects.size(); i++) {
					if (sceneObjects[i]->GetPhysicsBody()) {
						sceneObjects[i]->GetPhysicsBody()->PhysicsUpdate(time);
					}
				}
			}

			void Update(std::vector<GameObject::GameObject*>& sceneObjects, float deltaTime) {
				int collisionCheckIterationCount = 0;
				float currentDeltaTime = deltaTime;
				std::vector<CollisionPair> collisions;
				//while (collisionCheckIterationCount < MAXCOLLISIONCHECKS) {
					CheckCollisions(sceneObjects, currentDeltaTime, collisions);
					//if (earliestCollision.collisionNormal == Math::Vector3::ZERO || earliestCollision.collisionTime >= currentDeltaTime) {
						//break;
					//}
					//else {
						//DEBUG_LOG("Earliest collision time %f\n", earliestCollision.collisionTime);
						//DEBUG_LOG("Collision normal x:%f, y:%f, z:%f\n", earliestCollision.collisionNormal.X(), earliestCollision.collisionNormal.Y(), earliestCollision.collisionNormal.Z());
						//if (earliestCollision.collisionTime > 0.0f) {
							//currentDeltaTime -= earliestCollision.collisionTime;
						//}
						ResolveCollisions(collisions);
						//SimulateObjects(sceneObjects, earliestCollision.collisionTime);
					//}
					//collisionCheckIterationCount++;
				}				
			//}
		}
	}
}