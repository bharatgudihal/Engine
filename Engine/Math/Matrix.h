#pragma once
#include <math.h>
#include <assert.h>
#include "FloatCheck.h"
#include "Vector4.h"
namespace Engine {
	namespace Math {
#define DEGREES2RADIANS 0.0174533f
		class Matrix {
		public:
			inline Matrix(const float i_a11 = 0.0f, const float i_a12 = 0.0f, const float i_a13 = 0.0f, const float i_a14 = 0.0f,
						  const float i_a21 = 0.0f, const float i_a22 = 0.0f, const float i_a23 = 0.0f, const float i_a24 = 0.0f,
						  const float i_a31 = 0.0f, const float i_a32 = 0.0f, const float i_a33 = 0.0f, const float i_a34 = 0.0f,
						  const float i_a41 = 0.0f, const float i_a42 = 0.0f, const float i_a43 = 0.0f, const float i_a44 = 0.0f);
			inline Matrix(const Matrix&);
			static Matrix GetXRotationMatrix(const float rotation);
			static Matrix GetYRotationMatrix(const float rotation);
			static Matrix GetZRotationMatrix(const float rotation);
			inline static Matrix GetScaleMatrix(const Vector3&);
			inline static Matrix GetTranslationMatrix(const Vector3&);
			static const Matrix IDENTITY;
			Matrix& operator=(Matrix&);
			inline bool operator==(Matrix&);
			Matrix& operator*(const float);
			Matrix& operator/(const float);
			Matrix GetTranspose();
			Matrix GetInverse();
			inline float Determinant();
			float a11,a12,a13,a14,
				  a21,a22,a23,a24,
				  a31,a32,a33,a34,
				  a41,a42,a43,a44;
		private:			
			Matrix GetAdjugate();
		};
		Matrix operator*(const Matrix&, const Matrix&);
		Vector4 operator*(const Vector4&, const Matrix&);
		Vector4 operator*(const Matrix&, const Vector4&);
	}
}
#include "Matrix_Inl.h"