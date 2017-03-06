#ifndef VECTOR_H
#define VECTOR_H
#include <assert.h>
#include <math.h>
#include "FloatCheck.h"
namespace Engine {
	class Vector
	{
	public:		
		inline Vector(const float iX = 0, const float iY = 0, const float iZ = 0, const float iW = 0);
		inline Vector(const Vector& other);
		inline float X() const;
		inline void X(const float iX);
		inline float Y() const;
		inline void Y(const float iY);
		inline float Z() const;
		inline void Z(const float iZ);
		inline Vector& operator+=(const Vector& rhs);
		inline Vector& operator-=(const Vector& rhs);
		inline Vector& operator=(const Vector& rhs);		
		inline float Magnitude() const;
		void Normalize();
		static const Vector ZERO;
		static const Vector UP;
		static const Vector DOWN;
		static const Vector LEFT;
		static const Vector RIGHT;
	private:
		float x, y, z, w;
	};
	inline Vector operator+(const Vector&, const Vector&);
	inline Vector operator-(const Vector&, const Vector&);
	inline bool operator==(const Vector&, const Vector&);
	inline Vector operator*(const Vector&, const float&);
	inline Vector operator/(const Vector&, const float&);
	inline Vector operator-(const Vector& rhs);
	inline Vector operator*(const Vector&, const Vector&);
}
#include "Vector_Inl.h"
#endif // !VECTOR_H
