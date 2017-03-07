#include "../Matrix.h"
namespace Engine {
	namespace Math {

		const Matrix Matrix::IDENTITY(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		Matrix Matrix::GetRotationMatrix(const float xRotation, const float yRotation, const float zRotation) {
			Matrix defaultResult;
			if (xRotation != 0.0f) {
				float cosX = static_cast<float>(cos(xRotation * DEGREES2RADIANS));
				float sinX = static_cast<float>(sin(xRotation * DEGREES2RADIANS));
				Matrix xRotationMatrix(
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, cosX, -sinX, 0.0f,
					0.0f, sinX, cosX, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
				return xRotationMatrix;
			}
			if (yRotation != 0.0f) {
				float cosY = static_cast<float>(cos(yRotation * DEGREES2RADIANS));
				float sinY = static_cast<float>(sin(yRotation * DEGREES2RADIANS));
				Matrix yRotationMatrix(
					cosY, 0.0f, sinY, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					-sinY, 0.0f, cosY, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
				return yRotationMatrix;
			}
			if (yRotation != 0.0f) {
				float cosZ = static_cast<float>(cos(zRotation * DEGREES2RADIANS));
				float sinZ = static_cast<float>(sin(zRotation * DEGREES2RADIANS));
				Matrix zRotationMatrix(
					cosZ, -sinZ, 0.0f, 0.0f,
					sinZ, cosZ, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
				return zRotationMatrix;
			}
			return defaultResult;
		}

		Matrix& Matrix::operator=(Matrix& other) {
			a11 = other.a11;
			a12 = other.a12;
			a13 = other.a13;
			a14 = other.a14;
			a21 = other.a21;
			a22 = other.a22;
			a23 = other.a23;
			a24 = other.a24;
			a31 = other.a31;
			a32 = other.a32;
			a33 = other.a33;
			a34 = other.a34;
			a41 = other.a41;
			a42 = other.a42;
			a43 = other.a43;
			a44 = other.a44;
			return *this;
		}

		Matrix& Matrix::operator*(const float value) {
			a11 *= value;
			a12 *= value;
			a13 *= value;
			a14 *= value;
			a21 *= value;
			a22 *= value;
			a23 *= value;
			a24 *= value;
			a31 *= value;
			a32 *= value;
			a33 *= value;
			a34 *= value;
			a41 *= value;
			a42 *= value;
			a43 *= value;
			a44 *= value;
			return *this;
		}

		Matrix& Matrix::operator/(const float value) {
			a11 /= value;
			a12 /= value;
			a13 /= value;
			a14 /= value;
			a21 /= value;
			a22 /= value;
			a23 /= value;
			a24 /= value;
			a31 /= value;
			a32 /= value;
			a33 /= value;
			a34 /= value;
			a41 /= value;
			a42 /= value;
			a43 /= value;
			a44 /= value;
			return *this;
		}

		void Matrix::Transpose() {
			float temp = a12;
			a12 = a21;
			a21 = temp;
			temp = a13;
			a13 = a31;
			a31 = temp;
			temp = a14;
			a14 = a41;
			a41 = temp;
			temp = a23;
			a23 = a32;
			a32 = temp;
			temp = a24;
			a24 = a42;
			a42 = temp;
			temp = a34;
			a34 = a43;
			a43 = temp;
		}

		Matrix Matrix::GetAdjugate() {

			//Find minors
			float adj11 = a22*(a33*a44 - a34*a43) - a23*(a32*a44 - a42*a34) + a24*(a32*a43 - a33*a42);
			float adj12 = a21*(a33*a44 - a34*a43) - a23*(a31*a44 - a41*a34) + a24*(a31*a43 - a33*a11);
			float adj13 = a21*(a32*a44 - a34*a42) - a22*(a31*a44 - a41*a34) + a24*(a31*a42 - a32*a41);
			float adj14 = a21*(a32*a43 - a33*a42) - a22*(a31*a43 - a33*a41) + a23*(a31*a42 - a32*a41);
			float adj21 = a12*(a33*a44 - a34*a43) - a13*(a32*a44 - a34*a42) + a14*(a32*a43 - a33*a42);
			float adj22 = a11*(a33*a44 - a34*a43) - a13*(a31*a44 - a34*a41) + a14*(a31*a44 - a33*a41);
			float adj23 = a11*(a32*a44 - a34*a42) - a12*(a31*a44 - a34*a41) + a14*(a31*a42 - a32*a41);
			float adj24 = a11*(a32*a43 - a33*a42) - a12*(a31*a43 - a33*a41) + a13*(a31*a42 - a32*a41);
			float adj31 = a12*(a23*a44 - a24*a43) - a13*(a22*a44 - a24*a42) + a14*(a22*a43 - a23*a42);
			float adj32 = a11*(a23*a44 - a24*a43) - a13*(a21*a44 - a24*a41) + a14*(a21*a43 - a23*a41);
			float adj33 = a11*(a22*a44 - a24*a42) - a12*(a21*a44 - a24*a41) + a14*(a21*a42 - a22*a41);
			float adj34 = a11*(a22*a43 - a23*a42) - a12*(a21*a43 - a23*a41) + a13*(a21*a42 - a22*a41);
			float adj41 = a12*(a23*a34 - a24*a33) - a13*(a22*a34 - a24*a32) + a14*(a22*a33 - a23*a32);
			float adj42 = a11*(a23*a34 - a24*a33) - a13*(a21*a34 - a24*a31) + a14*(a21*a33 - a23*a31);
			float adj43 = a11*(a22*a34 - a24*a32) - a12*(a21*a34 - a24*a31) + a14*(a21*a32 - a22*a31);
			float adj44 = a11*(a22*a33 - a23*a32) - a12*(a21*a33 - a23*a31) + a13*(a21*a32 - a22*a31);

			//Create matrix of cofactors
			adj12 = -adj12;
			adj14 = -adj14;
			adj22 = -adj22;
			adj24 = -adj24;
			adj32 = -adj32;
			adj34 = -adj34;
			adj42 = -adj42;
			adj44 = -adj44;

			Matrix adj(
				adj11, adj12, adj13, adj14,
				adj21, adj22, adj23, adj24,
				adj31, adj32, adj33, adj34,
				adj41, adj42, adj43, adj44);

			adj.Transpose();
			return adj;
		}

		void Matrix::Invert() {
			float determinant = Determinant();
			Matrix adjugate = GetAdjugate();
			Matrix inverse = adjugate / determinant;
			a11 = inverse.a11;
			a12 = inverse.a12;
			a13 = inverse.a13;
			a14 = inverse.a14;
			a21 = inverse.a21;
			a22 = inverse.a22;
			a23 = inverse.a23;
			a24 = inverse.a24;
			a31 = inverse.a31;
			a32 = inverse.a32;
			a33 = inverse.a33;
			a34 = inverse.a34;
			a41 = inverse.a41;
			a42 = inverse.a42;
			a43 = inverse.a43;
			a44 = inverse.a44;
		}
		
	}
}