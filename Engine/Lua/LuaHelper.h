#pragma once
#include <assert.h>
#include <string>
#include "lua\lua.hpp"
#include "../Utility/Utility.h"
#include "../Math/Vector2D.h"
#include "../String/PooledString.h"
namespace Engine {
	namespace LuaHelper {
		class LuaHelper {
		public:
			LuaHelper(const char*);
			~LuaHelper();
			void LoadGlobalTable(const char*);
			String::PooledString LoadGlobalString(const char*);
			void LoadGlobalVector2D(const char*, Vector2D&);
			String::PooledString GetStringFromTable(const char*, int);
			void GetVector2DFromTable(const char*, Vector2D&, int);
			void GetFloatFromTable(const char*, float&, int);
			void GetTableFromTable(const char*, int);
			void Pop();
		private:
			lua_State * state;
		};
	}
}