#include "../CollisionCheck.h"

namespace Engine {
	namespace Physics {
		namespace Collision {

			bool CheckSeparation(float VelBInA, float BCenterInA, float BExtentsXInA, float BExtentsYInA, float ExtentsA, float CenterA, float tEnd, float& o_tClose, float& o_tOpen) {
				//Get B's extents projection
				float BProjectionOnA = fabs(BExtentsXInA) + fabs(BExtentsYInA);
				if (VelBInA != 0.0f) {
					//Calculate DClose
					float DClose = CenterA - ExtentsA - BProjectionOnA - BCenterInA;
					//Calculate DOpen
					float DOpen = CenterA + ExtentsA + BProjectionOnA - BCenterInA;
					//Calculate tClose
					o_tClose = DClose / VelBInA;
					//Calculate tOpen
					o_tOpen = DOpen / VelBInA;
					if (o_tOpen < o_tClose) {
						//Moving in opposite direction
						float temp = o_tOpen;
						o_tOpen = o_tClose;
						o_tClose = temp;
					}
					return (o_tClose > tEnd || o_tOpen < 0.0f);
				}
				else {
					return fabs(CenterA - BCenterInA) > ExtentsA + BProjectionOnA;
				}
			}

			bool TestCollisionOfBInA(GameObject::GameObject* objectA, GameObject::GameObject* objectB, float deltaTime, float& o_latestTClose, float& o_earliestTOpen,
				Math::Vector4& o_collisionNormal) {

				float tStart = 0.0f;
				float tEnd = deltaTime;
				Math::Vector3& positionA = (*(objectA->GetActorReference()))->GetPosition();
				Math::Vector3& positionB = (*(objectB->GetActorReference()))->GetPosition();
				float zRotationA = (*(objectA->GetActorReference()))->GetRotation().Z();
				float zRotationB = (*(objectB->GetActorReference()))->GetRotation().Z();
				Math::Vector3 CenterA = (*(objectA->GetActorReference()))->GetBounds().Center;
				Math::Vector3 ExtentsA = (*(objectA->GetActorReference()))->GetBounds().Extents;
				Math::Vector3 CenterB = (*(objectB->GetActorReference()))->GetBounds().Center;
				Math::Vector3 ExtentsB = (*(objectB->GetActorReference()))->GetBounds().Extents;
				//Get A's translation matrix
				Math::Opt::Matrix ATranslationMatrix = Math::Matrix::GetTranslationMatrix(positionA);
				//Get A's rotation matrix
				Math::Opt::Matrix ARotationMatrix = Math::Matrix::GetZRotationMatrix(zRotationA);
				//Get A to world matrix
				Math::Opt::Matrix AtoWorld = ATranslationMatrix * ARotationMatrix;
				//Get world to A matrix
				Math::Opt::Matrix WorldToA = AtoWorld.GetStandardMatrix().GetInverse();
				//Get B's translation matrix
				Math::Opt::Matrix BTranslationMatrix = Math::Matrix::GetTranslationMatrix(positionB);
				//Get B's rotation matrix
				Math::Opt::Matrix BRotationMatrix = Math::Matrix::GetZRotationMatrix(zRotationB);
				//Get B to world matrix
				Math::Opt::Matrix BtoWorld = BTranslationMatrix * BRotationMatrix;
				//Get world to B matrix
				Math::Opt::Matrix WorldToB = BtoWorld.GetStandardMatrix().GetInverse();
				//Get B to A matrix
				Math::Opt::Matrix BtoA = WorldToA * BtoWorld;
				//Get A to B matrix
				Math::Opt::Matrix AtoB = WorldToB * AtoWorld;
				//Get B's center in A
				Math::Vector4 BCenterInA = BtoA * Math::Vector4(CenterB, 1.0f);
				//Get B's X extents in A
				Math::Vector4 BExtentsXInA = BtoA * Math::Vector4(ExtentsB.X(), 0.0f, 0.0f, 0.0f);
				//Get B's Y extents in A
				Math::Vector4 BExtentsYInA = BtoA * Math::Vector4(0.0f, ExtentsB.Y(), 0.0f, 0.0f);

				Math::Vector3 VelA = Math::Vector3::ZERO;
				Math::Vector3 VelB = Math::Vector3::ZERO;
				if (objectA->GetPhysicsBody() != nullptr) {
					VelA = objectA->GetPhysicsBody()->GetVelocity();
				}
				if (objectB->GetPhysicsBody() != nullptr) {
					VelB = objectB->GetPhysicsBody()->GetVelocity();
				}
				//Get relative velocity of B and A
				Math::Vector3 VelBRelToA = VelB - VelA;
				//Get B's velocity in A
				Math::Vector4 VelBInA = WorldToA * Math::Vector4(VelBRelToA, 0.0f);
				float tcloseX = 0.0f;
				float topenX = 0.0f;
				float tcloseY = 0.0f;
				float topenY = 0.0f;
				bool isSeparatedOnY = true;
				bool isSeparatedOnX = CheckSeparation(VelBInA.X(), BCenterInA.X(), BExtentsXInA.X(), BExtentsYInA.X(), ExtentsA.X(), CenterA.X(), tEnd, tcloseX, topenX);
				if (!isSeparatedOnX) {
					isSeparatedOnY = CheckSeparation(VelBInA.Y(), BCenterInA.Y(), BExtentsXInA.Y(), BExtentsYInA.Y(), ExtentsA.Y(), CenterA.Y(), tEnd, tcloseY, topenY);
				}
				o_latestTClose = tcloseX > tcloseY ? tcloseX : tcloseY;
				o_earliestTOpen = topenX < topenY ? topenX : topenY;
				if (o_latestTClose == tcloseX) {
					o_collisionNormal = AtoWorld * Math::Vector4(1.0f, 0.0f, 0.0f, 0.0f);
				}
				else if (o_latestTClose == tcloseY) {
					o_collisionNormal = AtoWorld * Math::Vector4(0.0f, 1.0f, 0.0f, 0.0f);
				}
				return !isSeparatedOnX && !isSeparatedOnY;
			}

			bool CheckCollision(GameObject::GameObject* objectA, GameObject::GameObject* objectB, float deltaTime, float& o_collisionTime, Math::Vector4& o_collisionNormal) {
				bool result = false;
				float latestTCloseAB = 0.0f;
				float earliestTOpenAB = 0.0f;
				float latestTCloseBA = 0.0f;
				float earliestTOpenBA = 0.0f;
				Math::Vector4 collisionNormalAB;
				Math::Vector4 collisionNormalBA;
				result = TestCollisionOfBInA(objectA, objectB, deltaTime, latestTCloseAB, earliestTOpenAB, collisionNormalAB);
				if (result) {
					result = TestCollisionOfBInA(objectB, objectA, deltaTime, latestTCloseBA, earliestTOpenBA, collisionNormalBA);
					if (result) {
						float latestClose = latestTCloseAB > latestTCloseBA ? latestTCloseAB : latestTCloseBA;
						float earliestOpen = earliestTOpenAB > earliestTOpenBA ? earliestTOpenAB : earliestTOpenBA;
						if (latestClose == latestTCloseAB) {
							o_collisionNormal = collisionNormalAB;
						}
						else if (latestClose == latestTCloseBA) {
							o_collisionNormal = collisionNormalBA;
						}
						result = latestClose < earliestOpen;
						if (result) {
							o_collisionTime = latestClose;
						}
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
									//DEBUG_LOG("Collision!\n");
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