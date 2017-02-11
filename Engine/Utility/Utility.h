#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
namespace Engine {
	namespace Utility {
		void* LoadFile(const char* fileName, size_t & o_size);
	}
}