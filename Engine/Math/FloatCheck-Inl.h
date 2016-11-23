#pragma once
inline bool Engine::IsNAN(const float value) {
	volatile float val = value;
	return val != val;
}

inline bool Engine::AreAboutEqual(const float i_lhs, const float i_rhs, const float epsilon) {
	return fabs(i_lhs - i_rhs) < epsilon;
}