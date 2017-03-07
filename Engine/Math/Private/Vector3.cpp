#include "..\Vector3.h"
#include <conio.h>
#include <stdio.h>
namespace Engine {
	namespace Math {

		const Vector3 Vector3::ZERO(0.0f, 0.0f);
		const Vector3 Vector3::UP(0.0f, 1.0f);
		const Vector3 Vector3::DOWN(0.0f, -1.0f);
		const Vector3 Vector3::LEFT(-1.0f, 0.0f);
		const Vector3 Vector3::RIGHT(1.0f, 0.0f);

		void Vector3::Normalize() {
			float magnitude = Magnitude();
			if (magnitude != 0) {
				x /= magnitude;
				y /= magnitude;
				z /= magnitude;
			}
		}
	}
}