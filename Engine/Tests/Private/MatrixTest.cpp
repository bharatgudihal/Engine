#include "../MatrixTest.h"
#define DEGREES2RADIANS 0.0174533f
namespace Engine {
	namespace Test {
		bool TestMatrix() {
			Math::Vector3 testVector3(2.0f, 4.8f, 3.3f);
			Math::Vector4 testVector4(testVector3);
			Math::Matrix testTranslationMatrix = Math::Matrix::GetTranslationMatrix(testVector3);
			Math::Matrix proofTranslationMatrix(
				1.0f, 0.0f, 0.0f, 2.0f,
				0.0f, 1.0f, 0.0f, 4.8f,
				0.0f, 0.0f, 1.0f, 3.3f,
				0.0f, 0.0f, 0.0f, 1.0f);
			assert(testTranslationMatrix == proofTranslationMatrix);
			assert(testTranslationMatrix == testTranslationMatrix.GetTranspose().GetTranspose());
			Math::Matrix testInverse = testTranslationMatrix.GetInverse();
			Math::Matrix proofInverse(
				1.0f, 0.0f, 0.0f, -2.0f,
				0.0f, 1.0f, 0.0f, -4.8f,
				0.0f, 0.0f, 1.0f, -3.3f,
				0.0f, 0.0f, 0.0f, 1.0f);
			assert(testInverse == proofInverse);
			Math::Matrix testRotationMatrix = Math::Matrix::GetRotationMatrix(30.0f, 0.0f, 0.0f);
			Math::Matrix proofRotationMatrix(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, static_cast<float>(cos(DEGREES2RADIANS*30.0f)), static_cast<float>(-sin(DEGREES2RADIANS*30.0f)), 0.0f,
				0.0f, static_cast<float>(sin(DEGREES2RADIANS*30.0f)), static_cast<float>(cos(DEGREES2RADIANS*30.0f)), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
			assert(testRotationMatrix == proofRotationMatrix);
			return true;
		}
	}
}