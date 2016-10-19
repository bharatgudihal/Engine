#include <Windows.h>
#include <stdio.h>
#include "..\Logger.h"
namespace Engine {	
	void DebugLog(const char* format,...) {
		const size_t lenTemp = 256;
		char strTemp[lenTemp] = "DEBUG: %s %d ";
		strcat_s(strTemp, format);
		va_list args;
		va_start(args, format);
		const size_t lenOutput = lenTemp + 32;
		char strOutput[lenOutput];
		vsprintf_s(strOutput, lenOutput, strTemp, args);
		va_end(args);
		OutputDebugStringA(strOutput);
	}
}