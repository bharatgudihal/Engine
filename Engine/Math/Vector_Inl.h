namespace Engine {

	inline 	Vector::Vector(const float iX, const float iY, const float iZ, const float iW) :x(iX), y(iY), z(iZ), w(iW) {};

	inline 	Vector::Vector(const Vector& other) :x(other.x), y(other.y), z(other.z), w(other.w) {};

	inline float Vector::X() const { return x; }

	inline void Vector::X(const float iX) {
		assert(!IsNAN(iX));
		x = iX; 
	}

	inline float Vector::Y() const { return y; }

	inline void Vector::Y(const float iY) {
		assert(!IsNAN(iY));
		y = iY; 
	}

	inline float Vector::Z() const { return z; }

	inline void Vector::Z(const float iZ) {
		assert(!IsNAN(iZ));
		z = iZ;
	}

	inline Vector operator+(const Vector& lhs_vector, const Vector& rhs_vector) {
		return Vector(lhs_vector.X() + rhs_vector.X(), lhs_vector.Y() + rhs_vector.Y(), lhs_vector.Z() + rhs_vector.Z());
	}

	inline Vector operator-(const Vector& lhs_vector, const Vector& rhs_vector) {
		return Vector(lhs_vector.X() - rhs_vector.X(), lhs_vector.Y() - rhs_vector.Y(), lhs_vector.Z() - rhs_vector.Z());
	}

	inline bool operator==(const Vector& rhs, const Vector& lhs) {
		return Engine::AreAboutEqual(rhs.X(), lhs.X()) && Engine::AreAboutEqual(rhs.Y(), lhs.Y()) && Engine::AreAboutEqual(rhs.Z(), lhs.Z());
	}

	inline Vector& Vector::operator+=(const Vector& rhs) {
		*this = *this + rhs;
		return *this;
	}

	inline Vector& Vector::operator-=(const Vector& rhs) {
		*this = *this - rhs;
		return *this;
	}

	inline Vector& Vector::operator=(const Vector& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

	inline float Vector::Magnitude() const {
		return static_cast<float>(pow((pow(x, 2) + pow(y, 2) + pow(z, 2)),0.5f));
	}

	inline Vector operator*(const Vector& lhs_vector, const float& rhs_float) {
		return Vector(lhs_vector.X() * rhs_float, lhs_vector.Y() * rhs_float, lhs_vector.Z() * rhs_float);
	}

	inline Vector operator/(const Vector& lhs_vector, const float& rhs_float) {
		return Vector(lhs_vector.X() / rhs_float, lhs_vector.Y() / rhs_float, lhs_vector.Z() / rhs_float);
	}

	inline Vector operator-(const Vector& rhs) {
		return Vector(-rhs.X(), -rhs.Y(), -rhs.Z());
	}

	inline Vector operator*(const Vector& lhs, const Vector& rhs) {
		return Vector(lhs.X()*rhs.X(), lhs.Y()*rhs.Y(), lhs.Z()*rhs.Z());
	}
}