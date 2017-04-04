#pragma once
#include "../String/StringPool.h"
#include "../String/ConstantStrings.h"
#include "../Utility/Utility.h"
#include "../Messaging/MessagingSystem.h"

namespace Engine {
	namespace Core {
		bool Startup();
		void ShutDown();
	}
}