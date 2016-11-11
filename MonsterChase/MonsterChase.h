#ifndef MONSTERCHASE_H
#define MONSTERCHASE_H

#include "Math\Vector2D.h"
#include "Monster\MonsterController.h"
#include "Monster\TrackingMonsterController.h"
#include "Player\PlayerController.h"

class Actor;

class MonsterChase{
	public:
		const int GRIDSIZE = 64;
		const Engine::Vector2D MONSTER_SPEED_X = Engine::Vector2D(3, 0);
		const Engine::Vector2D MONSTER_SPEED_Y = Engine::Vector2D(0, 3);
		const Engine::Vector2D PLAYER_SPEED_X = Engine::Vector2D(1, 0);
		const Engine::Vector2D PLAYER_SPEED_Y = Engine::Vector2D(0, 1);
		MonsterChase() {};
		void UpdateMonsterLocation(Engine::Actor* monsterArray, const int count, const Engine::Actor* player);
		void CheckMonsterToMonsterCollision(const Engine::Actor* monsterArray, const int monsterCount) const;
		bool CheckPlayerToMonsterCollision(const Engine::Actor* player, const Engine::Actor* monsterArray, const int monsterCount) const;
	private:
		MonsterController monsterController;
		PlayerController playerController;
		TrackingMonsterController trackingMonsterController;
};
#endif // !MONSTERCHASE_H
