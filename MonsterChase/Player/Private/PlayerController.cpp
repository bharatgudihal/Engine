#include "../PlayerController.h"

PlayerController::PlayerController(Engine::Pointer::SmartPointer<Engine::Actor>* smartPointer):playerReference(*smartPointer){}

void PlayerController::Update() {	
	Engine::Vector2D direction = Engine::Vector2D::ZERO;
	if (Engine::Input::isDown) {
		if (Engine::Input::keyCode == 65) {
			direction += Engine::Vector2D::LEFT;
		}
		if (Engine::Input::keyCode == 68) {
			direction += Engine::Vector2D::RIGHT;
		}
		if (Engine::Input::keyCode == 83) {
			direction += Engine::Vector2D::DOWN;
		}
		if (Engine::Input::keyCode == 87) {
			direction += Engine::Vector2D::UP;
		}
	}
	playerReference.Acquire()->setDirection(direction);
}