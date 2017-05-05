#include "../Matrix_Opt.h"

namespace Engine {
	namespace Math {
		namespace Opt {

			Matrix::Matrix(
				const float i_a11, const float i_a12, const float i_a13, const float i_a14,
				const float i_a21, const float i_a22, const float i_a23, const float i_a24,
				const float i_a31, const float i_a32, const float i_a33, const float i_a34,
				const float i_a41, const float i_a42, const float i_a43, const float i_a44) :
				a11(i_a11), a12(i_a12), a13(i_a13), a14(i_a14),
				a21(i_a21), a22(i_a22), a23(i_a23), a24(i_a24),
				a31(i_a31), a32(i_a32), a33(i_a33), a34(i_a34),
				a41(i_a41), a42(i_a42), a43(i_a43), a44(i_a44) {}

			Matrix::Matrix(const Engine::Math::Matrix& i_matrix){
				rows[0] = _mm_set_ps(i_matrix.a14, i_matrix.a13, i_matrix.a12, i_matrix.a11);
				rows[1] = _mm_set_ps(i_matrix.a24, i_matrix.a23, i_matrix.a22, i_matrix.a21);
				rows[2] = _mm_set_ps(i_matrix.a34, i_matrix.a33, i_matrix.a32, i_matrix.a31);
				rows[3] = _mm_set_ps(i_matrix.a44, i_matrix.a43, i_matrix.a42, i_matrix.a41);
			}

			Engine::Math::Matrix Matrix::GetStandardMatrix() const{
				return Engine::Math::Matrix
					(a11, a12, a13, a14,
					a21, a22, a23, a24,
					a31, a32, a33, a34,
					a41, a42, a43, a44);
			}

			Matrix operator*(const Matrix& lhs, const Matrix& rhs) {				
				Matrix result;

				__m128 rhs_row1 = rhs.rows[0];
				__m128 rhs_row2 = rhs.rows[1];
				__m128 rhs_row3 = rhs.rows[2];
				__m128 rhs_row4 = rhs.rows[3];

				__m128 sum = _mm_mul_ps(_mm_load1_ps(&lhs.a11), rhs_row1);
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a12), rhs_row2));
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a13), rhs_row3));
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a14), rhs_row4));
				_mm_storel_pi(reinterpret_cast<__m64*>(&result.a11), sum);
				_mm_storeh_pi(reinterpret_cast<__m64*>(&result.a13), sum);

				sum = _mm_mul_ps(_mm_load1_ps(&lhs.a21), rhs.rows[0]);
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a22), rhs_row2));
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a23), rhs_row3));
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a24), rhs_row4));
				_mm_storel_pi(reinterpret_cast<__m64*>(&result.a21), sum);
				_mm_storeh_pi(reinterpret_cast<__m64*>(&result.a23), sum);

				sum = _mm_mul_ps(_mm_load1_ps(&lhs.a31), rhs.rows[0]);
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a32), rhs_row2));
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a33), rhs_row3));
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a34), rhs_row4));
				_mm_storel_pi(reinterpret_cast<__m64*>(&result.a31), sum);
				_mm_storeh_pi(reinterpret_cast<__m64*>(&result.a33), sum);

				sum = _mm_mul_ps(_mm_load1_ps(&lhs.a41), rhs.rows[0]);
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a42), rhs_row2));
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a43), rhs_row3));
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&lhs.a44), rhs_row4));
				_mm_storel_pi(reinterpret_cast<__m64*>(&result.a41), sum);
				_mm_storeh_pi(reinterpret_cast<__m64*>(&result.a43), sum);

				return result;
			}

			Vector4 operator*(const Vector4& lhs, const Matrix& rhs) {
				float x = lhs.X();
				float y = lhs.Y();
				float z = lhs.Z();
				float w = lhs.W();

				__m128 rhs_row1 = _mm_load_ps(&rhs.a11);
				__m128 rhs_row2 = _mm_load_ps(&rhs.a21);
				__m128 rhs_row3 = _mm_load_ps(&rhs.a31);
				__m128 rhs_row4 = _mm_load_ps(&rhs.a41);

				__m128 sum = _mm_mul_ps(_mm_load1_ps(&x), rhs_row1);
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&y), rhs_row2));
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&z), rhs_row3));
				sum = _mm_add_ps(sum, _mm_mul_ps(_mm_load1_ps(&w), rhs_row4));
				return Vector4(sum.m128_f32[0], sum.m128_f32[1], sum.m128_f32[2], sum.m128_f32[3]);
			}

			Vector4 operator*(const Matrix& lhs, const Vector4& rhs) {
				Vector4 result;
				__m128 vector = _mm_set_ps(rhs.W(), rhs.Z(), rhs.Y(), rhs.X());

				__m128 lhs_row1 = _mm_load_ps(&lhs.a11);
				__m128 lhs_row2 = _mm_load_ps(&lhs.a21);
				__m128 lhs_row3 = _mm_load_ps(&lhs.a31);
				__m128 lhs_row4 = _mm_load_ps(&lhs.a41);

				__m128 acc = _mm_mul_ps(vector, lhs_row1);
				acc = _mm_hadd_ps(acc, acc);
				acc = _mm_hadd_ps(acc, acc);
				result.X(_mm_cvtss_f32(acc));

				acc = _mm_mul_ps(vector, lhs_row2);
				acc = _mm_hadd_ps(acc, acc);
				acc = _mm_hadd_ps(acc, acc);
				result.Y(_mm_cvtss_f32(acc));

				acc = _mm_mul_ps(vector, lhs_row3);
				acc = _mm_hadd_ps(acc, acc);
				acc = _mm_hadd_ps(acc, acc);
				result.Z(_mm_cvtss_f32(acc));

				acc = _mm_mul_ps(vector, lhs_row4);
				acc = _mm_hadd_ps(acc, acc);
				acc = _mm_hadd_ps(acc, acc);
				result.W(_mm_cvtss_f32(acc));

				return result;
			}
		}
	}
}