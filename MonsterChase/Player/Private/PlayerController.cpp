#include "../PlayerController.h"

PlayerController::PlayerController(Engine::Pointer::SmartPointer<Engine::Actor>* smartPointer):playerReference(*smartPointer){}

void PlayerController::Update(float deltaTime) {	
	Engine::Math::Vector3 direction = Engine::Math::Vector3::ZERO;
	if (Engine::Input::isDown) {
		if (Engine::Input::keyCode == 65 && playerReference.Acquire()->GetPosition().X() > -350) {
			direction += Engine::Math::Vector3::LEFT;
		}
		if (Engine::Input::keyCode == 68 && playerReference.Acquire()->GetPosition().X() < 350) {
			direction += Engine::Math::Vector3::RIGHT;
		}
	}
	playerReference.Acquire()->SetForward(direction);
}

bool PlayerController::OnCollisionEnter(const Engine::Math::Vector3& collisionNormal, Engine::GameObject::GameObject* other) {
	DEBUG_LOG("Collision\n");
	return false;
}