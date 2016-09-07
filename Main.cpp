

#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
using namespace std;

class Monster {
public:
	char *Name;
	int X;
	int Y;
};

const int GRIDSIZE = 64;
const int MONSTERSPEED = 3;

bool CheckInput(char c) {
	if (c != 'A' && c != 'a' && c != 'W' && c != 'w' && c != 'S' && c != 's' && c != 'D' && c != 'd' && c == 'Q' && c == 'q') {
		printf("\\(O_O)/\n");
		printf("Wrong Input! Read the instructions and try again dummy!\n");
		return false;
	}
	return true;
}

void UpdatePlayer(Monster* player, char c) {
	if (c == 'A', c == 'a') {
		player->X -= 1;
		if (player->X < 0) {
			player->X = 0;
		}
	}
	else if (c == 'D', c == 'd') {
		player->X += 1;
		if (player->X > GRIDSIZE - 1) {
			player->X = GRIDSIZE - 1;
		}
	}
	else if (c == 'W' || c == 'w') {
		player->Y += 1;
		if (player->Y > GRIDSIZE - 1) {
			player->Y = GRIDSIZE - 1;
		}
	}
	else {
		player->Y -= 1;
		if (player->Y < 0) {
			player->Y = 0;
		}
	}
}

void UpdateMonsterLocation(Monster* monsterArray, int count) {
	for (int i = 0; i < count; i++) {
		if (rand() % 2 + 1 == 1) {
			//Change x coordinate
			if (rand() % 2 + 1 == 1) {
				// Increase x coordinate
				monsterArray[i].X += MONSTERSPEED;
				if (monsterArray[i].X > GRIDSIZE - 1) {
					monsterArray[i].X = GRIDSIZE - 1;
				}
			}
			else {
				// Decrease x coordinate
				monsterArray[i].X -= MONSTERSPEED;
				if (monsterArray[i].X < 0) {
					monsterArray[i].X = 0;
				}
			}
		}
		else {
			//Change y coordinate
			if (rand() % 2 + 1 == 1) {
				// Increase y coordinate
				monsterArray[i].Y += MONSTERSPEED;
				if (monsterArray[i].Y > GRIDSIZE - 1) {
					monsterArray[i].Y = GRIDSIZE - 1;
				}
			}
			else {
				// Decrease y coordinate
				monsterArray[i].Y -= MONSTERSPEED;
				if (monsterArray[i].Y < 0) {
					monsterArray[i].Y = 0;
				}
			}
		}
	}
}

void CheckMonsterToMonsterCollision(Monster* monsterArray, int monsterCount) {
	for (int i = 0; i < monsterCount; i++) {
		for (int j = i + 1; j < monsterCount; j++) {
			if (monsterArray[i].X == monsterArray[j].X && monsterArray[i].Y == monsterArray[j].Y) {
				// If collision spawn another monster
				monsterArray[j].X = rand() % 64;
				monsterArray[j].Y = rand() % 64;
				printf("Collision between monster %s and %s. %s has respawned at a different location.\n", monsterArray[i].Name, monsterArray[j].Name, monsterArray[j].Name);
			}
		}
	}
}

bool CheckPlayerToMonsterCollision(Monster* player, Monster* monsterArray, int monsterCount) {
	for (int i = 0; i < monsterCount; i++) {
		if (player->X == monsterArray[i].X && player->Y == monsterArray[i].Y) {
			printf("Player %s has been caught by monster %s!\n", player->Name, monsterArray[i].Name);
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
		printf("Please enter a valid input: ");
		scanf_s("%d", &monsterCount);
	}
	while (monsterCount > 50) {
		printf("Do you really think you can escape so many monsters?\nTry something smaller: ");
		scanf_s("%d", &monsterCount);
	}
	Monster monsterArray[50];
	for (int i = 0; i < monsterCount; i++) {
		printf("Enter the name of monster %d: ", i);
		char monsterName[20];
		scanf_s("%s", monsterName, 20);
		monsterArray[i].Name = monsterName;
		monsterArray[i].X = rand() % GRIDSIZE;
		monsterArray[i].Y = rand() % GRIDSIZE;
	}
	printf("Enter the player's name: ");
	char playerName[20];
	scanf_s("%s", playerName, 20);
	Monster player;
	player.Name = playerName;
	player.X = 0;
	player.Y = 0;
	bool quitGame = false;
	while (true) {
		for (int i = 0; i < monsterCount; i++) {
			printf("Monster %s at [%d,%d]\n", monsterArray[i].Name, monsterArray[i].X, monsterArray[i].Y);
		}
		printf("Player %s at [%d,%d]\n", player.Name, player.X, player.Y);
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