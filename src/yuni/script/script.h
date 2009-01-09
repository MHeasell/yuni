#ifndef __YUNI_SCRIPT_SCRIPT_H__
# define __YUNI_SCRIPT_SCRIPT_H__

# include "../yuni.h"
# include "../toolbox/string.h"
# include <vector>
# include "variant.h"

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
			public:
		//! \name Contructor & Destructor
		//@{
		//! Default constructor
		AScript();
		//! Destructor
		virtual ~AScript();
		//@}

	public:
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
		virtual bool run() = 0;

		/*!
		** \brief Calls the specified function. It exists in 9 different template versions,
		** from 0 to 8 arguments.
		** \return True if the call was successful, false if any error occured.
		** \param[in] method The method to call
		** \param[out] returnValues A vector containing the return values of the called function, if any.
		** \param[in] arg1 The first argument (and so on.)
		**
		** This function only supports simple types like int, char, double, float, String, ...
		** If the underlying script engine do not support a particular type, it will be
		** converted to the best match.
		*/
		virtual bool call(const String& method, RetValues& retValues, const Variant& arg1 = Variant::Null) = 0;

		//@}

	private:

	}; // class AScript


} // namespace Script
} // namespace Yuni

#endif // __YUNI_SCRIPT_SCRIPT_H__
