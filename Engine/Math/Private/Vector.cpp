#include "..\Vector.h"
#include <conio.h>
#include <stdio.h>
namespace Engine {

	const Vector Vector::ZERO(0.0f, 0.0f);
	const Vector Vector::UP(0.0f, 1.0f);
	const Vector Vector::DOWN(0.0f, -1.0f);
	const Vector Vector::LEFT(-1.0f, 0.0f);
	const Vector Vector::RIGHT(1.0f, 0.0f);

	void Vector::Normalize() {
		float magnitude = Magnitude();
		if (magnitude != 0) {
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
	}
}