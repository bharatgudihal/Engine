#ifndef MONSTER_H
#define MONSTER_H
#include "Actor\Actor.h"
#include "Math\Vector2D.h"
#include "..\MonsterChase.h"

class Monster :public Engine::Actor {
	public:
		Monster() {};
		Monster(char *i_name, Engine::Vector2D i_position) :Actor(i_name, i_position) {};
		void Update(const MonsterChase* monsterChase);
};
#endif