#include "..\Player.h"
#include "..\..\MonsterChase.h"

void Player::Update(char c,MonsterChase* monsterChase) {
	Engine::Vector2D currentPlayerPosition = this->getPosition();
	if (c == 'A', c == 'a') {
		currentPlayerPosition -= monsterChase->PLAYER_SPEED_X;
		if (currentPlayerPosition.X() < 0) {
			currentPlayerPosition.X(0);
		}
	}
	else if (c == 'D', c == 'd') {
		currentPlayerPosition += monsterChase->PLAYER_SPEED_X;
		if (currentPlayerPosition.X() > monsterChase->GRIDSIZE - 1) {
			currentPlayerPosition.X((float)(monsterChase->GRIDSIZE - 1));
		}
	}
	else if (c == 'W' || c == 'w') {
		currentPlayerPosition += monsterChase->PLAYER_SPEED_Y;
		if (currentPlayerPosition.Y() > monsterChase->GRIDSIZE - 1) {
			currentPlayerPosition.Y((float)(monsterChase->GRIDSIZE - 1));
		}
	}
	else {
		currentPlayerPosition -= monsterChase->PLAYER_SPEED_Y;
		if (currentPlayerPosition.Y() < 0) {
			currentPlayerPosition.Y(0);
		}
	}
	this->setPosition(currentPlayerPosition);
}