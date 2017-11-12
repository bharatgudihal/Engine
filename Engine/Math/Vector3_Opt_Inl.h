#pragma once

namespace Engine {
	namespace Math {
		namespace Opt {
			inline float Vector3::X() const { return x; }
			inline float Vector3::Y() const { return y; }
			inline float Vector3::Z() const { return z; }
			inline Vector3& Vector3::operator=(Math::Vector3& i_vector) {
				x = i_vector.X();
				y = i_vector.Y();
				z = i_vector.Z();
				return *this;
			}
		}
	}
}