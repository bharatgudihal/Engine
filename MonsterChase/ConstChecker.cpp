#include "ConstChecker.h"
#include "Math\Vector2D.h"
using namespace Engine;

bool ConstChecker(){
	const Vector2D vector1(132.5f,151.0f);
	const Vector2D vector2(558.4f, 157.0f);
	float x = vector1.X();
	float y = vector1.Y();
	x = vector2.X();
	y = vector2.Y();	
	Vector2D sum = vector1 + vector2;
	Vector2D diff = vector1 - vector2;
	sum.X(5);
	//Tested
	//vector1(1.0f, 1.0f, 1.0f);
	//vector1 += vector2;
	//vector1 = vector2;
	//vector1 = vector1+vector2;
	return true;
}