#include "..\Vector2D.h"
#include <conio.h>
#include <stdio.h>
namespace Engine {

	const Vector2D Vector2D::ZERO(0.0f, 0.0f);
	const Vector2D Vector2D::UP(0.0f, 1.0f);
	const Vector2D Vector2D::DOWN(0.0f, -1.0f);
	const Vector2D Vector2D::LEFT(-1.0f, 0.0f);
	const Vector2D Vector2D::RIGHT(1.0f, 0.0f);

	void Vector2D::Normalize() {
		float magnitude = Magnitude();
		if (magnitude != 0) {
			x /= magnitude;
			y /= magnitude;
		}
	}
}