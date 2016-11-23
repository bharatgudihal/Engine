#ifndef POINT2D_H
#define POINT2D_H
#include <assert.h>
#include <math.h>
#include "FloatCheck.h"
namespace Engine {
	class Vector2D
	{
	public:
		Vector2D() {};
		inline Vector2D(const float iX, const float iY);
		inline float X() const;
		inline void X(const float iX);
		inline float Y() const;
		inline void Y(const float iY);
		inline Vector2D& operator+=(const Vector2D&);
		inline Vector2D& operator-=(const Vector2D&);
		inline float Magnitude() const;
		void Normalize();
		static const Vector2D ZERO;
	private:
		float x, y;
	};
	inline Vector2D operator+(const Vector2D&, const Vector2D&);
	inline Vector2D operator-(const Vector2D&, const Vector2D&);
	inline bool operator==(const Vector2D&, const Vector2D&);
	inline Vector2D operator*(const Vector2D&, const float&);
}
#include "Vector2D_Inl.h"
#endif // !VECTOR2D_H
