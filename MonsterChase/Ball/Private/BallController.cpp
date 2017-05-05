#include <time.h>
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
			srand(static_cast<unsigned int>(time(NULL)));
			if (Engine::Input::keyCode == 32) {
				float randomX = 1.0f + rand() % 1;
				float randomY = 2.0f - randomX;
				direction = Engine::Math::Vector3(randomX, randomY);
				float speed = ballReference->GetPhysicsBody()->GetSpeed();
				ballReference->GetPhysicsBody()->SetSpeed(speed);
				isFree = true;
			}
		}
		(*ballReference->GetActorReference())->SetForward(direction);
	}
}

bool BallController::OnCollisionEnter(const Engine::Math::Vector3& collisionNormal, Engine::GameObject::GameObject* other) {
	return !isFree;
}