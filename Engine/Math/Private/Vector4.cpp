#include "../Vector4.h"
namespace Engine {
	namespace Math {

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