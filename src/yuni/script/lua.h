#ifndef __YUNI_SCRIPT_LUA_H__
# define __YUNI_SCRIPT_LUA_H__

# include "../yuni.h"
# include "../toolbox/string.h"
# include "script.h"



namespace Yuni
{

namespace Private
{
namespace Script
{
	/*!
	** \see file yuni/private/script/lua.proxy.h
	*/
	class LuaProxy;
} // namespace Script
} // namespace Private


namespace Script
{
	/*!
	** \brief The class implementing the Lua language scripting.
	** \ingroup Script
	*/
	class Lua : public AScript
	{
	public:
		//! \name Contructor & Destructor
		//@{
		//! Default constructor
		Lua();
		//! Destructor
		virtual ~Lua();
		//@}

	public:
		//! \name Language
		//@{
		//! Returns the script language
		virtual Language language() const { return slLua; }
		//@}

	public:
		//! \name Script load & save operations
		//@{

		//! Loads a script from a file to memory
		virtual bool loadFromFile(const String& file);

		//! Loads a script from a string to memory
		virtual bool loadFromString(const String& script);

		//@}
	
	private:
		//! A proxy to the Lua language API.
		Yuni::Private::Script::LuaProxy *pProxy;

	}; // class Lua


} // namespace Script
} // namespace Yuni

#endif // __YUNI_SCRIPT_SCRIPT_H__
