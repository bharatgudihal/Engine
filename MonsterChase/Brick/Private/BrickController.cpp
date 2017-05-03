#include "../BrickController.h"
#include "GameObject\GameObject.h"

BrickController::BrickController(Engine::GameObject::GameObject* actorReference):brickReference(actorReference){}

void BrickController::Update(float deltaTime) {}

bool BrickController::OnCollisionEnter(const Engine::Math::Vector3& collisionNormal, Engine::GameObject::GameObject* other) {
	if (!isDisabled) {
		brickReference->SetRenderObject(nullptr);
		isDisabled = true;
	}
	return isDisabled;
}