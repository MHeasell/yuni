#include "script.h"
#include "../private/script/lua.proxy.h"

namespace Yuni
{
namespace Script
{
namespace Private
{
namespace Bind
{

	template <>
	int NthArgument<Lua*, int>::Get(Lua* ctx, unsigned int order)
	{
		int i = lua_tointeger(ctx->pProxy->pState, order + 1);
		std::cout << __FUNCTION__ << " => Lua stack @" << order << " yields integer: " << i << std::endl;
		return i;
	}

	template <>
	double NthArgument<Lua*, double>::Get(Lua* ctx, unsigned int order)
	{
		double i = lua_tonumber(ctx->pProxy->pState, order + 1);
		std::cout << __FUNCTION__ << " => Lua stack @" << order << " yields real: " << i << std::endl;
		return i;
	}

	template <>
	String NthArgument<Lua*, String>::Get(Lua* ctx, unsigned int order)
	{
		String i = lua_tostring(ctx->pProxy->pState, order + 1);
		std::cout << __FUNCTION__ << " => Lua stack @" << order << " yields string: \"" << i << "\"" << std::endl;
		return i;
	}

	template <>
	void* NthArgument<Lua*, void*>::Get(Lua* ctx, unsigned int order)
	{
		void* i = lua_touserdata(ctx->pProxy->pState, order + 1);
		std::cout << __FUNCTION__ << " => Lua stack @" << order << " yields pointer: @0x" << i << std::endl;
		return i;
	}



} // namespace Bind
} // namespace Private
} // namespace Script
} // namespace Yuni
