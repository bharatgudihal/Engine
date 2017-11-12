#pragma once
#include "../Utility/Utility.h"
#include "../Logger/Logger.h"

namespace Engine {
	namespace Test {
		class FileProcessorTest {
		public:
			class TestFileTask :public Utility::FileProcessor::Task {
			public:
				TestFileTask(const char* fileName, std::queue<void*>* i_postProcessQueue, Threading::Mutex* i_postProcessMutex) :Utility::FileProcessor::Task(fileName, i_postProcessQueue, i_postProcessMutex) {};
				void ProcessFile(uint8_t*, uint32_t) override;
			};
			FileProcessorTest();
			bool TestFileProcessor();
		private:
			std::queue<void*> fileQueue;
			Threading::Mutex fileQueueMutex;
		};		
	}
}