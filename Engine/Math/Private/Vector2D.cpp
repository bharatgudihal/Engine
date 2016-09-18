#include "..\Vector2D.h"
#include "conio.h"
#include "stdio.h"

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