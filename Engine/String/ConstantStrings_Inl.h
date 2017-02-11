#pragma once
namespace Engine {
	namespace String {		

		inline bool ConstantStrings::Create() {
			instance = new ConstantStrings();
			assert(instance);
			return true;
		}

		inline void ConstantStrings::Destroy() {
			delete instance;
		}

		inline ConstantStrings* ConstantStrings::GetInstance() {
			return instance;
		}

		inline ConstantStrings::~ConstantStrings() {}
	}
}