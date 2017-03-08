#pragma once
namespace Engine {
	namespace Math {

		inline Matrix::Matrix(
			const float i_a11, const float i_a12, const float i_a13, const float i_a14,
			const float i_a21, const float i_a22, const float i_a23, const float i_a24,
			const float i_a31, const float i_a32, const float i_a33, const float i_a34,
			const float i_a41, const float i_a42, const float i_a43, const float i_a44) :
			a11(i_a11), a12(i_a12), a13(i_a13), a14(i_a14),
			a21(i_a21), a22(i_a22), a23(i_a23), a24(i_a24),
			a31(i_a31), a32(i_a32), a33(i_a33), a34(i_a34),
			a41(i_a41), a42(i_a42), a43(i_a43), a44(i_a44) {}

		inline Matrix::Matrix(const Matrix& other) :
			a11(other.a11), a12(other.a12), a13(other.a13), a14(other.a14),
			a21(other.a21), a22(other.a22), a23(other.a23), a24(other.a24),
			a31(other.a31), a32(other.a32), a33(other.a33), a34(other.a34),
			a41(other.a41), a42(other.a42), a43(other.a43), a44(other.a44) {}

		inline Matrix Matrix::GetScaleMatrix(float xScale, float yScale, float zScale) {
			Matrix result(
				xScale, 0.0f, 0.0f, 0.0f,
				0.0f, yScale, 0.0f, 0.0f,
				0.0f, 0.0f, zScale, 0.0f,
				0.0f, 0.0f, 0.0, 1.0f);
			return result;
		}

		inline Matrix Matrix::GetTranslationMatrix(float xTranslate, float yTranslate, float zTranslate) {
			Matrix result(
				1.0f, 0.0f, 0.0f, xTranslate,
				0.0f, 1.0f, 0.0f, yTranslate,
				0.0f, 0.0f, 1.0f, zTranslate,
				0.0f, 0.0f, 0.0f, 1.0f);
			return result;
		}

		inline float Matrix::Determinant() {
			return a11*(a22*(a33*a44 - a34*a43) - a23*(a32*a44 - a42*a34) + a24*(a32*a43 - a33*a42))
				- a12*(a21*(a33*a44 - a34*a43) - a23*(a31*a44 - a41*a34) + a24*(a31*a43 - a33*a11))
				+ a13*(a21*(a32*a44 - a34*a42) - a22*(a31*a44 - a41*a34) + a24*(a31*a42 - a32*a41))
				- a14*(a21*(a32*a43 - a33*a42) - a22*(a31*a43 - a33*a41) + a23*(a31*a42 - a32*a41));
		}
	}
}