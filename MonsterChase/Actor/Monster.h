#ifndef MONSTER_H
#define MONSTER_H
#include "Math\Vector2D.h"

class Monster {
public:
	Monster() {}
	Monster(char *i_name, Engine::Vector2D i_position):name(i_name),position(i_position) {}
	char* getName() { return name; }
	Engine::Vector2D getPosition() { return position; }
	void setPosition(Engine::Vector2D newPosition) { position = newPosition; }
private:
	char *name;
	Engine::Vector2D position = Engine::Vector2D(0,0);
};
#endif
