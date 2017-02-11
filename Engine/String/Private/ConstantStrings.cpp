#include "../ConstantStrings.h"
namespace Engine {
	namespace String {
		ConstantStrings* ConstantStrings::instance = nullptr;

		ConstantStrings* ConstantStrings::GetInstance() {
			if (instance == nullptr) {
				instance = new ConstantStrings();
			}
			return instance;
		}

		ConstantStrings::ConstantStrings():NAME("name"), CLASS("class"), CONTROLLER("controller"), POSITION("position"), PHYSICSBODY("physicsbody"),
			RENDERSETTINGS("rendersettings"), PLAYER("Player"), PLAYERCONTROLLER("PlayerController"), MASS("mass"), DRAG("drag"), SPRITE("sprite"),
			FORCEMULTIPLIER("forceMultiplier"){}
	}
}