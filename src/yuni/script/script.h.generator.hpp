<?php


// Generated templates parameter comments, from A0 to Ai.
function GenerateTemplateComments($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; $j++)
	{
		$ret .= '		** \tparam A'.$j.' Type of the '.($j + 1).'th argument'."\n";
	}
	return $ret;
}

// Generated templates parameters, from A0 to Ai.
function GenerateTemplateParameters($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; $j++)
	{
		if ($j)
			$ret .= ', ';
		$ret .= 'typename A'.$j;
	}
	return $ret;
}

function GenerateArguments($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; $j++)
	{
		if ($j)
			$ret .= ', ';
		$ret .= 'A'.$j;
	}
	return $ret;
}

ob_start();
?>
#ifndef __YUNI_SCRIPT_SCRIPT_H__
# define __YUNI_SCRIPT_SCRIPT_H__

/*
**
** WARNING !
** -----------------------------------------------------------------
** This file was automatically generated by <?=basename(__FILE__)?>.
** Please make any modifications you wish to this script instead of
** this file, as they will otherwise be lost at the next generation.
** -----------------------------------------------------------------
**
*/

# include "../yuni.h"
# include "../core/string.h"
# include "../core/event.h"
# include "../core/any.h"
# include "../core/function.h"

// Defines complex macros used to declare call() and bind().
# include "script.defines.h"


namespace Yuni
{
namespace Script
{

	// Adding a language ?
	// Insert here the declaration of your language's class.
	class Lua;



namespace Private
{
namespace Bind
{

	/*!
	** \brief Base class for Argument getters
	** \tparam TScript The script engine type (Lua, ...)
	** \tparam TArgType The desired type of the argument.
	**
	** This class is empty, see script.args.language.hxx
	** for specializations.
	** The goal of this class is to get the Nth argument, forced to the
	** C++ type TArgType, for the language TScript. If the argument is not
	** compatible with TArgType, it will be set to the value of TArgType()
	*/
	template <class TScript, class TArgType>
	struct NthArgument;

	/*!
	** \brief Base class for ReturnValue pushers
	** \see NthArgument
	** \tparam TScript The script engine type (Lua, ...)
	** \tparam TValueType The type of the value to push.
	**
	** Same principle as NthArgument, but for pushing return
	** values in the script context.
	*/
	template <class TScript, class TValueType>
	struct ReturnValue;

	/*!
	** \brief Abstract proxy for C++ function binding into languages.
	** 
	** \todo document this.
	*/
	struct IBinding
	{
		//! Dtor
		virtual ~IBinding() {}

		//! Returns the contained function's arguement count
		virtual unsigned int argumentCount() = 0;

		//! Performs the actual function call for Lua implementation
		virtual int performFunctionCall(Lua * /* context */) = 0;

		// Adding a language ?
		// Insert here more function call overloads for your own script types
	};

	/*!
	** \brief Concrete templated binding implementation.
	** \tparam Fx The right Yuni::Function for the function pointer passed.
	** \tparam ReturnType The passed function return type.
	**
	** This is the only descendant of IBinding. IBinding exists only
	** because we want to be able to call the performFunctionCall method
	** without knowing exactly which instanciation was made of this class.
	*/
	template <typename Fx, typename ReturnType>
	class Binding : public IBinding
	{
	public:
		//! Ctor
		Binding(const Fx& fPtr)
			: pRealFunction(fPtr.ptr())
		{}

		unsigned int argumentCount()
		{
			return Fx::argumentsCount;
		}

		int performFunctionCall(Lua* luaContext)
		{
			/*	Lua::Private::Bind::ReturnValue<typename Fx::ReturnType>
				::Push(luaContext, callRealFunction<NthArgument>(context, 0));	*/

			pRealFunction. template callWithArgumentGetter<NthArgument, Lua*>(luaContext);

			std::cout << __FILE__ << ": Performing call, with return value." << std::endl;
			return 1;
		}

	private:
		Fx pRealFunction;
	};

	/*!
	** \brief Specialization of Binding for functions returning void.
	*/
	template <typename Fx>
	class Binding<Fx, void> : public IBinding
	{
	public:
		Binding(const Fx& fPtr)
			: pRealFunction(fPtr.ptr())
		{}

		unsigned int argumentCount()
		{
			return Fx::argumentsCount;
		}

