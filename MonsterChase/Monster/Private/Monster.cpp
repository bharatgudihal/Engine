#include "..\Monster.h"
#include <stdlib.h>
#include "..\..\MonsterChase.h"


void Monster::Update(const MonsterChase* monsterChase) {
	Engine::Vector2D currentMonsterPosition = this->getPosition();
	if (rand() % 2 + 1 == 1) {
		//Change x coordinate
		if (rand() % 2 + 1 == 1) {
			// Increase x coordinate
			currentMonsterPosition += monsterChase->MONSTER_SPEED_X;
			if (currentMonsterPosition.X() > monsterChase->GRIDSIZE - 1) {
				currentMonsterPosition.X((float)(monsterChase->GRIDSIZE - 1));
			}
		}
		else {
			// Decrease x coordinate
			currentMonsterPosition -= monsterChase->MONSTER_SPEED_X;
			if (currentMonsterPosition.X() < 0) {
				currentMonsterPosition.X(0);
			}
		}
	}
	else {
		//Change y coordinate
		if (rand() % 2 + 1 == 1) {
			// Increase y coordinate
			currentMonsterPosition += monsterChase->MONSTER_SPEED_Y;
			if (currentMonsterPosition.Y() > monsterChase->GRIDSIZE - 1) {
				currentMonsterPosition.Y((float)(monsterChase->GRIDSIZE - 1));
			}
		}
		else {
			// Decrease y coordinate
			currentMonsterPosition -= monsterChase->MONSTER_SPEED_Y;
			if (currentMonsterPosition.Y() < 0) {
				currentMonsterPosition.Y(0);
			}
		}
	}
	this->setPosition(currentMonsterPosition);
}