#include "../Input.h"

namespace Engine {

	unsigned int Input::keyCode = 0;
	bool Input::isDown = false;

	void Input::KeyChangeCallBack(unsigned int i_KeyCode, bool i_IsDown) {
		Input::keyCode = i_KeyCode;
		Input::isDown = i_IsDown;
		//DEBUG_LOG("Key %d, isdown %d\n", Input::keyCode, Input::isDown);
	}
}