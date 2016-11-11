#include "..\Vector2D.h"
#include <conio.h>
#include <stdio.h>
namespace Engine {
	Vector2D::Vector2D(const float iX, const float iY) :x(iX), y(iY) {};

	void Vector2D::Normalize() {
		float magnitude = Magnitude();
		x /= magnitude;
		y /= magnitude;
	}
}