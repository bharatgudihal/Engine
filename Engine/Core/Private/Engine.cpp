#include "../Engine.h"
namespace Engine {
	namespace Core {
		bool Startup() {
			if (Memory::MasterMemoryManager::Startup()) {
				if (String::StringPool::Startup(1024) && String::ConstantStrings::Create()) {
					return true;
				}else{
					Memory::MasterMemoryManager::ShutDown();
					return false;
				}
			}
			return false;
		}

		void ShutDown() {
			String::ConstantStrings::Destroy();
			String::StringPool::ShutDown();
			Memory::MasterMemoryManager::ShutDown();
		}
	}
}