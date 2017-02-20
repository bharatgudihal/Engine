#include "../Utility.h"
namespace Engine {
	namespace Utility {
		void* LoadFile(const char* fileName, size_t & o_size) {
			FILE * file = nullptr;
			errno_t error = fopen_s(&file, fileName, "rb");
			if (error != 0) {
				return nullptr;
			}
			assert(file != nullptr);
			int fileIOError = fseek(file, 0, SEEK_END);
			assert(fileIOError == 0);
			long fileSize = ftell(file);
			assert(fileSize >= 0);
			fileIOError = fseek(file, 0, SEEK_SET);
			assert(fileIOError == 0);
			uint8_t * buffer = new uint8_t[fileSize];
			assert(buffer);
			size_t FileRead = fread(buffer, 1, fileSize, file);
			assert(FileRead == fileSize);
			fclose(file);
			o_size = fileSize;
			return buffer;
		}

		FileProcessor::Task::Task(const char* i_fileName, FileType fileType) {
			assert(i_fileName != nullptr);
			fileName = _strdup(i_fileName);
			type = fileType;
		}

		char* FileProcessor::Task::GetFileName() {
			return fileName;
		}

		FileProcessor::FileType FileProcessor::Task::GetGileType() {
			return type;
		}
		
		FileProcessor::Task::~Task() {
			free(fileName);
		}
		
		FileProcessor* FileProcessor::Instance = nullptr;

		bool FileProcessor::Startup() {
			HANDLE loadFileHandle = CreateThread(NULL, 0, FileProcessor::LoadFile, NULL, CREATE_SUSPENDED, 0);			
			assert(loadFileHandle != NULL);
			HANDLE processFileHandle = CreateThread(NULL, 0, FileProcessor::ProcessFile, NULL, CREATE_SUSPENDED, 0);
			assert(processFileHandle != NULL);
			Instance = new FileProcessor(loadFileHandle, processFileHandle);
			assert(Instance != NULL);
			return true;
		}

		void FileProcessor::ShutDown() {
			if (Instance)
			{
				FileProcessor& instance = GetInstance();

				instance.shutDownEvent.Trigger();

				HANDLE ThreadHandles[] = { instance.loadFileHandle };

				DWORD Result = WaitForMultipleObjects(sizeof(ThreadHandles) / sizeof(ThreadHandles[0]), ThreadHandles, TRUE, INFINITE);

				delete Instance;
				Instance = nullptr;
			}
		}

		FileProcessor& FileProcessor::GetInstance() {
			return *Instance;
		}

		FileProcessor::FileProcessor(HANDLE i_loadFileHandle, HANDLE i_processFileHandle):loadFileHandle(i_loadFileHandle),
			processFileHandle(i_processFileHandle),
			shutDownEvent(false, "ShutDownEvent"), 
			loadSemaphore(0, 100, "LoadSemaphore"), 
			loadMutex(false, "LoadMutex"),
			processSemaphore(0, 100, "ProcessSemaphore"),
			processMutex(false, "ProcessMutex"){
			ResumeThread(loadFileHandle);
			ResumeThread(processFileHandle);
		}

		bool FileProcessor::InsertInLoadQueue(Task& task) {
			loadMutex.Acquire();
			loadQueue.push(&task);
			loadMutex.Release();
			loadSemaphore.Increment();
			return true;
		}

		bool FileProcessor::InsertInProcessQueue(FileData& fileData) {
			processMutex.Acquire();
			processQueue.push(&fileData);
			processMutex.Release();
			processSemaphore.Increment();
			return true;
		}

		FileProcessor::FileData* FileProcessor::GetFromProcessQueue() {
			FileData* fileData = nullptr;
			processMutex.Acquire();
			if (!processQueue.empty()) {
				fileData = processQueue.front();
				processQueue.pop();
			}
			processMutex.Release();
			processSemaphore.Decrement();
			return fileData;
		}

		FileProcessor::Task* FileProcessor::GetFromLoadQueue() {
			Task* task = nullptr;
			loadMutex.Acquire();
			if (!loadQueue.empty()) {
				task = loadQueue.front();
				loadQueue.pop();
			}
			loadMutex.Release();
			loadSemaphore.Decrement();
			return task;
		}

		DWORD WINAPI FileProcessor::LoadFile(void* threadData) {
			FileProcessor& instance = FileProcessor::GetInstance();
			OVERLAPPED fileOverLapped;
			fileOverLapped.Offset = fileOverLapped.OffsetHigh = 0;
			fileOverLapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);			
			HANDLE loadHandles[] = { instance.shutDownEvent.GetHandle(), instance.loadSemaphore.GetHandle() };
			HANDLE readHandles[] = { instance.shutDownEvent.GetHandle(), fileOverLapped.hEvent };
			bool done = false;			
			while (!done) {
				DWORD loadResult = WaitForMultipleObjects(sizeof(loadHandles) / sizeof(loadHandles[0]), loadHandles, FALSE, INFINITE);
				if (loadResult == WAIT_OBJECT_0) {
					done = true;
				}
				else if (loadResult == WAIT_OBJECT_0 + 1) {
					Task* task = instance.GetFromLoadQueue();
					assert(task != nullptr);
					char* fileName = task->GetFileName();
					assert(fileName != nullptr);
					HANDLE fileHandle = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
					if (fileHandle == INVALID_HANDLE_VALUE)
					{
						delete task;
					}
					else {
						DWORD fileSize = GetFileSize(fileHandle, NULL);
						assert(fileSize != INVALID_FILE_SIZE);
						uint8_t* fileBuffer = new uint8_t[fileSize];
						assert(fileBuffer != nullptr);
						BOOL readFileResult = ReadFile(fileHandle, fileBuffer, fileSize, NULL, &fileOverLapped);
						if (readFileResult != TRUE && GetLastError() != ERROR_IO_PENDING) {
							delete task;
						}
						else {
							DWORD readWaitResult = WaitForMultipleObjects(sizeof(readHandles) / sizeof(readHandles[0]), readHandles, FALSE, INFINITE);
							if (readWaitResult == WAIT_OBJECT_0) {
								CancelIo(fileHandle);
								delete task;
								done = true;
							}
							else if(readWaitResult == WAIT_OBJECT_0 + 1){
								DWORD bytesRead = 0;
								BOOL GORResult = GetOverlappedResult(fileHandle, &fileOverLapped, &bytesRead, FALSE);
								assert(GORResult == TRUE);
								FileData* fileData = new FileData(task, fileBuffer, bytesRead);
							}
							else {
								delete task;
							}
						}
					}
				}
			}
			CloseHandle(fileOverLapped.hEvent);
			return 0;
		}

		DWORD WINAPI FileProcessor::ProcessFile(void* threadData) {
			FileProcessor& instance = FileProcessor::GetInstance();
			HANDLE processHandles[] = { instance.shutDownEvent.GetHandle(), instance.processSemaphore.GetHandle() };
			bool done = false;
			while (done) {
				DWORD processResult = WaitForMultipleObjects(sizeof(processHandles) / sizeof(processHandles[0]), processHandles, FALSE, INFINITE);
				if (processResult == WAIT_OBJECT_0) {
					done = true;
				}
				else if(processResult == WAIT_OBJECT_0 + 1){
					FileData* fileData = instance.GetFromProcessQueue();
					if (fileData->task->GetGileType() == FileType::LUA) {
						
					}
					else if (fileData->task->GetGileType() == FileType::SPRITE) {

					}
				}
			}
			return 0;
		}

	}	
}