#include "../Engine.h"
#include "../../String/StringPool.h"
#include "../../String/ConstantStrings.h"
#include "../../Utility/Utility.h"
#include "../../Messaging/MessagingSystem.h"
#include "../../Profiling/Profiler.h"
#include "../UIDGenerator.h"

namespace Engine {
	namespace Core {
		bool Startup() {
			if (Memory::MasterMemoryManager::Startup() && String::StringPool::Startup(1024) && String::ConstantStrings::Create() && Utility::FileProcessor::Startup()
				&& Messaging::MessagingSystem::Startup() && Profiling::Profiler::Startup() && UIDGenerator::Startup()) {
						return true;
			}else{
				ShutDown();
			}
			return false;
		}

		void ShutDown() {
			UIDGenerator::ShutDown();
			Profiling::Profiler::Shutdown();
			Messaging::MessagingSystem::ShutDown();
			Utility::FileProcessor::ShutDown();
			String::ConstantStrings::Destroy();
			String::StringPool::ShutDown();
			Memory::MasterMemoryManager::ShutDown();
		}
	}
}