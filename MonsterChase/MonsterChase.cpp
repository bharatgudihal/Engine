#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Math\Vector2D.h"
#include "Player\Player.h"
#include "Logger\Logger.h"
#include "MonsterChase.h"
#include "Monster\Monster.h"
#include "Actor\Actor.h"

void MonsterChase::UpdateMonsterLocation(Engine::Actor* monsterArray, const int count, const Engine::Actor* player) {
	assert(monsterArray != NULL);
	for (int i = 0; i < count; i++) {
		if (i % 2 == 0) {
			trackingMonsterController.SetActor(&monsterArray[i]);
			trackingMonsterController.SetDirection(player);
			trackingMonsterController.Update(NULL);
		}
		else {
			monsterController.SetActor(&monsterArray[i]);
			monsterController.Update(NULL);
		}
	}
}

void MonsterChase::CheckMonsterToMonsterCollision(const Engine::Actor* monsterArray, const int monsterCount) const {
	int gridSize = 64;
	for (int i = 0; i < monsterCount; i++) {
		for (int j = i + 1; j < monsterCount; j++) {
			if (monsterArray[i].getPosition() == monsterArray[j].getPosition()) {
				// If collision spawn another monster
				DEBUG_LOG("Collision position [%f,%f] ", monsterArray[i].getPosition().X(), monsterArray[i].getPosition().Y());
				monsterArray[j].getPosition() = Engine::Vector2D(static_cast<float>(rand() % gridSize), static_cast<float>(rand() % gridSize));
				printf("Collision between monster %s and %s. %s has respawned at a different location.\n", monsterArray[i].getName(), monsterArray[j].getName(), monsterArray[j].getName());
			}
		}
	}
}

bool MonsterChase::CheckPlayerToMonsterCollision(const Engine::Actor* player, const Engine::Actor* monsterArray, const int monsterCount) const {
	for (int i = 0; i < monsterCount; i++) {
		if (player->getPosition() == monsterArray[i].getPosition()) {
			DEBUG_LOG("Collision position [%f,%f] ", player->getPosition().X(), player->getPosition().Y());
			printf("Player %s has been caught by monster %s!\n", player->getName(), monsterArray[i].getName());
			return true;
		}
	}
	return false;
}