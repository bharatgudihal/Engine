#include "../BallController.h"
#include "GameObject\GameObject.h"

BallController::BallController(Engine::GameObject::GameObject* actorReference) :ballReference(actorReference), defaultForce(actorReference->GetPhysicsBody()->GetSpeed()) {
}

void BallController::Update(float deltaTime) {
	if (!isFree) {		
		Engine::Math::Vector3 direction = Engine::Math::Vector3::ZERO;
		if (Engine::Input::isDown) {
			if (Engine::Input::keyCode == 65 && (*ballReference->GetActorReference())->GetPosition().X() > -350) {
				direction += Engine::Math::Vector3::LEFT;
			}
			if (Engine::Input::keyCode == 68 && (*ballReference->GetActorReference())->GetPosition().X() < 350) {
				direction += Engine::Math::Vector3::RIGHT;
			}
			if (Engine::Input::keyCode == 32) {
				direction = Engine::Math::Vector3(1.0f, 1.0f);
				isFree = true;
			}
		}
		(*ballReference->GetActorReference())->SetForward(direction);
	}
}

bool BallController::OnCollisionEnter(const Engine::Math::Vector3& collisionNormal, Engine::GameObject::GameObject* other) {
	return !isFree;
}