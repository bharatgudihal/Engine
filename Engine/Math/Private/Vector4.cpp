#include "../Vector4.h"
namespace Engine {
	namespace Math {

		const Vector4 Vector4::ZERO;
		const Vector4 Vector4::UP(0.0f,1.0f);
		const Vector4 Vector4::DOWN(0.0f, -1.0f);
		const Vector4 Vector4::LEFT(-1.0f, 0.0f);
		const Vector4 Vector4::RIGHT(1.0f, 0.0f);

		void Vector4::Normalize() {
			float magnitude = Magnitude();
			if (magnitude != 0) {
				x /= magnitude;
				y /= magnitude;
				z /= magnitude;
			}
		}

	}
}