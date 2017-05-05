#include "../DeathBoxController.h"
#include "Messaging\MessagingSystem.h"
#include "GameObject\GameObject.h"

bool DeathBoxController::OnCollisionEnter(const Engine::Math::Vector3 & collisionNormal, Engine::GameObject::GameObject * other)
{
	if ((*(other->GetActorReference()))->GetNameHash() == "Ball") {
		Engine::Messaging::MessagingSystem::GetInstance()->SendMessageToHandler("GameLost");
	}
	return false;
}
