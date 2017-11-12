#include "..\ConstChecker.h"
#include "..\..\Math\Vector3.h"

namespace Engine {
	namespace Test {
		bool ConstChecker() {
			const Math::Vector3 vector1(132.5f, 151.0f);
			const Math::Vector3 vector2(558.4f, 157.0f);
			float x = vector1.X();
			float y = vector1.Y();
			x = vector2.X();
			y = vector2.Y();
			Math::Vector3 sum = vector1 + vector2;
			Math::Vector3 diff = vector1 - vector2;
			sum.X(5);
			//Tested
			//vector1(1.0f, 1.0f, 1.0f);
			//vector1 += vector2;
			//vector1 = vector2;
			//vector1 = vector1+vector2;
			return true;
		}
	}
}