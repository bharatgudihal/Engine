#pragma once
inline bool Engine::IsNAN(const float value) {
	volatile float val = value;
	return val != val;
}