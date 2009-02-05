
#include "lua.h"
#include "../private/script/lua.proxy.h"
#include <iostream>


// Defines for call() and bind()
#include "script.defines.h"
#include "../private/script/script.defines.h"


namespace Yuni
{
namespace Script
{

	Lua::Lua()
		:pEvalPending(0)
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


	void Lua::reset()
	{
		lua_close(this->pProxy->pState);
		this->pProxy->pState = luaL_newstate();
		luaL_openlibs(this->pProxy->pState);
		pEvalPending = 0;
	}


	/*
	 * TODO: Use Events to emit proper signals.
	 */
	bool Lua::appendFromFile(const String& file)
	{
		const int result = luaL_loadfile(pProxy->pState, file.c_str());
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
				++pEvalPending;
				if (pEvalPending > 1)
					lua_insert(pProxy->pState, -pEvalPending);
				// Ok
				break;
		}
		return true;
	}


	bool Lua::appendFromString(const String& script)
	{
		const int result = luaL_loadstring(pProxy->pState, script.c_str());
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
				++pEvalPending;
				if (pEvalPending > 1)
					lua_insert(pProxy->pState, -pEvalPending);
				// Ok
				break;
		}
		return true;
	}

	bool Lua::appendFromBuffer(const char * scriptBuf, const unsigned int scriptSize)
	{
		const int result = luaL_loadbuffer(pProxy->pState, scriptBuf, scriptSize, "<unnamed_buffer>");
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
				++pEvalPending;
				if (pEvalPending > 1)
					lua_insert(pProxy->pState, -pEvalPending);
				// Ok
				break;
		}
		return true;
	}


	bool Lua::prepare()
	{
		while (pEvalPending > 0)
		{
			pEvalPending--;
			if (lua_pcall(pProxy->pState, 0, 0, 0) != 0)
			{
				size_t len;
				std::cout << lua_tolstring(pProxy->pState, lua_gettop(pProxy->pState), &len) << std::endl;
				lua_pop(pProxy->pState, 1);
				return false;
			}
		}
		return true;
	}

	int Lua::popReturnValues(int args)
	{
		int popped = 0;
		while (args > 0)
		{
		/*	if (lua_isboolean(pProxy->pState))
			{
		*/
				
			lua_pop(pProxy->pState, 1);

			std::cout << "Lua: popped a value" << std::endl;
			++popped;
			--args;
		}
		return popped;
	}

	bool Lua::push(const Variant &var)
	{
		lua_checkstack(pProxy->pState, 1);
		if (var.is<short>())
		{
			lua_pushinteger(pProxy->pState, var.cast<short>());
			return true;
		}
		if (var.is<int>())
		{
			lua_pushinteger(pProxy->pState, var.cast<int>());
			return true;
		}
		if (var.is<std::string>())
		{
			const std::string &str = var.cast<std::string>();
			lua_pushlstring(pProxy->pState, str.c_str(), str.size());
			return true;
		}
		if (var.is<char*>())
		{
			const char* str = var.cast<char*>();
			lua_pushlstring(pProxy->pState, str, strlen(str));
			return true;
		}
		if (var.is<double>())
		{
			lua_pushnumber(pProxy->pState, var.cast<double>());
			return true;
		}
		if (var.is<void*>())
		{
			lua_pushlightuserdata(pProxy->pState, var.cast<void*>());
			return true;
		}
		if (var.empty())
		{
			lua_pushnil(pProxy->pState);
			return true;
		}

		return false;
	}


	/*
	 * Implementation of the call() method variants.
	 * This is done via macros, because it's very repetitive and
	 * will be unmaintainable otherwise. The drawback is that it's a little
	 * harder to understand.
	 *
	 * In the first macro below, _PART1, we get the method on the stack.
	 * If the stack did not move, the method does not exist, so we bail out.
	 *
	 * Then, we push, via the _PUSH_ARG macro, every argument given to our
	 * function (they are named argX by _X_VARIANTS macros).
	 *
	 * Finally, we make the call and catch any errors with _PART2.
	 *
	 * TODO: implement the return value handling.
	 */

# define YUNI_SCRIPT_LUA_DEFINE_CALL_PART1 \
	\
		if (pEvalPending && !this->prepare()) \
			return false; /* A script runtime error occured while evaluating loaded chunks. */ \
		int argc = 0; \
		int stackTop = lua_gettop(pProxy->pState); \
		lua_getfield(pProxy->pState, LUA_GLOBALSINDEX, method.c_str()); \
		int stackPos = lua_gettop(pProxy->pState); \
		if (stackTop == stackPos) /* Nothing has been pushed on the stack ? Strange. */ \
		{ \
			return false; /* The call can't succeed, we have nothing to call. */ \
		}



