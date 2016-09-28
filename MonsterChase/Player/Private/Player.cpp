#include "..\Player.h"
#include "..\..\MonsterChase.h"

void Player::Update(char c,MonsterChase* monsterChase) {
	Engine::Vector2D currentPlayerPosition = this->getPosition();
	if (c == 'A', c == 'a') {
		currentPlayerPosition -= monsterChase->PLAYER_SPEED_X;
		if (currentPlayerPosition.getX() < 0) {
			currentPlayerPosition.setX(0);
		}
	}
	else if (c == 'D', c == 'd') {
		currentPlayerPosition += monsterChase->PLAYER_SPEED_X;
		if (currentPlayerPosition.getX() > monsterChase->GRIDSIZE - 1) {
			currentPlayerPosition.setX((float)(monsterChase->GRIDSIZE - 1));
		}
	}
	else if (c == 'W' || c == 'w') {
		currentPlayerPosition += monsterChase->PLAYER_SPEED_Y;
		if (currentPlayerPosition.getY() > monsterChase->GRIDSIZE - 1) {
			currentPlayerPosition.setY((float)(monsterChase->GRIDSIZE - 1));
		}
	}
	else {
		currentPlayerPosition -= monsterChase->PLAYER_SPEED_Y;
		if (currentPlayerPosition.getY() < 0) {
			currentPlayerPosition.setY(0);
		}
	}
	this->setPosition(currentPlayerPosition);
}