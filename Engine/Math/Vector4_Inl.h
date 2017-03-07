#pragma once
namespace Engine {
	namespace Math {

		inline 	Vector4::Vector4(const float iX, const float iY, const float iZ, const float iW) : x(iX), y(iY), z(iZ), w(iW) {}

		inline 	Vector4::Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

		inline Vector4::Vector4(const Vector3& other) : x(other.X()), y(other.Y()), z(other.Z()), w(1.0f) {}

		inline float Vector4::X() const { return x; }

		inline void Vector4::X(const float iX) {
			assert(!IsNAN(iX));
			x = iX;
		}

		inline float Vector4::Y() const { return y; }

		inline void Vector4::Y(const float iY) {
			assert(!IsNAN(iY));
			y = iY;
		}

		inline float Vector4::Z() const { return z; }

		inline void Vector4::Z(const float iZ) {
			assert(!IsNAN(iZ));
			z = iZ;
		}

		inline float Vector4::W() const { return w; }

		inline void Vector4::W(const float iW) {
			assert(!IsNAN(iW));
			z = iW;
		}

		inline Vector4 operator+(const Vector4& lhs_vector, const Vector4& rhs_vector) {
			return Vector4(lhs_vector.X() + rhs_vector.X(), lhs_vector.Y() + rhs_vector.Y(), lhs_vector.Z() + rhs_vector.Z());
		}

		inline Vector4 operator-(const Vector4& lhs_vector, const Vector4& rhs_vector) {
			return Vector4(lhs_vector.X() - rhs_vector.X(), lhs_vector.Y() - rhs_vector.Y(), lhs_vector.Z() - rhs_vector.Z());
		}

		inline bool operator==(const Vector4& rhs, const Vector4& lhs) {
			return Engine::AreAboutEqual(rhs.X(), lhs.X()) && Engine::AreAboutEqual(rhs.Y(), lhs.Y()) && Engine::AreAboutEqual(rhs.Z(), lhs.Z());
		}

		inline Vector4& Vector4::operator+=(const Vector4& rhs) {
			*this = *this + rhs;
			return *this;
		}

		inline Vector4& Vector4::operator-=(const Vector4& rhs) {
			*this = *this - rhs;
			return *this;
		}

		inline Vector4& Vector4::operator=(const Vector4& rhs) {
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
			return *this;
		}

		inline float Vector4::Magnitude() const {
			return static_cast<float>(pow((pow(x, 2) + pow(y, 2) + pow(z, 2)), 0.5f));
		}

		inline Vector4 operator*(const Vector4& lhs_vector, const float& rhs_float) {
			return Vector4(lhs_vector.X() * rhs_float, lhs_vector.Y() * rhs_float, lhs_vector.Z() * rhs_float);
		}

		inline Vector4 operator/(const Vector4& lhs_vector, const float& rhs_float) {
			return Vector4(lhs_vector.X() / rhs_float, lhs_vector.Y() / rhs_float, lhs_vector.Z() / rhs_float);
		}

		inline Vector4 operator-(const Vector4& rhs) {
			return Vector4(-rhs.X(), -rhs.Y(), -rhs.Z());
		}

		inline Vector4 operator*(const Vector4& lhs, const Vector4& rhs) {
			return Vector4(lhs.X()*rhs.X(), lhs.Y()*rhs.Y(), lhs.Z()*rhs.Z());
		}
	}
}