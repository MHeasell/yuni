#ifndef __YUNI_PRIVATE_SCRIPT_LUA_PROXY__
#define __YUNI_PRIVATE_SCRIPT_LUA_PROXY__

# include <lua.hpp>
# include "../../yuni.h"

namespace Yuni
{
namespace Private
{
/*!
** \brief Contains internal proxy classes for the Script module.
*/
namespace Script
{

	/*!
	** \brief A proxy to avoid lua.h inclusions for user programs
	** while using the Yuni::Script::Lua class.
	**
	** This class should contain everything that deals with anything
	** contained or included by <lua.hpp>, so that a user program
	** does not have to include it.
	**
	** \see class Yuni::Script::Lua
	*/
	class LuaProxy
	{
	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		LuaProxy();
		//! Destructor
		~LuaProxy();
		//@}
	
	private:
		//! The Lua internal state storage
		lua_State*	pState;
	}; // class LuaProxy

} // namespace Script
} // namespace Private
} // namespace Yuni

#endif
