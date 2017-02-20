#include "../Engine.h"
namespace Engine {
	namespace Core {
		bool Startup() {
			if (Memory::MasterMemoryManager::Startup()) {
				if (String::StringPool::Startup(1024) && String::ConstantStrings::Create()) {
					if (Utility::FileProcessor::Startup()) {
						return true;
					}
					else {
						String::ConstantStrings::Destroy();
						String::StringPool::ShutDown();
						Memory::MasterMemoryManager::ShutDown();
						return false;
					}
				}else{
					Memory::MasterMemoryManager::ShutDown();
					return false;
				}
			}
			return false;
		}

		void ShutDown() {
			Utility::FileProcessor::ShutDown();
			String::ConstantStrings::Destroy();
			String::StringPool::ShutDown();
			Memory::MasterMemoryManager::ShutDown();
		}
	}
}