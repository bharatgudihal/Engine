#pragma once
#include <math.h>
namespace Engine {
	inline bool IsNAN(const float value);
	inline bool AreAboutEqual(const float i_lhs, const float i_rhs, const float epsilon = 0.0001f);
}
#include "FloatCheck-Inl.h"