#include "../FileProcessorTest.h"

namespace Engine {
	namespace Test {
		
		void FileProcessorTest::TestFileTask::ProcessFile(uint8_t* fileData, uint32_t fileSize) {
			assert(fileData != nullptr);
			assert(fileSize > 0);
			uint8_t* temp = new uint8_t[fileSize];
			memcpy(temp, fileData, fileSize);
			UpdatePostProcessQueue(temp);
			DEBUG_LOG("Processed File %s\n", GetFileName());
		}

		FileProcessorTest::FileProcessorTest():fileQueueMutex(false, "FileQueueMutex"){}

		bool FileProcessorTest::TestFileProcessor() {
			TestFileTask* task1 = new TestFileTask("Assets\\Data\\Player.lua", &fileQueue, &fileQueueMutex);
			Utility::FileProcessor::GetInstance().InsertInLoadQueue(task1);
			TestFileTask* task2 = new TestFileTask("Assets\\Data\\Test.txt", &fileQueue, &fileQueueMutex);
			Utility::FileProcessor::GetInstance().InsertInLoadQueue(task2);
			bool done = false;
			int count = 0;
			while (!done) {
				fileQueueMutex.Acquire();
				if (!fileQueue.empty()) {
					void* temp = fileQueue.front();
					fileQueue.pop();
					delete temp;
					count++;
					if (count == 2) {
						done = true;
					}
				}
				fileQueueMutex.Release();
				Sleep(1000);
			}
			return true;
		}
		
	}
}