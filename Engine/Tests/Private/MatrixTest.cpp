#include "../MatrixTest.h"

namespace Engine {
	namespace Test {
		bool TestMatrix() {
			Math::Vector3 testVector3(2.0f, 4.8f, 3.3f);
			Math::Vector4 testVector4(testVector3);
			Math::Matrix testMatrix = Math::Matrix::GetTranslationMatrix(testVector3);
			assert(testMatrix == testMatrix.GetTranspose().GetTranspose());
			Math::Matrix testInverse = testMatrix.GetInverse();
			Math::Matrix proofInverse(
				1.0f, 0.0f, 0.0f, -2.0f,
				0.0f, 1.0f, 0.0f, -4.8f,
				0.0f, 0.0f, 1.0f, -3.3f,
				0.0f, 0.0f, 0.0f, 1.0f);
			assert(testInverse == proofInverse);
			return true;
		}
	}
}