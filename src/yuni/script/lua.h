#ifndef __YUNI_SCRIPT_LUA_H__
# define __YUNI_SCRIPT_LUA_H__

# include "../yuni.h"
# include "../toolbox/string.h"
# include "script.h"

// Macros for call() and bind()
# include "script.defines.h"

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

		//! \name Language
		//@{
		//! Returns the script language
		virtual Language language() const { return slLua; }
		//@}

		//! \name Script load & save operations
		//@{

		virtual bool appendFromFile(const String& file);

		virtual bool appendFromString(const String& script);
		
		virtual bool appendFromBuffer(const char * scriptBuf, const unsigned int scriptSize);

		virtual void reset();

		//@}

		//! \name Execution control
		//@{
		virtual bool prepare();

		// call()
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH();
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_1_VARIANT);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_2_VARIANTS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_3_VARIANTS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_4_VARIANTS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_5_VARIANTS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_6_VARIANTS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_7_VARIANTS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_8_VARIANTS);

		// bind()
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback0);
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback1);
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback2);
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback3);
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback4);
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback5);
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback6);
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback7);
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback8);

		//@}

	private:
		/*!
		** \brief Pushes a variant on the Lua stack.
		** \return True if the variant was pushed, false if the variant was null.
		** \param[in] var the variant to push on the stack
		*/
		bool push(const Variant &var);

		/*!
		** \brief Callback Proxy
		*/
		static int callbackProxy(void *lua_state);
	
	private:
		//! A proxy to the Lua language API.
		Yuni::Private::Script::LuaProxy *pProxy;

		//! How many scripts are pending evaluation
		unsigned int pEvalPending;


	}; // class Lua


} // namespace Script
} // namespace Yuni

# include "script.undefs.h"

#endif // __YUNI_SCRIPT_LUA_H__
