#include "..\Vector2D.h"
#include <conio.h>
#include <stdio.h>
namespace Engine {

	const Vector2D Vector2D::ZERO(0.0f, 0.0f);

	void Vector2D::Normalize() {
		float magnitude = Magnitude();
		if (magnitude != 0) {
			x /= magnitude;
			y /= magnitude;
		}
	}
}