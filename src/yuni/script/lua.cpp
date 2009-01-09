
#include "lua.h"
#include "../private/script/lua.proxy.h"
#include <iostream>

namespace Yuni
{
namespace Script
{

	Lua::Lua()
	{
		this->pProxy = new Private::Script::LuaProxy();
		this->pProxy->pState = luaL_newstate();
		luaL_openlibs(this->pProxy->pState);
	}

	Lua::~Lua()
	{
		lua_close(this->pProxy->pState);
		delete this->pProxy;
	}

	bool Lua::loadFromFile(const String& file)
	{
		int result = luaL_loadfile(pProxy->pState, file.c_str());
		switch (result)
		{
			case LUA_ERRSYNTAX:
				// Emit errsyntax, return false
				std::cout << "Lua: Syntax error" << std::endl;
				return false;
				break;
			case LUA_ERRMEM:
				// Emit insufficient memory, return false
				std::cout << "Lua: Insufficient memory" << std::endl;
				return false;
				break;
			case LUA_ERRFILE:
				// Emit file/permission errors, return false
				std::cout << "Lua: File access error" << std::endl;
				return false;
				break;
			default:
				// Ok
				break;
		}
		return true;
	}

	bool Lua::loadFromString(const String& script)
	{
		int result = luaL_loadstring(pProxy->pState, script.c_str());
		switch (result)
		{
			case LUA_ERRSYNTAX:
				// Emit errsyntax, return false
				std::cout << "Lua: Syntax error" << std::endl;
				return false;
				break;
			case LUA_ERRMEM:
				// Emit insufficient memory, return false
				std::cout << "Lua: Insufficient memory" << std::endl;
				return false;
				break;
			default:
				break;
		}
		return true;
	}

	bool Lua::run()
	{
		if (lua_pcall(pProxy->pState, 0, 0, 0) != 0)
		{
			size_t len;
			std::cout << lua_tolstring(pProxy->pState, lua_gettop(pProxy->pState), &len) << std::endl;
			lua_pop(pProxy->pState, 1);
			return false;
		}
		return true;
	}

	bool Lua::push(const Variant &var)
	{
		switch (var.type())
		{
			case Variant::vtShort:
				lua_pushinteger(pProxy->pState, var.asShort());
				return true;
			case Variant::vtInt:
				lua_pushinteger(pProxy->pState, var.asInt());
				return true;
			case Variant::vtString:
				{
					const String& str = var.asString();
					lua_pushlstring(pProxy->pState, str.c_str(), str.size());
					return true;
				}
			case Variant::vtCString:
				{
					lua_pushlstring(pProxy->pState, var.asCString(), strlen(var.asCString()));
					return true;
				}
			case Variant::vtDouble:
				lua_pushnumber(pProxy->pState, var.asDouble());
				return true;
			case Variant::vtPointer:
				lua_pushlightuserdata(pProxy->pState, var.asPointer());
				return true;

			default:
				break;
		}
		return false;
	}

	bool Lua::call(const String& method, RetValues& retValues, const Variant& arg1)
	{
		int argc = 0;
		retValues.clear();

		lua_getfield(pProxy->pState, LUA_GLOBALSINDEX, method.c_str());
		argc += (this->push(arg1) ? 1 : 0);
			
		if (lua_pcall(pProxy->pState, argc, 0, 0) != 0)
		{
			size_t len;
			std::cout << lua_tolstring(pProxy->pState, lua_gettop(pProxy->pState), &len) << std::endl;
			lua_pop(pProxy->pState, 1);
			return false;
		}
		return true;
	}
} // namespace Script
} // namespace Yuni
