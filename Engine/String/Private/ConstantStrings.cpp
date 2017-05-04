#include "../ConstantStrings.h"
namespace Engine {
	namespace String {
		ConstantStrings* ConstantStrings::instance = nullptr;

		ConstantStrings::ConstantStrings() :NAME("name"), CLASS("class"), CONTROLLER("controller"), POSITION("position"), PHYSICSBODY("physicsbody"),
			RENDERSETTINGS("rendersettings"), GAMEOBJECT("GameObject"), MASS("mass"), DRAG("drag"), SPRITE("sprite"), FORCEMULTIPLIER("forceMultiplier"), 
			AABB("AABB"), CENTER("Center"), EXTENTS("Extents"), COUNT("count"), ISENABLED("isEnabled"), TRUE_STRING("true"), FALSE_STRING("false"){}
	}
}