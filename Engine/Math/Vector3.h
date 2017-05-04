#ifndef VECTOR_H
#define VECTOR_H
#include <assert.h>
#include <math.h>
#include "FloatCheck.h"

namespace Engine {
	namespace Math {
		class Vector3
		{
		public:
			inline Vector3(const float iX = 0.0f, const float iY = 0.0f, const float iZ = 0.0f);
			inline Vector3(const Vector3& other);
			inline float X() const;
			inline void X(const float iX);
			inline float Y() const;
			inline void Y(const float iY);
			inline float Z() const;
			inline void Z(const float iZ);
			inline Vector3& operator+=(const Vector3& rhs);
			inline Vector3& operator-=(const Vector3& rhs);
			inline Vector3& operator=(const Vector3& rhs);
			inline float SquareMagnitude() const;
			inline float Magnitude() const;
			void Normalize();
			static const Vector3 ZERO;
			static const Vector3 UP;
			static const Vector3 DOWN;
			static const Vector3 LEFT;
			static const Vector3 RIGHT;
		private:
			float x, y, z;
		};
		inline Vector3 operator+(const Vector3&, const Vector3&);
		inline Vector3 operator-(const Vector3&, const Vector3&);
		inline bool operator==(const Vector3&, const Vector3&);
		inline Vector3 operator*(const Vector3&, const float&);
		inline Vector3 operator/(const Vector3&, const float&);
		inline Vector3 operator-(const Vector3& rhs);
		inline Vector3 operator*(const Vector3&, const Vector3&);
		inline float dot(const Vector3&, const Vector3&);
		Vector3 cross(const Vector3&, const Vector3&);
		struct AABB {
			Vector3 Center;
			Vector3 Extents;
		};
	}
}
#include "Vector3_Inl.h"
#endif // !VECTOR_H
