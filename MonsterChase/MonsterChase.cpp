#include "MonsterChase.h"

void MonsterChase::UpdateMonsterLocation(std::vector<Engine::Actor>* monsterArray, const int count, const Engine::Actor* player) {
	assert(monsterArray != NULL);
	for (int i = 0; i < count; i++) {
		if (i % 2 == 0) {
			trackingMonsterController.SetActor(&monsterArray->at(i));
			trackingMonsterController.SetDirection(player);
			trackingMonsterController.Update(NULL);
		}
		else {
			monsterController.SetActor(&monsterArray->at(i));
			monsterController.Update(NULL);
		}
	}
}

void MonsterChase::CheckMonsterToMonsterCollision(const std::vector<Engine::Actor>* monsterArray, const int monsterCount) const {
	int gridSize = 64;
	for (int i = 0; i < monsterCount; i++) {
		for (int j = i + 1; j < monsterCount; j++) {
			if (monsterArray->at(i).getPosition() == monsterArray->at(j).getPosition()) {
				// If collision spawn another monster
				DEBUG_LOG("Collision position [%f,%f] ", monsterArray->at(i).getPosition().X(), monsterArray->at(i).getPosition().Y());
				monsterArray->at(j).getPosition() = Engine::Vector2D(static_cast<float>(rand() % gridSize), static_cast<float>(rand() % gridSize));
				printf("Collision between monster %s and %s. %s has respawned at a different location.\n", monsterArray->at(i).getName(), monsterArray->at(j).getName(), monsterArray->at(j).getName());
			}
		}
	}
}

bool MonsterChase::CheckPlayerToMonsterCollision(const Engine::Actor* player, const std::vector<Engine::Actor>* monsterArray, const int monsterCount) const {
	for (int i = 0; i < monsterCount; i++) {
		if (player->getPosition() == monsterArray->at(i).getPosition()) {
			DEBUG_LOG("Collision position [%f,%f] ", player->getPosition().X(), player->getPosition().Y());
			printf("Player %s has been caught by monster %s!\n", player->getName(), monsterArray->at(i).getName());
			return true;
		}
	}
	return false;
}