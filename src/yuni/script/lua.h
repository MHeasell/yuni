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
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_1_ANY);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_2_ANYS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_3_ANYS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_4_ANYS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_5_ANYS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_6_ANYS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_7_ANYS);
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_8_ANYS);

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
		** \brief Pops a number of values from the Lua stack and put them in a Any.
		** \param[in] valuesToPop The number of values to pop
		** \param[in] values A pointer on a variant that will contain either the only one
		**                   popped value, or a vector containing all the popped value.
		**                   Pass null if you do not care about the popped values.
		** \return The number of values successfully popped and converted.
		*/
		int popReturnValues(int valuesToPop, Any *values);

		/*!
		** \brief Pushes a variant on the Lua stack.
		** \param[in] var the variant to push on the stack
		** \return True if the variant was pushed, false if the variant was null.
		*/
		bool push(const Any &var);

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
