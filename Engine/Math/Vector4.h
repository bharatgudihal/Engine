#pragma once
#include <assert.h>
#include <math.h>
#include "FloatCheck.h"
#include "Vector3.h"
namespace Engine {
	namespace Math {

		class Vector4
		{
		public:
			inline Vector4(const float iX = 0.0f, const float iY = 0.0f, const float iZ = 0.0f, const float iW = 1.0f);
			inline Vector4(const Vector4& other);
			inline Vector4(const Vector3& other, const float i_w);
			inline float X() const;
			inline void X(const float iX);
			inline float Y() const;
			inline void Y(const float iY);
			inline float Z() const;
			inline void Z(const float iZ);
			inline float W() const;
			inline void W(const float iW);
			inline Vector4& operator+=(const Vector4& rhs);
			inline Vector4& operator-=(const Vector4& rhs);
			inline Vector4& operator=(const Vector4& rhs);
			inline float Magnitude() const;
			void Normalize();
			static const Vector4 ZERO;
			static const Vector4 UP;
			static const Vector4 DOWN;
			static const Vector4 LEFT;
			static const Vector4 RIGHT;
			inline Vector3 GetVector3();
		private:
			float x, y, z, w;
		};
		inline Vector4 operator+(const Vector4&, const Vector4&);
		inline Vector4 operator-(const Vector4&, const Vector4&);
		inline bool operator==(const Vector4&, const Vector4&);
		inline Vector4 operator*(const Vector4&, const float&);
		inline Vector4 operator/(const Vector4&, const float&);
		inline Vector4 operator-(const Vector4& rhs);
		inline Vector4 operator*(const Vector4&, const Vector4&);

	}
}
#include "Vector4_Inl.h"