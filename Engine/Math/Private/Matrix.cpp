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

		Matrix Matrix::GetTranspose() {
			Matrix transpose(
				a11, a21, a31, a41,
				a12, a22, a32, a42,
				a13, a23, a33, a43,
				a14, a24, a34, a44);
			return transpose;
		}

		Matrix Matrix::GetAdjugate() {

			//Find minors
			float adj11 = a22*(a33*a44 - a34*a43) - a23*(a32*a44 - a42*a34) + a24*(a32*a43 - a33*a42);
			float adj12 = a21*(a33*a44 - a34*a43) - a23*(a31*a44 - a41*a34) + a24*(a31*a43 - a33*a41);
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
			adj21 = -adj21;
			adj23 = -adj23;
			adj32 = -adj32;
			adj34 = -adj34;
			adj41 = -adj41;
			adj43 = -adj43;
			Matrix adj(
				adj11, adj12, adj13, adj14,
				adj21, adj22, adj23, adj24,
				adj31, adj32, adj33, adj34,
				adj41, adj42, adj43, adj44);
			Matrix transpose = adj.GetTranspose();
			return transpose;
		}

		Matrix Matrix::GetInverse() {
			float determinant = Determinant();
			Matrix adjugate = GetAdjugate();
			Matrix inverse = adjugate / determinant;
			return inverse;
		}
		
		Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
			float result11 = lhs.a11*rhs.a11 + lhs.a12*rhs.a21 + lhs.a13*rhs.a31 + lhs.a14*rhs.a41;
			float result12 = lhs.a11*rhs.a12 + lhs.a12*rhs.a22 + lhs.a13*rhs.a32 + lhs.a14*rhs.a42;
			float result13 = lhs.a11*rhs.a13 + lhs.a12*rhs.a23 + lhs.a13*rhs.a33 + lhs.a14*rhs.a43;
			float result14 = lhs.a11*rhs.a14 + lhs.a12*rhs.a24 + lhs.a13*rhs.a34 + lhs.a14*rhs.a44;
			float result21 = lhs.a21*rhs.a11 + lhs.a22*rhs.a21 + lhs.a23*rhs.a31 + lhs.a24*rhs.a41;
			float result22 = lhs.a21*rhs.a12 + lhs.a22*rhs.a22 + lhs.a23*rhs.a32 + lhs.a24*rhs.a42;
			float result23 = lhs.a21*rhs.a13 + lhs.a22*rhs.a23 + lhs.a23*rhs.a33 + lhs.a24*rhs.a43;
			float result24 = lhs.a21*rhs.a14 + lhs.a22*rhs.a24 + lhs.a23*rhs.a34 + lhs.a24*rhs.a44;
			float result31 = lhs.a31*rhs.a11 + lhs.a32*rhs.a21 + lhs.a33*rhs.a31 + lhs.a34*rhs.a41;
			float result32 = lhs.a31*rhs.a12 + lhs.a32*rhs.a22 + lhs.a33*rhs.a32 + lhs.a34*rhs.a42;
			float result33 = lhs.a31*rhs.a13 + lhs.a32*rhs.a23 + lhs.a33*rhs.a33 + lhs.a34*rhs.a43;
			float result34 = lhs.a31*rhs.a14 + lhs.a32*rhs.a24 + lhs.a33*rhs.a34 + lhs.a34*rhs.a44;
			float result41 = lhs.a41*rhs.a11 + lhs.a42*rhs.a21 + lhs.a43*rhs.a31 + lhs.a44*rhs.a41;
			float result42 = lhs.a41*rhs.a12 + lhs.a42*rhs.a22 + lhs.a43*rhs.a32 + lhs.a44*rhs.a42;
			float result43 = lhs.a41*rhs.a13 + lhs.a42*rhs.a23 + lhs.a43*rhs.a33 + lhs.a44*rhs.a43;
			float result44 = lhs.a41*rhs.a14 + lhs.a42*rhs.a24 + lhs.a43*rhs.a34 + lhs.a44*rhs.a44;
			Matrix result(
				result11, result12, result13, result14,
				result21, result22, result23, result24,
				result31, result32, result33, result34,
				result41, result42, result43, result44);
			return result;
		}

		Vector4 operator*(const Vector4& lhs, const Matrix& rhs) {
			float resultX = lhs.X()*rhs.a11 + lhs.Y()*rhs.a21 + lhs.Z()*rhs.a31 + lhs.W()*rhs.a41;
			float resultY = lhs.X()*rhs.a12 + lhs.Y()*rhs.a22 + lhs.Z()*rhs.a32 + lhs.W()*rhs.a42;
			float resultZ = lhs.X()*rhs.a13 + lhs.Y()*rhs.a23 + lhs.Z()*rhs.a33 + lhs.W()*rhs.a43;
			float resultW = lhs.X()*rhs.a14 + lhs.Y()*rhs.a24 + lhs.Z()*rhs.a34 + lhs.W()*rhs.a44;
			Vector4 result(resultX, resultY, resultZ, resultW);
			return result;
		}

		Vector4 operator*(const Matrix& lhs, const Vector4& rhs) {
			float resultX = lhs.a11*rhs.X() + lhs.a12*rhs.Y() + lhs.a13*rhs.Z() + lhs.a14*rhs.W();
			float resultY = lhs.a21*rhs.X() + lhs.a22*rhs.Y() + lhs.a23*rhs.Z() + lhs.a24*rhs.W();
			float resultZ = lhs.a31*rhs.X() + lhs.a32*rhs.Y() + lhs.a33*rhs.Z() + lhs.a34*rhs.W();
			float resultW = lhs.a41*rhs.X() + lhs.a42*rhs.Y() + lhs.a43*rhs.Z() + lhs.a44*rhs.W();
			Vector4 result(resultX, resultY, resultZ, resultW);
			return result;
		}
	}
}