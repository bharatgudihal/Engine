#include "..\Vector2D.h"
#include "conio.h"
#include "stdio.h"
namespace Engine {

	Vector2D::Vector2D(const float iX, const float iY) :x(iX), y(iY) {};

	float Vector2D::getX()const { return x; }

	void Vector2D::setX(const float iX) { x = iX; }

	float Vector2D::getY() const { return y; }

	void Vector2D::setY(const float iY) { y = iY; }

	Vector2D operator+(const Vector2D& lhs_vector, const Vector2D& rhs_vector) {
		return Vector2D(lhs_vector.getX() + rhs_vector.getX(), lhs_vector.getY() + rhs_vector.getY());
	}
	Vector2D operator-(const Vector2D& lhs_vector, const Vector2D& rhs_vector) {
		return Vector2D(lhs_vector.getX() - rhs_vector.getX(), lhs_vector.getY() - rhs_vector.getY());
	}
	bool operator==(const Vector2D& rhs, const Vector2D& lhs) {
		return rhs.getX() == lhs.getX() && rhs.getY() == lhs.getY();
	}
	Vector2D& Vector2D::operator+=(const Vector2D& rhs) {
		*this = *this + rhs;
		return *this;
	}
	Vector2D& Vector2D::operator-=(const Vector2D& rhs) {
		*this = *this - rhs;
		return *this;
	}
}