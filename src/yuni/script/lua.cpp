
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

	bool Lua::call(const String& method, Variant* retValues, const Variant& arg1)
	{
		int argc = 0;
		int stackTop = lua_gettop(pProxy->pState);
		lua_getfield(pProxy->pState, LUA_GLOBALSINDEX, method.c_str());
		int stackPos = lua_gettop(pProxy->pState);
		if (stackTop == stackPos) // Nothing has been pushed on the stack ? Strange.
		{
			return false; // The call can't succeed, we have nothing to call.
		}

		argc += (this->push(arg1) ? 1 : 0);
			
		if (lua_pcall(pProxy->pState, argc, LUA_MULTRET, 0) != 0)
		{
			size_t len;
			std::cout << lua_tolstring(pProxy->pState, lua_gettop(pProxy->pState), &len) << std::endl;
			lua_pop(pProxy->pState, 1);
			return false;
		}
		// The call succeeded. Pop any values still hanging on the stack.
		stackPos = lua_gettop(pProxy->pState);
		while (stackPos > stackTop) // While we stil have remains from our previous call
		{
			lua_pop(pProxy->pState, 1);
			(void)retValues;
			std::cout << "Popped." << std::endl;
		}

		return true;
	}

	
// Warning: this function is ugly. Please avoid reading it. Or, if you're brave,
// provide a work-around.

#define YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH(cb, argcount) \
	bool Lua::bind(const String& method, cb callback, void *callbackData) \
	{ \
		lua_pushlightuserdata(pProxy->pState, static_cast<void *>(this)); \
		lua_pushlightuserdata(pProxy->pState, reinterpret_cast<void *>(callback)); \
		lua_pushlightuserdata(pProxy->pState, static_cast<void *>(callbackData)); \
		lua_pushinteger(pProxy->pState, argcount); /* argcount variants in the real callback */ \
		std::cout << "Pushed callback at address: " << reinterpret_cast<void *>(callback) << " with " << argcount << " args" << std::endl; \
		lua_pushcclosure(pProxy->pState, reinterpret_cast<lua_CFunction>(&(Lua::callbackProxy)), 4); \
		lua_setfield(pProxy->pState, LUA_GLOBALSINDEX, method.c_str()); \
		return true; \
	}

	YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH(Callback0, 0);
	YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH(Callback1, 1);
	YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH(Callback2, 2);
	YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH(Callback3, 3);
	YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH(Callback4, 4);
	YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH(Callback5, 5);
	YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH(Callback6, 6);
	YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH(Callback7, 7);
	YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH(Callback8, 8);

#undef YUNI_SCRIPT_LUA_IMPLEMENT_BIND_WITH

	int Lua::callbackProxy(void *st)
	{
		// Same warning as above.
		// TODO: please add some ASSERTs in this section.
		lua_State *state = static_cast<lua_State *>(st);

		Lua *This = static_cast<Lua *>(const_cast<void *>(lua_touserdata(state, lua_upvalueindex(1))));
		
		int argCount = lua_tointeger(state, lua_upvalueindex(4)); // Get the original function argument count.

		switch (argCount)
		{
			case 0:
				{
					Callback0 call = reinterpret_cast<Callback0>(lua_touserdata(state, lua_upvalueindex(2)));
					return call(This);
				}
				break;
			case 1:
				{
					Callback1 call = reinterpret_cast<Callback1>(lua_touserdata(state, lua_upvalueindex(2)));
					return call(This, 1);
				}
				break; 
			default:
				lua_pushstring(state, "Yuni::Script::Lua::callbackProxy(): received garbage data.");
				lua_error(state); // Never returns.
		};


		return 0;
	}


} // namespace Script
} // namespace Yuni
