#include "../LuaHelper.h"
namespace Engine {
	namespace LuaHelper {		

		LuaHelper::LuaHelper(const char* fileName) {
			assert(fileName);
			state = luaL_newstate();
			assert(state);
			luaL_openlibs(state);
			size_t fileSize;
			void* file = Utility::LoadFile(fileName, fileSize);
			assert(file && fileSize);
			int result = 0;
			result = luaL_loadbuffer(state, static_cast<char *>(file), fileSize, nullptr);
			lua_pcall(state, 0, 0, 0);
			assert(result == 0);
			delete[] file;
		}

		LuaHelper::~LuaHelper() {
			lua_close(state);
		}

		void LuaHelper::LoadGlobalTable(const char* key) {
			assert(key);
			int result = 0;
			result = lua_getglobal(state, key);
			assert(result == LUA_TTABLE);
		}

		String::PooledString LuaHelper::LoadGlobalString(const char* key) {
			assert(key);
			int result = 0;
			result = lua_getglobal(state, key);
			assert(result == LUA_TSTRING);
			const char* resultString = lua_tostring(state, -1);
			assert(resultString);
			return String::PooledString(resultString);
		}

		void LuaHelper::LoadGlobalVector2D(const char* key, Vector2D& outVector) {
			assert(key);
			int result = 0;
			result = lua_getglobal(state, key);
			assert(result == LUA_TTABLE);
			float floatResult[2] = { 0.0f };
			size_t index = 0;
			lua_pushnil(state);
			while (lua_next(state, -2) != 0)
			{
				assert(lua_type(state, -1) == LUA_TNUMBER);
				floatResult[index] = float(lua_tonumber(state, -1));
				lua_pop(state, 1);
				if (++index == 2)
				{
					break;
				}
			}
			lua_pop(state, 2);
			outVector.X(floatResult[0]);
			outVector.Y(floatResult[1]);
		}

		String::PooledString LuaHelper::GetStringFromTable(const char* key, int tableIndex) {
			assert(key);
			int type = LUA_TNIL;
			lua_pushstring(state, key);
			type = lua_gettable(state, tableIndex - 1);
			assert(type == LUA_TSTRING);
			const char* result = lua_tostring(state, -1);
			assert(result);
			lua_pop(state, 1);
			String::PooledString poolString(result);			
			return poolString;
		}

		void LuaHelper::GetVector2DFromTable(const char* key, Vector2D& outVector, int tableIndex) {
			assert(key);
			int type = LUA_TNIL;
			lua_pushstring(state, key);
			type = lua_gettable(state, tableIndex - 1);
			assert(type == LUA_TTABLE);
			float floatResult[2] = { 0.0f };
			size_t index = 0;
			lua_pushnil(state);
			while (lua_next(state, tableIndex - 1) != 0)
			{
				assert(lua_type(state, - 1) == LUA_TNUMBER);
				floatResult[index] = float(lua_tonumber(state, -1));
				lua_pop(state, 1);
				if (++index == 2)
				{
					break;
				}
			}
			lua_pop(state, 2);
			outVector.X(floatResult[0]);
			outVector.Y(floatResult[1]);
		}

		void LuaHelper::GetFloatFromTable(const char* key, float& outFloat, int tableIndex) {
			assert(key);
			int type = LUA_TNIL;
			lua_pushstring(state, key);
			type = lua_gettable(state, tableIndex - 1);
			assert(type == LUA_TNUMBER);
			outFloat = float(lua_tonumber(state, -1));
			lua_pop(state, 1);
		}

		void LuaHelper::GetTableFromTable(const char* key, int tableIndex) {
			assert(key);
			int type = LUA_TNIL;
			lua_pushstring(state, key);
			type = lua_gettable(state, tableIndex - 1);
			assert(type == LUA_TTABLE);
		}

		void LuaHelper::Pop() {
			lua_pop(state, 1);
		}
	}
}