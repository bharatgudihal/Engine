#include "../DeathBoxController.h"
#include "Messaging\MessagingSystem.h"

bool DeathBoxController::OnCollisionEnter(const Engine::Math::Vector3 &, Engine::GameObject::GameObject *)
{
	Engine::Messaging::MessagingSystem::GetInstance()->SendMessageToHandler("GameLost");
	return false;
}
