#include "..\Monster.h"
#include <stdlib.h>
#include "..\..\MonsterChase.h"


void Monster::Update(MonsterChase* monsterChase) {
	Engine::Vector2D currentMonsterPosition = this->getPosition();
	if (rand() % 2 + 1 == 1) {
		//Change x coordinate
		if (rand() % 2 + 1 == 1) {
			// Increase x coordinate
			currentMonsterPosition += monsterChase->MONSTER_SPEED_X;
			if (currentMonsterPosition.getX() > monsterChase->GRIDSIZE - 1) {
				currentMonsterPosition.setX((float)(monsterChase->GRIDSIZE - 1));
			}
		}
		else {
			// Decrease x coordinate
			currentMonsterPosition -= monsterChase->MONSTER_SPEED_X;
			if (currentMonsterPosition.getX() < 0) {
				currentMonsterPosition.setX(0);
			}
		}
	}
	else {
		//Change y coordinate
		if (rand() % 2 + 1 == 1) {
			// Increase y coordinate
			currentMonsterPosition += monsterChase->MONSTER_SPEED_Y;
			if (currentMonsterPosition.getY() > monsterChase->GRIDSIZE - 1) {
				currentMonsterPosition.setY((float)(monsterChase->GRIDSIZE - 1));
			}
		}
		else {
			// Decrease y coordinate
			currentMonsterPosition -= monsterChase->MONSTER_SPEED_Y;
			if (currentMonsterPosition.getY() < 0) {
				currentMonsterPosition.setY(0);
			}
		}
	}
	this->setPosition(currentMonsterPosition);
}