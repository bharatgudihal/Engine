#include "../MonsterController.h"
#include "Actor\Actor.h"
using namespace Engine;

void MonsterController::Update(const char input) {
	Vector2D currentPlayerPosition = monster->getPosition();
	monster->setPosition(currentPlayerPosition + GetRandomDirection());
	if (monster->getPosition().X() > GRIDSIZE) {
		monster->getPosition().X(GRIDSIZE);
	}
	else if (monster->getPosition().X() < GRIDSIZE) {
		monster->getPosition().X(-GRIDSIZE);
	}
	else if (monster->getPosition().Y() > GRIDSIZE) {
		monster->getPosition().Y(GRIDSIZE);
	}
	else if (monster->getPosition().Y() < GRIDSIZE) {
		monster->getPosition().Y(-GRIDSIZE);
	}
}