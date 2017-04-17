#pragma once
namespace Engine {
	namespace Profiling {
		inline Accumulator::Accumulator(const char* name):sum(0.0),count(0),min(std::numeric_limits<float>::max()), max(std::numeric_limits<float>::min()) {
			Profiler::Instance()->RegisterAccumulator(name, this);
		}

		inline void Accumulator::operator+=(float time) {
			sum += time;
			count++;
			min = min > time ? time : min;
			max = max < time ? time : min;
		}

		inline float Accumulator::average() const{
			return static_cast<float>(sum / count);
		}
	}
}