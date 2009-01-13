#ifndef __YUNI_SCRIPT_SCRIPT_H__
# define __YUNI_SCRIPT_SCRIPT_H__

# include "../yuni.h"
# include "../toolbox/string.h"
# include <vector>
# include "../toolbox/variant.h"

// Defines complex macros used to declare call() and bind().
# include "script.defines.h"

/*
** TODO: Enable or disable a precise language support at compile-time via defines.
*/

namespace Yuni
{
namespace Script
{

	//! Construct to store the return values.
	typedef std::vector<Variant> RetValues;

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

		#define YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH(cbargs, name) \
		typedef bool (*name)cbargs

		//! \name Various Callback types (\see AScript::bind())
		//@{

		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *), Callback0);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_1_VARIANT), Callback1);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_2_VARIANTS), Callback2);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_3_VARIANTS), Callback3);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_4_VARIANTS), Callback4);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_5_VARIANTS), Callback5);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_6_VARIANTS), Callback6);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_7_VARIANTS), Callback7);
		YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH((AScript *, YUNI_SCRIPT_SCRIPT_8_VARIANTS), Callback8);
		//@}

		#undef YUNI_SCRIPT_SCRIPT_DEFINE_CBTYPE_WITH


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
		** \brief Schedules the loading of the specified file in the script context.
		** \param[in] file The file to load
		** \return True if the file is readable, false otherwise.
		** \see run(), call()
		**
		** The specified file may not be read immediately. To ensure a correct 
		** behavior, the loaded script file must remain accessible until you
		** use one of the following methods - which will parse and run any
		** pending scripts: run(), call().
		** You may call this method several times to sequentially load several
		** files in the same script context. The files will be parsed and run 
		** sequentially in this case (FIFO).
		**
		*/
		virtual bool loadFromFile(const String& file) = 0;

		/*!
		** \brief Schedules the loading of a script chunk in the script context.
		** \todo Enhance the Script class documentation with a doxygen example.
		** \param[in] script The string containing the chunk to load.
		** \return True
		** This function behaves the same as loadFromFile, and uses the same queue.
		*/
		virtual bool loadFromString(const String& script) = 0;

		//@}

		//! \name Execution control
		//@{

		/*!
		** \brief Parses and run any pending script or script chunk loaded with
		** loadFromString() or loadFromFile().
		** \return True if there was no error returned by the script engine, false otherwise.
		**
		** Once the scripts are run, they are removed from the queue, and subsequent
		** calls to run() won't do anything. If you want to repeat a particular action,
		** consider creating a script function doing what you want, and call() it.
		**
		** In case of error while parsing scripts, the parsing stops at the first problem
		** and this function returns false.
		*/
		virtual bool prepare() = 0;

		/*!
		** \brief This method is merely a shortcut for the "main" function in
		** the current script. It is equivalent to: call("main");
		** \return True if the "main" function was successfully called.
		*/
		bool run();

		/*!
		** \fn bool call(Variant *retValues, const String& method, const Variant& arg1)
		** \brief This family of functions calls the specified function.
		**		  It exists in 9 different versions, from 0 to 8 arguments.
		** \param[out] retValues A variant containing the (or a list of) the return
		**			   values. You may pass NULL there if you do
		**			   not wish to do anything with the return value.
		** \param[in] method The method to call in the script namespace
		** \param[in] arg1 The first argument (and so on.) You can pass Variant::Null as a
		**			  value to mean the same thing as "nil" in Lua.
		** \return True if the call was made without any runtime fatal error.
		**
		** This function supports a restricted set of value types. If a type mean nothing in the
		** current script language, a default neutral value will be used.
		**
		** \code
		**
		** Variant ret;
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
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_1_VARIANT) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_2_VARIANTS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_3_VARIANTS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_4_VARIANTS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_5_VARIANTS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_6_VARIANTS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_7_VARIANTS) = 0;
		YUNI_SCRIPT_SCRIPT_DECLARE_CALL_WITH(YUNI_SCRIPT_SCRIPT_8_VARIANTS) = 0;


		/*!
		** \fn bool bind(const String& method, Callback1 callback, void *callbackData)
		** \brief This family of function binds a C++ global function with 0 to 8 Yuni::Variant arguments in
		** the lua namespace, with the (script namespace) name method.
		** \param[in] method The method name in the lua namespace
		** \param[in] callback the callback function (a global function or a static method), taking an AScript* as first
		**			  argument, and 0 to 8 Yuni::Variant arguments.
		** \param[in] callbackData Not yet implemented. Will be any user data that you wish to pass as a context to callback().
		** \return True if the function was successfully bound.
		**
		** Warning, the callback protocol will change soon.
		**
		** \code
		**
		** bool my_print(AScript *, const Variant &toPrint)
		** {
		**	 if (toPrint.type() != Variant::vtCString)
		**		return false;
		**	 std::cout << toPrint << std::endl;
		**	 return true;
		** }
		**
		** Script::AScript *sc = ...; 
		**
		** if (!sc->bind("my_print_function", &(::my_print)))
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


	}; // class AScript


} // namespace Script
} // namespace Yuni

// Cleans up complex macros used to declare call() and bind().
# include "script.undefs.h"

#endif // __YUNI_SCRIPT_SCRIPT_H__
