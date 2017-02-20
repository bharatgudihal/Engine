#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <queue>
#include "../Threading/Event.h"
#include "../Threading/Semaphore.h"
#include "../Threading/Mutex.h"
namespace Engine {
	namespace Utility {
		void* LoadFile(const char* fileName, size_t & o_size);

		class FileProcessor{
		public:
			enum FileType
			{
				LUA,
				SPRITE
			};
			class Task {
			public:
				Task(const char* i_fileName, FileType fileType);
				~Task();
				char* GetFileName();
				FileType GetGileType();
			private:
				char* fileName;
				FileType type;
			};
			static bool Startup();
			static void ShutDown();
			static FileProcessor& GetInstance();
			bool InsertInLoadQueue(Task&);			
		private:
			struct FileData {
				Task* task;
				uint8_t* fileData;
				uint32_t fileSize;
				FileData(Task* i_task, uint8_t* i_fileData, uint32_t i_fileSize):task(i_task), fileData(i_fileData), fileSize(i_fileSize) {
					assert(i_task != nullptr);
					assert(i_fileData != nullptr);
					assert(fileSize > 0);
				}
			};			
			static FileProcessor* Instance;
			HANDLE loadFileHandle;
			HANDLE processFileHandle;
			Threading::ManualEvent shutDownEvent;
			Threading::Semaphore loadSemaphore;
			Threading::Mutex loadMutex;
			std::queue<Task*> loadQueue;			
			Threading::Semaphore processSemaphore;
			Threading::Mutex processMutex;
			std::queue<FileData*> processQueue;
			FileProcessor(HANDLE, HANDLE);
			Task* GetFromLoadQueue();
			bool InsertInProcessQueue(FileData&);
			FileData* GetFromProcessQueue();
			static DWORD WINAPI LoadFile(void*);
			static DWORD WINAPI ProcessFile(void*);
		};
	}
}