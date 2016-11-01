#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Math\Vector2D.h"
#include "Player\Player.h"
#include "Logger\Logger.h"
#include "MonsterChase.h"
#include "Monster\Monster.h"

void MonsterChase::UpdateMonsterLocation(Monster* monsterArray, const int count) {
	assert(monsterArray != NULL);
	for (int i = 0; i < count; i++) {
		monsterArray[i].Update(this);
	}
}

void MonsterChase::CheckMonsterToMonsterCollision(const Monster* monsterArray, const int monsterCount) const {
	for (int i = 0; i < monsterCount; i++) {
		for (int j = i + 1; j < monsterCount; j++) {
			if (monsterArray[i].getPosition() == monsterArray[j].getPosition()) {
				// If collision spawn another monster
				DEBUG_LOG("Collision position [%f,%f] ", monsterArray[i].getPosition().X(), monsterArray[i].getPosition().Y());
				monsterArray[j].getPosition() = Engine::Vector2D(static_cast<float>(rand() % 64), static_cast<float>(rand() % 64));
				printf("Collision between monster %s and %s. %s has respawned at a different location.\n", monsterArray[i].getName(), monsterArray[j].getName(), monsterArray[j].getName());
			}
		}
	}
}

bool MonsterChase::CheckPlayerToMonsterCollision(const Player* player, const Monster* monsterArray, const int monsterCount) const {
	for (int i = 0; i < monsterCount; i++) {
		if (player->getPosition() == monsterArray[i].getPosition()) {
			DEBUG_LOG("Collision position [%f,%f] ", player->getPosition().X(), player->getPosition().Y());
			printf("Player %s has been caught by monster %s!\n", player->getName(), monsterArray[i].getName());
			return true;
		}
	}
	return false;
}