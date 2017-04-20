#pragma once
#include <intrin.h>
#include "Matrix.h"

namespace Engine {
	namespace Math {
		namespace Opt {
			union Matrix
			{
			public:
				Matrix(const Engine::Math::Matrix&);
				Matrix(const float i_a11 = 0.0f, const float i_a12 = 0.0f, const float i_a13 = 0.0f, const float i_a14 = 0.0f,
					const float i_a21 = 0.0f, const float i_a22 = 0.0f, const float i_a23 = 0.0f, const float i_a24 = 0.0f,
					const float i_a31 = 0.0f, const float i_a32 = 0.0f, const float i_a33 = 0.0f, const float i_a34 = 0.0f,
					const float i_a41 = 0.0f, const float i_a42 = 0.0f, const float i_a43 = 0.0f, const float i_a44 = 0.0f);
				Engine::Math::Matrix GetStandardMatrix() const;
				__m128 row1, row2, row3, row4;
				struct {
					float a11, a12, a13, a14,
						a21, a22, a23, a24,
						a31, a32, a33, a34,
						a41, a42, a43, a44;
				};
			};
			Matrix operator*(const Matrix&, const Matrix&);
			Vector4 operator*(const Vector4&, const Matrix&);
			Vector4 operator*(const Matrix&, const Vector4&);
		}
	}
}