#pragma once
#include <assert.h>
#include <string>
#include "lua\lua.hpp"
#include "../Utility/Utility.h"
#include "../Math/Vector3.h"
#include "../String/PooledString.h"
namespace Engine {
	namespace LuaHelper {
		class LuaHelper {
		public:
			LuaHelper(void*, size_t);
			~LuaHelper();
			bool LoadGlobalTable(const char*);
			String::PooledString LoadGlobalString(const char*);
			bool LoadGlobalVector2D(const char*, Math::Vector3&);
			String::PooledString GetStringFromTable(const char*, int);
			bool GetVector2DFromTable(const char*, Math::Vector3&, int);
			bool GetFloatFromTable(const char*, float&, int);
			bool GetTableFromTable(const char*, int);
			void Pop();
		private:
			lua_State * state;
		};
	}
}