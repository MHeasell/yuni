#ifndef __YUNI_SCRIPT_SCRIPT_H__
# define __YUNI_SCRIPT_SCRIPT_H__

# include "../yuni.h"
# include "../toolbox/string.h"
# include "../toolbox/event.h"
# include "../toolbox/any.h"

// Defines complex macros used to declare call() and bind().
# include "script.defines.h"

/*
** TODO: Enable or disable a precise language support at compile-time via defines.
*/


# define YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH(cbargs, name)  \
			typedef bool (*name)cbargs



namespace Yuni
{
namespace Script
{


	/*!
	** \brief All the supported languages.
	** \todo This enum must be dynamic to account only for the
	** \todo built-in languages.
	** \ingroup Script
	*/
	enum Language
	{
		//! This language is unknown
		slUnknown = 0,
		//! This is the Lua language
		slLua
	};



	/*!
	** \brief Script Interface (abstract)
	** \ingroup Script
	*/
	class AScript
	{
	public:
		/*!
        ** \name Various Callback types
        ** \see AScript::bind()
        */
		//@{
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *), Callback0);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_1_ANY), Callback1);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_2_ANYS), Callback2);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_3_ANYS), Callback3);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_4_ANYS), Callback4);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_5_ANYS), Callback5);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_6_ANYS), Callback6);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_7_ANYS), Callback7);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_8_ANYS), Callback8);
		//@}


	public:
		//! \name Contructor & Destructor
		//@{
		//! Default constructor
		AScript();
		//! Destructor
		virtual ~AScript();
		//@}

		//! \name Language
		//@{
		//! Returns the script language
		virtual Language language() const = 0;
		//@}


		//! \name Script load & save operations
		//@{

		/*!
		** \brief Loads the specified file a fresh script context.
		**
		** This method is equivalent to calling reset() just before appendFromFile().
		**
		** \param[in] file The file to load
		** \return True if the script was at least parsed correcty.
		*/
		virtual bool loadFromFile(const String& file)
		{ this->reset(); return appendFromFile(file); }

		/*!
		** \brief Loads the specified file in the current context.
		**
		** The specified file will be parsed and may or may not be evaluated
		** immediately, depending on the capacities of the underlying script
		** engine. You may call this method several times to sequentially load several
		** files in the same script context. The files will be parsed (and evaluated 
		** on subsequent calls to call() or prepare()) in the same order.
		** sequentially in this case (FIFO).
		**
		** \param[in] file The file to load
		** \return True if the script was at least parsed correcty.
		** \see run(), call()
		*/
		virtual bool appendFromFile(const String& file) = 0;

		/*!
		** \brief Loads the specified string in a fresh script context
		**
		** Behaves like loadFromFile().
		**
		** \param[in] script The string to load
		** \return True if the script was at least parsed correcty.
		** \see loadFromFile()
		*/
		virtual bool loadFromString(const String& script)
		{ this->reset(); return appendFromString(script); }

		/*!
		** \brief Loads the specified string in the current context
		**
		** Behaves like appendFromFile().
		**
		** \param[in] script The string to load
		** \return True if the script was at least parsed correcty.
		** \see appendFromFile()
		*/
		virtual bool appendFromString(const String& script) = 0;

		/*!
		** \brief Loads the specified buffer a fresh context
		**
		** Behaves like loadFromFile().
		**
		** \param[in] scriptBuf The buffer to load
		** \param[in] scriptSize The size of the data in scriptBuf.
		** \return True if the script was at least parsed correcty.
		** \see loadFromFile()
		*/
		virtual bool loadFromBuffer(const char *scriptBuf, const unsigned int scriptSize)
		{ this->reset(); return appendFromBuffer(scriptBuf, scriptSize); }

		/*!
		** \brief Loads the specified buffer in the current context
		**
		** Behaves like appendFromFile().
		**
		** \param[in] scriptBuf The buffer to load
		** \param[in] scriptSize The size of the data in scriptBuf.
		** \return True if the script was at least parsed correcty.
		** \see appendFromFile()
		*/
		virtual bool appendFromBuffer(const char *scriptBuf, const unsigned int scriptSize) = 0;

		/*!
		** \brief Restarts the script engine
		**
		** Almost equivalent to destroying and re-creating the script object. The
		** script engine is initialized again.
		*/
		virtual void reset() = 0;

		//@}

		//! \name Execution control
		//@{

		/*!
		** \brief Parses and run any pending script or script chunk loaded with
		** loadFromString() or loadFromFile().
		**
		** Once the scripts are run, they are removed from the queue, and subsequent
		** calls to run() won't do anything. If you want to repeat a particular action,
		** consider creating a script function doing what you want, and call() it.
		**
		** In case of error while parsing scripts, the parsing stops at the first problem
		** and this function returns false.
		**
		** \return True if there was no error returned by the script engine, false otherwise.
		*/
		virtual bool prepare() = 0;


		/*!
		** \brief Call the default entry point of the script
		**
		** This method is a convenient shortcut for the "main" function in
		** the current script. It is equivalent to: call("main");
		**
		** \return True if the "main" function was successfully called.
		*/
		bool run() {return call(NULL, "main");}


		/*!
		** \brief This family of functions calls the specified function.
		**		  
        ** It exists in 9 different versions, from 0 to 8 arguments.
		** 
        ** \param[out] retValues A variant containing the (or a list of) the return
		**			   values. You may pass NULL there if you do
		**			   not wish to do anything with the return value.
		** \param[in] method The method to call in the script namespace
		** \param[in] arg1 The first argument (and so on.) You can pass an empty Any as a
		**			  value to mean the same thing as "nil" in Lua.
		** \return True if the call was made without any runtime fatal error.
		**
		** This function supports a restricted set of value types. If a type mean nothing in the
		** current script language, a default neutral value will be used.
		**
		** \code
		**
		** Any ret;
		** Script::AScript *sc = ...; 
		** std::vector<int> intVector;
		**
		** [...]
		**
		** if (!sc->call("luaMethod", 42, 55.42, intVector, "Some string"))
		** {
		**	 // The call has failed
		** }
		** else
		** {
		**	 // Do something with ret.
		** }
		**
		** \endcode
		*/
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH() = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_1_ANY) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_2_ANYS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_3_ANYS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_4_ANYS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_5_ANYS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_6_ANYS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_7_ANYS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_8_ANYS) = 0;


		/*!
		** \brief This family of function binds a C++ global function with 0 to 8 Yuni::Any arguments in
		** the lua namespace, with the (script namespace) name method.
        **
		** \param[in] method The method name in the lua namespace
		** \param[in] callback the callback function (a global function or a static method), taking an AScript* as first
		**			  argument, and 0 to 8 Yuni::Any arguments.
		** \param[in] callbackData Not yet implemented. Will be any user data that you wish to pass as a context to callback().
		** \return True if the function was successfully bound.
		**
		** \warning, the callback protocol will change soon.
		**
		** \code
		**
		** bool myPrint(AScript *, const Any &toPrint)
		** {
		**	 if (toPrint.type() != Any::vtCString)
		**		return false;
		**	 std::cout << toPrint << std::endl;
		**	 return true;
		** }
		**
		** Script::AScript *sc = ...; 
		**
		** if (!sc->bind("myPrint_function", &(::myPrint)))
		** {
		**		// The function could not be bound
		** }
		** else
		** {
		**		// The function was bound !
		**		// You can call it from the script.
		** }
		**
		** \endcode
		*/
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback0) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback1) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback2) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback3) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback4) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback5) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback6) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback7) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_BIND_WITH(Callback8) = 0;

		//@}

	public:

		//! Type for script run-time error events
		typedef Event::E5<void, Language, const String& /* file */, unsigned int /* line */,
			unsigned int /* position */, const String& /*errorString */> ScriptErrorEvent;


		/*!
		** \brief Event for script errors
		**
		** This event will be emitted on every script error reported
		** by the underlying script engine.
		*/
		ScriptErrorEvent onError;

	}; // class AScript



	//! Type for multiple return values
	typedef std::vector<Any> MultipleReturn;




} // namespace Script
} // namespace Yuni


// Cleans up complex macros used to declare call() and bind().
# include "script.undefs.h"

#endif // __YUNI_SCRIPT_SCRIPT_H__
