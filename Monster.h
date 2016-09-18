#ifndef MONSTER_H
#define MONSTER_H
#include "Engine\Vector2D.h"
class Monster {
public:
	Monster() {}
	Monster(char *i_name, Vector2D i_position):name(i_name),position(i_position) {}
	char* getName() { return name; }
	Vector2D getPosition() { return position; }
	void setPosition(Vector2D newPosition) { position = newPosition; }
private:
	char *name;
	Vector2D position = Vector2D(0,0);
};
#endif
