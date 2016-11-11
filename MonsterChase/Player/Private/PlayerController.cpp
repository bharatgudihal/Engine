#include "../PlayerController.h"

void PlayerController::Update(const char input) {
	Engine::Vector2D currentPlayerPosition = player->getPosition();
	if (input == 'A' || input == 'a') {
		currentPlayerPosition -= PLAYER_SPEED_X;
		if (currentPlayerPosition.X() < -GRIDSIZE) {
			currentPlayerPosition.X(-GRIDSIZE);
		}
	}
	else if (input == 'D' || input == 'd') {
		currentPlayerPosition += PLAYER_SPEED_X;		
		if (currentPlayerPosition.X() > GRIDSIZE) {
			currentPlayerPosition.X(GRIDSIZE);
		}
	}
	else if (input == 'W' || input == 'w') {
		currentPlayerPosition += PLAYER_SPEED_Y;
		if (currentPlayerPosition.Y() > GRIDSIZE) {
			currentPlayerPosition.Y(GRIDSIZE);
		}
	}
	else {
		currentPlayerPosition -= PLAYER_SPEED_Y;
		if (currentPlayerPosition.Y() < -GRIDSIZE) {
			currentPlayerPosition.Y(-GRIDSIZE);
		}
	}
	player->setPosition(currentPlayerPosition);
}