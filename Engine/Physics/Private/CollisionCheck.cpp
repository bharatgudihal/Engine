#include "../CollisionCheck.h"

namespace Engine {
	namespace Physics {
		namespace Collision {

			bool TestCollisionOfBInA(GameObject::GameObject* objectA, GameObject::GameObject* objectB, float deltaTime, float& o_latestTClose, float& o_earliestTOpen, 
				float& o_collisionTime, Math::Vector4& o_collisionNormal) {

				bool isSeparated;
				float tStart = 0.0f;
				float tEnd = deltaTime;
				Math::Opt::Matrix ATranslationMatrix = Math::Matrix::GetTranslationMatrix((*(objectA->GetActorReference()))->GetPosition());
				Math::Opt::Matrix ARotationMatrix = Math::Matrix::GetZRotationMatrix((*(objectA->GetActorReference()))->GetRotation().Z());
				Math::Opt::Matrix AtoWorld = ATranslationMatrix * ARotationMatrix;
				Math::Opt::Matrix WorldToA = AtoWorld.GetStandardMatrix().GetInverse();
				Math::Opt::Matrix BTranslationMatrix = Math::Matrix::GetTranslationMatrix((*(objectB->GetActorReference()))->GetPosition());
				Math::Opt::Matrix BRotationMatrix = Math::Matrix::GetZRotationMatrix((*(objectB->GetActorReference()))->GetRotation().Z());
				Math::Opt::Matrix BtoWorld = BTranslationMatrix * BRotationMatrix;
				Math::Opt::Matrix WorldToB = BtoWorld.GetStandardMatrix().GetInverse();
				Math::Opt::Matrix BtoA = WorldToA * BtoWorld;
				Math::Opt::Matrix AtoB = WorldToB * AtoWorld;
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
				Math::Opt::Vector3 normal = collisionPair.collisionNormal;
				Math::Opt::Vector3 velocityA;
				Math::Opt::Vector3 velocityB;
				if (collisionPair.collisionObjects[0]->GetPhysicsBody()) {
					velocityA = collisionPair.collisionObjects[0]->GetPhysicsBody()->GetVelocity();
				}
				if (collisionPair.collisionObjects[1]->GetPhysicsBody()) {
					velocityB = collisionPair.collisionObjects[1]->GetPhysicsBody()->GetVelocity();
				}
				if (collisionPair.collisionObjects[0]->GetController() && !collisionPair.collisionObjects[0]->GetController()->OnCollisionEnter(collisionPair.collisionNormal, collisionPair.collisionObjects[1])) {
					Math::Opt::Vector3 forwardA = (*(collisionPair.collisionObjects[0]->GetActorReference()))->GetForward();
					Math::Opt::Vector3 reflectionForwardA = forwardA - normal*2.0f*Math::Opt::dot(normal, forwardA);
					Math::Opt::Vector3 reflectionVelocityA = velocityA - normal*2.0f*Math::Opt::dot(normal, velocityA);
					if (collisionPair.collisionObjects[0]->GetPhysicsBody()) {
						collisionPair.collisionObjects[0]->GetPhysicsBody()->SetVelocity(Math::Vector3(reflectionVelocityA.X(), reflectionVelocityA.Y()));
					}
					(*(collisionPair.collisionObjects[0]->GetActorReference()))->SetForward(Math::Vector3(reflectionForwardA.X(), reflectionForwardA.Y()));
				}
				if (collisionPair.collisionObjects[1]->GetController() && !collisionPair.collisionObjects[1]->GetController()->OnCollisionEnter(collisionPair.collisionNormal, collisionPair.collisionObjects[0])) {
					Math::Opt::Vector3 forwardB = (*(collisionPair.collisionObjects[1]->GetActorReference()))->GetForward();
					Math::Opt::Vector3 reflectionVelocityB = velocityB - normal*2.0f*Math::Opt::dot(normal, velocityB);
					Math::Opt::Vector3 reflectionForwardB = forwardB - normal*2.0f*Math::Opt::dot(normal, forwardB);
					if (collisionPair.collisionObjects[1]->GetPhysicsBody()) {
						collisionPair.collisionObjects[1]->GetPhysicsBody()->SetVelocity(Math::Vector3(reflectionVelocityB.X(), reflectionVelocityB.Y()));
					}

					(*(collisionPair.collisionObjects[1]->GetActorReference()))->SetForward(Math::Vector3(reflectionForwardB.X(), reflectionForwardB.Y()));
				}
			}

			void ResolveCollisions(std::vector<CollisionPair>& collisions) {
				for (size_t i = 0; i < collisions.size(); i++) {
					ResolveCollision(collisions[i]);
				}
			}

			void CheckCollisions(std::vector<GameObject::GameObject*>& sceneObjects, float deltaTime, std::vector<CollisionPair>& collisions) {
				if (sceneObjects.size() > 0) {
					for (size_t i = 0; i < sceneObjects.size() - 1; i++) {
						if (sceneObjects[i]->GetEnabled()) {
							for (size_t j = i + 1; j < sceneObjects.size(); j++) {
								float collisionTime = deltaTime;
								Math::Vector4 collisionNormal;
								CollisionPair collisionPair;
								if (sceneObjects[j]->GetEnabled() && CheckCollision(sceneObjects[i], sceneObjects[j], deltaTime, collisionTime, collisionNormal)) {
									DEBUG_LOG("Collision!\n");
									if (collisionNormal != Math::Vector4::ZERO) {
										collisionPair.collisionTime = collisionTime;
										collisionPair.collisionNormal = collisionNormal.GetVector3();
										collisionPair.collisionObjects[0] = sceneObjects[i];
										collisionPair.collisionObjects[1] = sceneObjects[j];
										collisions.push_back(collisionPair);
									}
								}
							}
						}
					}
				}
			}

			void SimulateObjects(std::vector<GameObject::GameObject*>& sceneObjects, float time) {
				for (size_t i = 0; i < sceneObjects.size(); i++) {
					if (sceneObjects[i]->GetPhysicsBody()) {
						sceneObjects[i]->GetPhysicsBody()->PhysicsUpdate(time);
					}
				}
			}

			void Update(std::vector<GameObject::GameObject*>& sceneObjects, float deltaTime) {
				int collisionCheckIterationCount = 0;
				float currentDeltaTime = deltaTime;
				std::vector<CollisionPair> collisions;
				CheckCollisions(sceneObjects, currentDeltaTime, collisions);
				ResolveCollisions(collisions);
			}				
		}
	}
}