# define YUNI_SCRIPT_LUA_DEFINE_CALL_PART2 \
		if (lua_pcall(pProxy->pState, argc, 1, 0) != 0) \
		{ \
			size_t len; \
			std::cout << lua_tolstring(pProxy->pState, lua_gettop(pProxy->pState), &len) << std::endl; \
			lua_pop(pProxy->pState, 1); \
			return false; \
		} \
		/* The call succeeded. Pop any values still hanging on the stack. */ \
		stackPos = lua_gettop(pProxy->pState); \
		this->popReturnValues(stackPos - stackTop); \
		return true; 



# define YUNI_SCRIPT_LUA_PUSH_ARG(arg) \
		argc += (this->push(arg) ? 1 : 0);

	YUNI_SCRIPT_SCRIPT_DEFINE_CALL_WITH(Lua)
	{
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART1
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART2
	}

	YUNI_SCRIPT_SCRIPT_DEFINE_CALL_WITH(Lua, YUNI_SCRIPT_SCRIPT_1_VARIANT)
	{
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART1
		YUNI_SCRIPT_LUA_PUSH_ARG(arg1)
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART2
	}

	YUNI_SCRIPT_SCRIPT_DEFINE_CALL_WITH(Lua, YUNI_SCRIPT_SCRIPT_2_VARIANTS)
	{
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART1
		YUNI_SCRIPT_LUA_PUSH_ARG(arg1)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg2)
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART2
	}

	YUNI_SCRIPT_SCRIPT_DEFINE_CALL_WITH(Lua, YUNI_SCRIPT_SCRIPT_3_VARIANTS)
	{
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART1
		YUNI_SCRIPT_LUA_PUSH_ARG(arg1)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg2)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg3)
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART2
	}

	YUNI_SCRIPT_SCRIPT_DEFINE_CALL_WITH(Lua, YUNI_SCRIPT_SCRIPT_4_VARIANTS)
	{
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART1
		YUNI_SCRIPT_LUA_PUSH_ARG(arg1)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg2)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg3)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg4)
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART2
	}

	YUNI_SCRIPT_SCRIPT_DEFINE_CALL_WITH(Lua, YUNI_SCRIPT_SCRIPT_5_VARIANTS)
	{
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART1
		YUNI_SCRIPT_LUA_PUSH_ARG(arg1)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg2)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg3)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg4)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg5)
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART2
	}


	YUNI_SCRIPT_SCRIPT_DEFINE_CALL_WITH(Lua, YUNI_SCRIPT_SCRIPT_6_VARIANTS)
	{
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART1
		YUNI_SCRIPT_LUA_PUSH_ARG(arg1)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg2)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg3)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg4)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg5)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg6)
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART2
	}

	YUNI_SCRIPT_SCRIPT_DEFINE_CALL_WITH(Lua, YUNI_SCRIPT_SCRIPT_7_VARIANTS)
	{
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART1
		YUNI_SCRIPT_LUA_PUSH_ARG(arg1)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg2)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg3)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg4)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg5)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg6)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg7)
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART2
	}

	YUNI_SCRIPT_SCRIPT_DEFINE_CALL_WITH(Lua, YUNI_SCRIPT_SCRIPT_8_VARIANTS)
	{
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART1
		YUNI_SCRIPT_LUA_PUSH_ARG(arg1)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg2)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg3)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg4)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg5)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg6)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg7)
		YUNI_SCRIPT_LUA_PUSH_ARG(arg8)
		YUNI_SCRIPT_LUA_DEFINE_CALL_PART2
	}


#undef YUNI_SCRIPT_LUA_PUSH_ARG
#undef YUNI_SCRIPT_LUA_DEFINE_CALL_PART1
#undef YUNI_SCRIPT_LUA_DEFINE_CALL_PART2

	
	/*
	 * Warning: this function is ugly. Please avoid reading it. Or, if you're brave,
	 * provide a work-around. Or, see it as Abstract Art.
	 *
	 * We have to call the function back with some Variants so that the function doesn't
	 * have to deal with Lua's stack. So, we must push on the lua stack a C closure that
	 * is a proxy to the real callback. We push pointers to the essential data, along with
	 * the number of arguments of the callback, in order to make the correct function call
	 * in the proxy, and pass along any user data we were provided.
	 *
	 * The proxy will in turn extract parameters from the lua stack, and call the bound
	 * function.
	 *
	 * TODO: implement userdata passing.
	 */

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

		Lua *This = static_cast<Lua *>(lua_touserdata(state, lua_upvalueindex(1)));
		
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

#include "../private/script/script.undefs.h"
#include "script.undefs.h"
