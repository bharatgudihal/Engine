#include "../HardBrickController.h"
#include "GameObject\GameObject.h"
#include "Messaging\MessagingSystem.h"

HardBrickController::HardBrickController(Engine::GameObject::GameObject* actorReference) :brickReference(actorReference), hitCount(0), maxHitCount(2){}

void HardBrickController::Update(float deltaTime) {}

bool HardBrickController::OnCollisionEnter(const Engine::Math::Vector3& collisionNormal, Engine::GameObject::GameObject* other) {
	if (brickReference->GetEnabled() && (*(other->GetActorReference()))->GetNameHash() == "Ball") {
		if (++hitCount == maxHitCount) {
			Engine::Messaging::MessagingSystem::GetInstance()->SendMessageToHandler("BrickDestroyed");
			brickReference->SetEnabled(false);
			hitCount = 0;
		}
	}
	return false;
}