#ifndef MONSTERCHASE_H
#define MONSTERCHASE_H

#include "Math\Vector2D.h"

class Player;
class Monster;

class MonsterChase{
	public:
		const int GRIDSIZE = 64;
		const Engine::Vector2D MONSTER_SPEED_X = Engine::Vector2D(3, 0);
		const Engine::Vector2D MONSTER_SPEED_Y = Engine::Vector2D(0, 3);
		const Engine::Vector2D PLAYER_SPEED_X = Engine::Vector2D(1, 0);
		const Engine::Vector2D PLAYER_SPEED_Y = Engine::Vector2D(0, 1);
		MonsterChase() {};
		void UpdateMonsterLocation(Monster* monsterArray, const int count);
		void CheckMonsterToMonsterCollision(const Monster* monsterArray, const int monsterCount) const;
		bool CheckPlayerToMonsterCollision(const Player* player, const Monster* monsterArray, const int monsterCount) const;
};
#endif // !MONSTERCHASE_H
