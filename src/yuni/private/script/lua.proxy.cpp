
#include "lua.proxy.h"

namespace Yuni
{
namespace Private
{
namespace Script
{

	LuaProxy::LuaProxy()
	{
		this->pState = luaL_newstate();
		luaL_openlibs(this->pState);
	}

	LuaProxy::~LuaProxy()
	{
		lua_close(this->pState);
	}

} // namespace Script
} // namespace Private
} // namespace Yuni
