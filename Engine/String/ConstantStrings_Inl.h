#pragma once
namespace Engine {
	namespace String {		

		inline bool ConstantStrings::Create() {
			if (!instance) {
				instance = new ConstantStrings();
			}
			assert(instance);
			return true;
		}

		inline void ConstantStrings::Destroy() {
			if (instance) {
				delete instance;
			}
		}

		inline ConstantStrings* ConstantStrings::GetInstance() {
			return instance;
		}

		inline ConstantStrings::~ConstantStrings() {}
	}
}