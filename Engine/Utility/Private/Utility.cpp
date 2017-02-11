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
	}
}