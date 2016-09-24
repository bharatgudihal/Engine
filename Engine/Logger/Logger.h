#include <varargs.h>
#ifndef LOGGER_H
namespace Engine {	
	void DebugLog(const char* format, char* fileName, int lineNumber, ...);
}
#endif // !LOGGER_H
#ifdef _DEBUG
#define DEBUG_LOG(fmt,...) Engine::DebugLog((fmt),__FILE__,__LINE__,__VA_ARGS__)
#else
#define DEBUG_LOG(fmt,...) void(0)
#endif // _DEBUG
