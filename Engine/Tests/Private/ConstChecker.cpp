#include "..\ConstChecker.h"
#include "..\..\Math\Vector.h"

namespace Engine {
	namespace Test {
		bool ConstChecker() {
			const Vector vector1(132.5f, 151.0f);
			const Vector vector2(558.4f, 157.0f);
			float x = vector1.X();
			float y = vector1.Y();
			x = vector2.X();
			y = vector2.Y();
			Vector sum = vector1 + vector2;
			Vector diff = vector1 - vector2;
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