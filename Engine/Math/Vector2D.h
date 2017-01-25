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
		inline Vector2D(const Vector2D& other);
		inline float X() const;
		inline void X(const float iX);
		inline float Y() const;
		inline void Y(const float iY);
		inline Vector2D& operator+=(const Vector2D& rhs);
		inline Vector2D& operator-=(const Vector2D& rhs);
		inline Vector2D& operator=(const Vector2D& rhs);		
		inline float Magnitude() const;
		void Normalize();
		static const Vector2D ZERO;
		static const Vector2D UP;
		static const Vector2D DOWN;
		static const Vector2D LEFT;
		static const Vector2D RIGHT;
	private:
		float x, y;
	};
	inline Vector2D operator+(const Vector2D&, const Vector2D&);
	inline Vector2D operator-(const Vector2D&, const Vector2D&);
	inline bool operator==(const Vector2D&, const Vector2D&);
	inline Vector2D operator*(const Vector2D&, const float&);
	inline Vector2D operator/(const Vector2D&, const float&);
	inline Vector2D operator-(const Vector2D& rhs);
	inline Vector2D operator*(const Vector2D&, const Vector2D&);
}
#include "Vector2D_Inl.h"
#endif // !VECTOR2D_H
