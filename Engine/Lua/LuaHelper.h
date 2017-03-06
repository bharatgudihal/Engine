#pragma once
#include <assert.h>
#include <string>
#include "lua\lua.hpp"
#include "../Utility/Utility.h"
#include "../Math/Vector.h"
#include "../String/PooledString.h"
namespace Engine {
	namespace LuaHelper {
		class LuaHelper {
		public:
			LuaHelper(void*, size_t);
			~LuaHelper();
			void LoadGlobalTable(const char*);
			String::PooledString LoadGlobalString(const char*);
			void LoadGlobalVector2D(const char*, Vector&);
			String::PooledString GetStringFromTable(const char*, int);
			void GetVector2DFromTable(const char*, Vector&, int);
			void GetFloatFromTable(const char*, float&, int);
			void GetTableFromTable(const char*, int);
			void Pop();
		private:
			lua_State * state;
		};
	}
}