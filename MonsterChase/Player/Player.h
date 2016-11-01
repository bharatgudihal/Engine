#ifndef PLAYER_H
#define PLAYER_H
#include "Actor\Actor.h"
#include "Math\Vector2D.h"

class MonsterChase;

class Player:public Engine::Actor {
	public:
		Player(char *i_name, Engine::Vector2D i_position) :Actor(i_name, i_position) {};
		void Update(const char c, const MonsterChase* monsterChase);
};
#endif // !PLAYER_H
