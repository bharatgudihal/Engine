#pragma once
#include "..\Logger\Logger.h"

namespace Engine {
	class Input {
	public:
		static unsigned int keyCode;
		static bool isDown;
		static void KeyChangeCallBack(unsigned int i_KeyCode, bool i_IsDown);
	};
}