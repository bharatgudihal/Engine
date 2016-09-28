#include "MonsterChase.h"
#include "Monster\Monster.h"
#include "stdio.h"
#include "stdlib.h"
#include "Math\Vector2D.h"
#include "Player\Player.h"

void MonsterChase::UpdateMonsterLocation(Monster* monsterArray, int count) {
	for (int i = 0; i < count; i++) {
		monsterArray[i].Update(this);
	}
}

void MonsterChase::CheckMonsterToMonsterCollision(Monster* monsterArray, int monsterCount) {
	for (int i = 0; i < monsterCount; i++) {
		for (int j = i + 1; j < monsterCount; j++) {
			if (monsterArray[i].getPosition() == monsterArray[j].getPosition()) {
				// If collision spawn another monster
				monsterArray[j].getPosition() = Engine::Vector2D(static_cast<float>(rand() % 64), static_cast<float>(rand() % 64));
				printf("Collision between monster %s and %s. %s has respawned at a different location.\n", monsterArray[i].getName(), monsterArray[j].getName(), monsterArray[j].getName());
			}
		}
	}
}

bool MonsterChase::CheckPlayerToMonsterCollision(Player* player, Monster* monsterArray, int monsterCount) {
	for (int i = 0; i < monsterCount; i++) {
		if (player->getPosition() == monsterArray[i].getPosition()) {
			printf("Player %s has been caught by monster %s!\n", player->getName(), monsterArray[i].getName());
			return true;
		}
	}
	return false;
}