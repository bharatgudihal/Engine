namespace Engine {
	inline float Vector2D::X() const { return x; }

	inline void Vector2D::X(const float iX) { x = iX; }

	inline float Vector2D::Y() const { return y; }

	inline void Vector2D::Y(const float iY) { y = iY; }

	inline Vector2D operator+(const Vector2D& lhs_vector, const Vector2D& rhs_vector) {
		return Vector2D(lhs_vector.X() + rhs_vector.X(), lhs_vector.Y() + rhs_vector.Y());
	}
	inline Vector2D operator-(const Vector2D& lhs_vector, const Vector2D& rhs_vector) {
		return Vector2D(lhs_vector.X() - rhs_vector.X(), lhs_vector.Y() - rhs_vector.Y());
	}
	inline bool operator==(const Vector2D& rhs, const Vector2D& lhs) {
		return rhs.X() == lhs.X() && rhs.Y() == lhs.Y();
	}
	inline Vector2D& Vector2D::operator+=(const Vector2D& rhs) {
		*this = *this + rhs;
		return *this;
	}
	inline Vector2D& Vector2D::operator-=(const Vector2D& rhs) {
		*this = *this - rhs;
		return *this;
	}
}