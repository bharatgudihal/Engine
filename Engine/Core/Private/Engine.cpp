#include "../Engine.h"
namespace Engine {
	namespace Core {
		bool Startup() {
			if (Memory::MasterMemoryManager::Startup() && String::StringPool::Startup(1024) && String::ConstantStrings::Create() && Utility::FileProcessor::Startup()
				&& Messaging::MessagingSystem::Startup()) {
						return true;
			}else{
				ShutDown();
			}
			return false;
		}

		void ShutDown() {
			Messaging::MessagingSystem::ShutDown();
			Utility::FileProcessor::ShutDown();
			String::ConstantStrings::Destroy();
			String::StringPool::ShutDown();
			Memory::MasterMemoryManager::ShutDown();
		}
	}
}