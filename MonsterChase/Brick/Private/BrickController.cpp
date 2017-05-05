#include "../BrickController.h"
#include "GameObject\GameObject.h"
#include "Messaging\MessagingSystem.h"

BrickController::BrickController(Engine::GameObject::GameObject* actorReference):brickReference(actorReference){}

void BrickController::Update(float deltaTime) {}

bool BrickController::OnCollisionEnter(const Engine::Math::Vector3& collisionNormal, Engine::GameObject::GameObject* other) {
	if (brickReference->GetEnabled() && (*(other->GetActorReference()))->GetNameHash() == "Ball") {
		Engine::Messaging::MessagingSystem::GetInstance()->SendMessageToHandler("BrickDestroyed");
		brickReference->SetEnabled(false);
	}
	return false;
}