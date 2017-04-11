#pragma once
#include <smmintrin.h>
#include "Vector3.h"

namespace Engine {
	namespace Math {
		namespace Opt {

#define IMM8 0x71

			union Vector3 {
			public:
				Vector3(const float i_x = 0.0f, const float i_y = 0.0f, const float i_z = 0.0f) :x(i_x), y(i_y), z(i_z) {}
				Vector3(const __m128 i_vector) :vector(i_vector) {}
				Vector3(const Math::Vector3& i_vector) :x(i_vector.X()), y(i_vector.Y()), z(i_vector.Z()) {}				
				inline float X() const;
				inline float Y() const;
				inline float Z() const;
				inline Vector3& operator=(Math::Vector3& i_vector);
				__m128 vector;
			private:
				struct {
					float x, y, z;
				};
			};

			inline float dot(const Vector3& lhs, const Vector3& rhs) {
				return _mm_cvtss_f32(_mm_dp_ps(lhs.vector, rhs.vector, IMM8));
			}

			inline Vector3 cross(const Vector3& lhs, const Vector3& rhs) {
				return Vector3(_mm_sub_ps(
					_mm_mul_ps(_mm_shuffle_ps(lhs.vector, lhs.vector, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(rhs.vector, rhs.vector, _MM_SHUFFLE(3, 1, 0, 2))),

					_mm_mul_ps(_mm_shuffle_ps(lhs.vector, lhs.vector, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(rhs.vector, rhs.vector, _MM_SHUFFLE(3, 0, 2, 1)))
				));
			}

			inline Vector3 operator*(const Vector3& lhs, const float& rhs) {
				return Vector3(lhs.X()*rhs, lhs.Y()*rhs, lhs.Z()*rhs);
			}

			inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
				return Vector3(lhs.X() - rhs.X(), lhs.Y() - rhs.Y(), lhs.Z() - rhs.Z());
			}
		}
	}
}
#include "Vector3_Opt_Inl.h"