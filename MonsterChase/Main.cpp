#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "Player\Player.h"
#include "Math\Vector2D.h"
#include "Monster\Monster.h"
#include "MonsterChase.h"
#include "Logger\Logger.h"
using namespace std;
using namespace Engine;

bool CheckInput(char c) {
	if (c != 'A' && c != 'a' && c != 'W' && c != 'w' && c != 'S' && c != 's' && c != 'D' && c != 'd' && c == 'Q' && c == 'q') {
		DEBUG_LOG("input entered %c ", c);
		printf("\\(O_O)/\n");
		printf("Wrong Input! Read the instructions and try again dummy!\n");
		return false;
	}
	return true;
}

int main() {
	MonsterChase monsterChase;
	printf("Please enter the number of monsters you want to start with: ");
	int monsterCount;
	scanf_s("%d", &monsterCount);
	while (monsterCount < 1) {
		DEBUG_LOG("monsterCount entered %d ",monsterCount);
		printf("Please enter a valid input: ");
		scanf_s("%d", &monsterCount);
	}
	while (monsterCount > 50) {
		DEBUG_LOG("monsterCount entered %d ", monsterCount);
		printf("Do you really think you can escape so many monsters?\nTry something smaller: ");
		scanf_s("%d", &monsterCount);
	}
	Monster monsterArray[50];
	for (int i = 0; i < monsterCount; i++) {
		printf("Enter the name of monster %d: ", i);
		char monsterName[20];
		scanf_s("%s", monsterName, 20);
		monsterArray[i] = Monster(monsterName, Vector2D((float)(rand() % monsterChase.GRIDSIZE), (float)(rand() % monsterChase.GRIDSIZE)));
	}
	printf("Enter the player's name: ");
	char playerName[20];
	scanf_s("%s", playerName, 20);
	Player player = Player(playerName,Vector2D(0,0));
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
		player.Update(c, &monsterChase);
		monsterChase.UpdateMonsterLocation(monsterArray, monsterCount);
		monsterChase.CheckMonsterToMonsterCollision(monsterArray, monsterCount);
		if (monsterChase.CheckPlayerToMonsterCollision(&player, monsterArray, monsterCount)) {
			printf("Press any button to exit.");
			_getch();
			break;
		}
	}
	return 0;
}