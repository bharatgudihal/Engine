#include "../PlayerController.h"

PlayerController::PlayerController(Engine::Pointer::SmartPointer<Engine::Actor>* smartPointer):playerReference(*smartPointer){}

void PlayerController::Update(float deltaTime) {	
	Engine::Math::Vector3 direction = Engine::Math::Vector3::ZERO;
	if (Engine::Input::isDown) {
		if (Engine::Input::keyCode == 65) {
			direction += Engine::Math::Vector3::LEFT;
		}
		if (Engine::Input::keyCode == 68) {
			direction += Engine::Math::Vector3::RIGHT;
		}
		if (Engine::Input::keyCode == 83) {
			direction += Engine::Math::Vector3::DOWN;
		}
		if (Engine::Input::keyCode == 87) {
			direction += Engine::Math::Vector3::UP;
		}
	}
	playerReference.Acquire()->setDirection(direction);
}