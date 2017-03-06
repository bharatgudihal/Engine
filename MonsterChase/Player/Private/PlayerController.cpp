#include "../PlayerController.h"

PlayerController::PlayerController(Engine::Pointer::SmartPointer<Engine::Actor>* smartPointer):playerReference(*smartPointer){}

void PlayerController::Update() {	
	Engine::Vector direction = Engine::Vector::ZERO;
	if (Engine::Input::isDown) {
		if (Engine::Input::keyCode == 65) {
			direction += Engine::Vector::LEFT;
		}
		if (Engine::Input::keyCode == 68) {
			direction += Engine::Vector::RIGHT;
		}
		if (Engine::Input::keyCode == 83) {
			direction += Engine::Vector::DOWN;
		}
		if (Engine::Input::keyCode == 87) {
			direction += Engine::Vector::UP;
		}
	}
	playerReference.Acquire()->setDirection(direction);
}