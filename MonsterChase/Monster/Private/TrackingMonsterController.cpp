#include "..\TrackingMonsterController.h"

void TrackingMonsterController::SetDirection(const Actor* player) {
	Vector2D directionVector = player->getPosition() - monster->getPosition();
	directionVector.Normalize();
	monster->setDirection(directionVector);
}