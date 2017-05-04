namespace Engine {
	namespace Math {
		inline 	Vector3::Vector3(const float iX, const float iY, const float iZ) :x(iX), y(iY), z(iZ) {};

		inline 	Vector3::Vector3(const Vector3& other) :x(other.x), y(other.y), z(other.z) {};

		inline float Vector3::X() const { return x; }

		inline void Vector3::X(const float iX) {
			assert(!IsNAN(iX));
			x = iX;
		}

		inline float Vector3::Y() const { return y; }

		inline void Vector3::Y(const float iY) {
			assert(!IsNAN(iY));
			y = iY;
		}

		inline float Vector3::Z() const { return z; }

		inline void Vector3::Z(const float iZ) {
			assert(!IsNAN(iZ));
			z = iZ;
		}

		inline Vector3 operator+(const Vector3& lhs_vector, const Vector3& rhs_vector) {
			return Vector3(lhs_vector.X() + rhs_vector.X(), lhs_vector.Y() + rhs_vector.Y(), lhs_vector.Z() + rhs_vector.Z());
		}

		inline Vector3 operator-(const Vector3& lhs_vector, const Vector3& rhs_vector) {
			return Vector3(lhs_vector.X() - rhs_vector.X(), lhs_vector.Y() - rhs_vector.Y(), lhs_vector.Z() - rhs_vector.Z());
		}

		inline bool operator==(const Vector3& rhs, const Vector3& lhs) {
			return Engine::AreAboutEqual(rhs.X(), lhs.X()) && Engine::AreAboutEqual(rhs.Y(), lhs.Y()) && Engine::AreAboutEqual(rhs.Z(), lhs.Z());
		}

		inline Vector3& Vector3::operator+=(const Vector3& rhs) {
			*this = *this + rhs;
			return *this;
		}

		inline Vector3& Vector3::operator-=(const Vector3& rhs) {
			*this = *this - rhs;
			return *this;
		}

		inline Vector3& Vector3::operator=(const Vector3& rhs) {
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}

		inline float Vector3::SquareMagnitude() const {
			return (x*x) + (y*y) + (z*z);
		}

		inline float Vector3::Magnitude() const {
			return static_cast<float>(pow(SquareMagnitude(), 0.5f));
		}

		inline Vector3 operator*(const Vector3& lhs_vector, const float& rhs_float) {
			return Vector3(lhs_vector.X() * rhs_float, lhs_vector.Y() * rhs_float, lhs_vector.Z() * rhs_float);
		}

		inline Vector3 operator/(const Vector3& lhs_vector, const float& rhs_float) {
			return Vector3(lhs_vector.X() / rhs_float, lhs_vector.Y() / rhs_float, lhs_vector.Z() / rhs_float);
		}

		inline Vector3 operator-(const Vector3& rhs) {
			return Vector3(-rhs.X(), -rhs.Y(), -rhs.Z());
		}

		inline Vector3 operator*(const Vector3& lhs, const Vector3& rhs) {
			return Vector3(lhs.X()*rhs.X(), lhs.Y()*rhs.Y(), lhs.Z()*rhs.Z());
		}

		inline float dot(const Vector3& lhs, const Vector3& rhs) {
			return lhs.X()*rhs.X() + lhs.Y()*rhs.Y() + lhs.Z()*rhs.Z();
		}
	}
}