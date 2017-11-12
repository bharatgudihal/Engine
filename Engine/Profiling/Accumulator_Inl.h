#pragma once
namespace Engine {
	namespace Profiling {
		

		inline Accumulator& Accumulator::operator+=(float time) {
			sum += time;
			count++;
			minTime = minTime > time ? time : minTime;
			maxTime = maxTime < time ? time : minTime;
			return *this;
		}

		inline float Accumulator::average() const{
			return static_cast<float>(sum / count);
		}
	}
}