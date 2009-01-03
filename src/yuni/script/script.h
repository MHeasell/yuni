#ifndef __YUNI_SCRIPT_SCRIPT_H__
# define __YUNI_SCRIPT_SCRIPT_H__

# include "../yuni.h"
# include "../toolbox/string.h"

/*
** TODO: Enable or disable a precise language support at compile-time via defines.
*/

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

	public:
		//! \name Script load & save operations
		//@{

		//! Loads a script from a file to memory
		virtual bool loadFromFile(const String& file) = 0;

		//! Loads a script from a string to memory
		virtual bool loadFromString(const String& script) = 0;

		//@}

	}; // class AScript


} // namespace Script
} // namespace Yuni

#endif // __YUNI_SCRIPT_SCRIPT_H__
