
#include "lua.h"
#include "../private/script/lua.proxy.h"

namespace Yuni
{
namespace Script
{

	Lua::Lua()
	{
		this->pProxy = new Private::Script::LuaProxy();
	}

	Lua::~Lua()
	{
		delete this->pProxy;
	}

	bool Lua::loadFromFile(const String& file)
	{
		// This is not implemented yet.
		(void)file;
		return false;
	}

	bool Lua::loadFromString(const String& script)
	{
		// This is not implemented yet.
		(void)script;
		return false;
	}


} // namespace Script
} // namespace Yuni
