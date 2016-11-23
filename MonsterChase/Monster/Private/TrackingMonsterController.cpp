#include "..\TrackingMonsterController.h"

void TrackingMonsterController::SetDirection(const Engine::Actor* player) {
	Engine::Vector2D directionVector = player->getPosition() - monster->getPosition();
	directionVector.Normalize();
	monster->setDirection(directionVector);
}