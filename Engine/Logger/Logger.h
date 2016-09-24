#ifndef LOGGER_H
namespace Engine {	
	void DebugLog(const char* format,...);	
}
#endif // !LOGGER_H
#ifdef _DEBUG
#define DEBUG_LOG(fmt,...) Engine::Logger::DebugLog((fmt),__VAR_ARGS__)
#else
#define DEBUG_LOG(fmt,...) void(0)
#endif // _DEBUG