		int performFunctionCall(Lua* luaContext)
		{
			/*	Lua::Private::Bind::ReturnValue<typename Fx::ReturnType>
				::Push(luaContext, callRealFunction<NthArgument>(context, 0));	*/
			pRealFunction. template callWithArgumentGetter<NthArgument, Lua*>(luaContext);
			std::cout << __FILE__ << ": Performing call WITHOUT return value." << std::endl;
			return 0;
		}

	private:
		Fx pRealFunction;
	};


} // namespace Bind
} // namespace Private


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
	class AScript : public Policy::ObjectLevelLockable<AScript>
	{
	public:
		//! The Threading policy
		typedef Policy::ObjectLevelLockable<AScript> ThreadingPolicy;

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
		virtual bool loadFromFile(const String& file);

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
		virtual bool loadFromString(const String& script);

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
		virtual bool loadFromBuffer(const char *scriptBuf, const unsigned int scriptSize);

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
		bool run();

		/*!
		** \brief Returns true if the named function is bound.
		** \param[in] functionName The function name
		*/
		bool isBound(const char* functionName);

		/*!
		** \brief Clears the bindings associated with the script.
		**
		** Call this method to unbind any function that may be bound
		** with the AScript underlying object.
		*/
		void clear();

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
		** \brief Binds a C++ function in the script context.
		** \param[in] method The function name in the script namespace
		** \param[in] callback A pointer to the C++ function to bind in the script.
		** \return True if the function was successfully bound.
		**
		** This family of functions bind a C++ function in the script context,
		** with the specified function name.
		**
		** Lua code:
		** \code
		** -- Print hello world !
		** myPrint_function("hello, world !");
		** \endcode
		**
		** C++ code:
		** \code
		**
		** bool myPrint(String toPrint)
		** {
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
		template <class TFuncPtr>
		bool bind(const char* functionName, TFuncPtr functionPtr);

<?php for ($i = 0; $i < 17; $i++) { 
	$genArgs = GenerateArguments($i);
	$genTpl = GenerateTemplateParameters($i);
?>
		/*!
		** \brief Binds a function with <?=($i > 0 ? $i : "no")?> argument<?=($i == 1 ? "" : "s")?>

		** \tparam R Return type of the function
<?=GenerateTemplateComments($i);?>
		*/
		template<class R<?=$genTpl ? ", ".$genTpl : ""?>>
		bool bind(const char* functionName, R (*f)(<?=$genArgs?>));

<?php } /* end for */ ?>

		/*!
		** \brief Unbinds a function by name
		** \param[in] functionName The function to unbind
		*/
		bool unbind(const char* functionName);

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

	protected:
		/*!
		** \brief Language-specific function binder
		** \param[in] name Function name inside the script.
		** \param[in] toBind Pointer to the generic function wrapper to bind.
		**
		** This function is implemented by language specific inheriting classes
		** to do the specific work required to really bind the function.
		** This involves, for example, lua_pushcclosure for Lua.
		*/
		virtual void internalBindWL(const char* name, Private::Bind::IBinding* toBind) = 0;

		/*!
		** \brief Language-specific function unbinder
		** \param[in] toUnbind Name of the function to unbind.
		** \see internalBindWL
		**
		** Reverse operation of internalBindWL.
		*/
		virtual void internalUnbindWL(const char* toUnbind) = 0;

	private:
		/*!
		** \brief Delete bound functions without unbinding them
		**
		** This operation is useful when the script context is going
		** to be destroyed and we want to delete the function objects
		** quickly.
		** The script must not be run again before the context is
		** destroyed.
		*/
		void clearWithoutUnbindWL();

	private:
		//! Type for dictionnary of currently bound functions
		typedef std::map<String, Private::Bind::IBinding*> BoundFunctions;

		//! Dictionnary of currently bound functions
		BoundFunctions pBoundFunctions;


	}; // class AScript

} // namespace Script
} // namespace Yuni


// Cleans up complex macros used to declare call() and bind().
# include "script.undefs.h"

// Template methods definitions
# include "script.hxx"
# include "script.args.hxx"

#endif // __YUNI_SCRIPT_SCRIPT_H__
<?php $file = ob_get_clean();
 file_put_contents(dirname(__FILE__)."/script.h", $file);
 die();
?>
