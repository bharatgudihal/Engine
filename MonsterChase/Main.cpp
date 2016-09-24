#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "Actor\Monster.h"
#include "Math\Vector2D.h"
#include <assert.h>
#include "Logger\Logger.h"
using namespace std;
using namespace Engine;

const int GRIDSIZE = 64;
const Vector2D MONSTER_SPEED_X = Vector2D(3, 0);
const Vector2D MONSTER_SPEED_Y = Vector2D(0, 3);
const Vector2D PLAYER_SPEED_X = Vector2D(1, 0);
const Vector2D PLAYER_SPEED_Y = Vector2D(0, 1);

bool CheckInput(char c) {
	if (c != 'A' && c != 'a' && c != 'W' && c != 'w' && c != 'S' && c != 's' && c != 'D' && c != 'd' && c == 'Q' && c == 'q') {
		DebugLog("input entered %c ", c);
		printf("\\(O_O)/\n");
		printf("Wrong Input! Read the instructions and try again dummy!\n");
		return false;
	}
	return true;
}

void UpdatePlayer(Monster* player, char c) {
	assert(player != NULL);
	Vector2D currentPlayerPosition = player->getPosition();
	if (c == 'A', c == 'a') {
		currentPlayerPosition -= PLAYER_SPEED_X;
		if (currentPlayerPosition.getX() < 0) {
			currentPlayerPosition.setX(0);
		}
	}
	else if (c == 'D', c == 'd') {
		currentPlayerPosition += PLAYER_SPEED_X;
		if (currentPlayerPosition.getX() > GRIDSIZE - 1) {
			currentPlayerPosition.setX(GRIDSIZE - 1);
		}
	}
	else if (c == 'W' || c == 'w') {
		currentPlayerPosition += PLAYER_SPEED_Y;
		if (currentPlayerPosition.getY() > GRIDSIZE - 1) {
			currentPlayerPosition.setY(GRIDSIZE - 1);
		}
	}
	else {
		currentPlayerPosition -= PLAYER_SPEED_Y;
		if (currentPlayerPosition.getY() < 0) {
			currentPlayerPosition.setY(0);
		}
	}
	player->setPosition(currentPlayerPosition);
}

void UpdateMonsterLocation(Monster* monsterArray, int count) {
	assert(monsterArray != NULL);
	for (int i = 0; i < count; i++) {
		Vector2D currentMonsterPosition = monsterArray[i].getPosition();
		if (rand() % 2 + 1 == 1) {
			//Change x coordinate
			if (rand() % 2 + 1 == 1) {
				// Increase x coordinate
				currentMonsterPosition += MONSTER_SPEED_X;
				if (currentMonsterPosition.getX() > GRIDSIZE - 1) {
					currentMonsterPosition.setX(GRIDSIZE - 1);
				}
			}
			else {
				// Decrease x coordinate
				currentMonsterPosition -= MONSTER_SPEED_X;
				if (currentMonsterPosition.getX() < 0) {
					currentMonsterPosition.setX(0);
				}
			}
		}
		else {
			//Change y coordinate
			if (rand() % 2 + 1 == 1) {
				// Increase y coordinate
				currentMonsterPosition += MONSTER_SPEED_Y;
				if (currentMonsterPosition.getY() > GRIDSIZE - 1) {
					currentMonsterPosition.setY(GRIDSIZE - 1);
				}
			}
			else {
				// Decrease y coordinate
				currentMonsterPosition -= MONSTER_SPEED_Y;
				if (currentMonsterPosition.getY() < 0) {
					currentMonsterPosition.setY(0);
				}
			}
		}
		monsterArray[i].setPosition(currentMonsterPosition);
	}
}

void CheckMonsterToMonsterCollision(Monster* monsterArray, int monsterCount) {
	assert(monsterArray != NULL);
	for (int i = 0; i < monsterCount; i++) {
		for (int j = i + 1; j < monsterCount; j++) {
			if (monsterArray[i].getPosition() == monsterArray[j].getPosition()) {
				// If collision spawn another monster
				DebugLog("Collision position [%f,%f] ", monsterArray[i].getPosition().getX(), monsterArray[i].getPosition().getY());
				monsterArray[j].getPosition() = Vector2D(static_cast<float>(rand() % 64), static_cast<float>(rand() % 64));
				printf("Collision between monster %s and %s. %s has respawned at a different location.\n", monsterArray[i].getName(), monsterArray[j].getName(), monsterArray[j].getName());
			}
		}
	}
}

bool CheckPlayerToMonsterCollision(Monster* player, Monster* monsterArray, int monsterCount) {
	assert(monsterArray != NULL);
	assert(player != NULL);
	for (int i = 0; i < monsterCount; i++) {
		if (player->getPosition() == monsterArray[i].getPosition()) {
			DebugLog("Collision position [%f,%f] ", player->getPosition().getX(), player->getPosition().getY());
			printf("Player %s has been caught by monster %s!\n", player->getName(), monsterArray[i].getName());
			return true;
		}
	}
	return false;
}

int main() {
	printf("Please enter the number of monsters you want to start with: ");
	int monsterCount;
	scanf_s("%d", &monsterCount);
	while (monsterCount < 1) {
		DebugLog("monsterCount entered %d ",monsterCount);
		printf("Please enter a valid input: ");
		scanf_s("%d", &monsterCount);
	}
	while (monsterCount > 50) {
		DebugLog("monsterCount entered %d ", monsterCount);
		printf("Do you really think you can escape so many monsters?\nTry something smaller: ");
		scanf_s("%d", &monsterCount);
	}
	Monster monsterArray[50];
	for (int i = 0; i < monsterCount; i++) {
		printf("Enter the name of monster %d: ", i);
		char monsterName[20];
		scanf_s("%s", monsterName, 20);
		monsterArray[i] = Monster(monsterName, Vector2D(static_cast<float>(rand() % GRIDSIZE), static_cast<float>(rand() % GRIDSIZE)));
	}
	printf("Enter the player's name: ");
	char playerName[20];
	scanf_s("%s", playerName, 20);
	Monster player = Monster(playerName,Vector2D(0,0));
	bool quitGame = false;
	while (true) {
		for (int i = 0; i < monsterCount; i++) {
			printf("Monster %s at [%f,%f]\n", monsterArray[i].getName(), monsterArray[i].getPosition().getX(), monsterArray[i].getPosition().getY());
		}
		printf("Player %s at [%f,%f]\n", player.getName(), player.getPosition().getX(), player.getPosition().getY());
		printf("Use the W,A,S,D keys to move. Press Q to quit.\n");
		char c;
		c = _getch();
		while (!CheckInput(c)) {
			c = _getch();
		}
		if (c == 'Q' || c == 'q') {
			break;
		}
		UpdatePlayer(&player, c);
		UpdateMonsterLocation(monsterArray, monsterCount);
		CheckMonsterToMonsterCollision(monsterArray, monsterCount);
		if (CheckPlayerToMonsterCollision(&player, monsterArray, monsterCount)) {
			printf("Press any button to exit.");
			_getch();
			break;
		}
	}
	return 0;
}