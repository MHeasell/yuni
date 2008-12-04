#ifndef __YUNI_TOOLBOX_GETOPT_PARSER_H__
# define __YUNI_TOOLBOX_GETOPT_PARSER_H__

# include <list>
# include <map>
# include "string.h"
# include "option.h"



namespace Yuni
{
namespace ToolBox
{
namespace GetOpt
{


	/*!
	** \brief Command-line options parser
	**
	** \code
	** // The command-line parser
	** GetOpt::Parser parser;
	**
	** // The option --add
	** GetOpt::Option<String>* oAdd = parser.add<String>('a', "add", "Add a module", true);
	** // The option --list
	** GetOpt::Option<String>* oList = parser.add<String>('l', "list", "List of available modules");
	** // The option --width
	** GetOpt::Option<uint16>* oWidth = parser.add<uint16>(' ', "width", "Width", true, 800);
	** // The option --height
	** GetOpt::Option<uint16>* oHeight = parser.add<uint16>(' ', "height", "Height", true, 600);
	**
	** // Allow extra options such as filenames for example
	** parser.allowExtraOptions(true);
	**
	** // Analyze the command-line arguments
	** if (!parser(argc, argv))
	**		return 1;
	** // The user might have requueted the help
	** if (parser.displayHelpIfNeeded())
	**		return 0;
	**
	** // --add
	** if (oAdd->modified())
	** {
	**		std::cout << " *** --add ***" << std::endl;
	**		// The latest given value :
	**		std::cout << "Add module : the latest given value: `" << oAdd->value() << "`" << std::endl;
	**		// All values
	**		std::cout << "All modules :" << std::endl;
	**		GetOpt::Option<String>::const_iterator end = oAdd->end();
	**		for (GetOpt::Option<String>::const_iterator i = oAdd->begin(); i != end; ++i)
	**			std::cout << "  - `" << *i << "`" << std::endl;
	** }
	** // --list
	** if (oList->modified())
	** {
	**		std::cout << " *** --list ***" << std::endl;
	**		std::cout << "Here is the list of all modules :\n" << "  - <none> :)" << std::endl;
	** }
	** //--width
	** std::cout << "Width  : " << (*oWidth)() << std::endl;
	** //--height
	** std::cout << "Height : " << (*oHeight)() << std::endl;
	** \endcode
	*/
	class Parser
	{
	public:
		//! \name Constructors & Destructor
		//@{
		//! Default constructor
		Parser();
		//! Copy constructor
		Parser(const Parser&);
		//! Destructor
		~Parser();
		//@}

		/*!
		** \brief Remove all options
		*/
		void clear();

		//! \name Options
		//@{

		/*!
		** \brief Add an option
		**
		** The instance of the class `Parser` takes the ownership
		** on the given pointer. Consequently the option must not be deleted.
		** \param A pointer to the option to add
		*/
		void add(AOption* opt);
		//! \see add(AOption*)
		Parser& operator += (AOption* opt) {this->add(opt);return *this;}

		/*!
		** \brief Convenient method to Create then Add an option
		**
		** This methode creates first the appropriate object. Then this object is
		** added to the list of options.
		** These two code are exactly the same :
		** \code
		** GetOpt::Option<int>* optFoo = new GetOpt::Option<int>('f', "foo", "An useless option");
		** parser += optFoo;
		** \endcode
		** \code
		** parser.add<int>('f', "foo", "An useless option");
		** \endcode
		**
		** The arguments of this method are exactly the same than the constructor
		** of the class `Option`.
		**
		** \param sOpt The short name of the option
		** \param lOpt The long name of the option
		** \param oComments The comments for this option
		** \param ndValue If requires an extra value
		** \param defValue The default value for the option
		** \return A pointer to the option
		**
		** \see add(AOption*)
		** \see class Option
		*/
		template<typename T, class ConvTO>
		Option<T, ConvTO>* add(const char sOpt, const String& lOpt = String(),
				const String& oComments = String(),
				const bool ndValue = false, const T& defValue = T());
		
		/*
		** see the previous declaration.
		** C++ does not really allow a default template parameter in function
		** templates
		*/
		template<typename T>
		Option<T>* add(const char sOpt, const String& lOpt = String(),
				const String& oComments = String(),
				const bool ndValue = false, const T& defValue = T())
		{
			this->add<T, DefaultConverterTo<T> >(sOpt, lOpt, oComments, ndValue, defValue);
		}



		//! Get if the parser allows extra options (such as filenames for example)
		bool allowExtraOptions() const {return pAllowExtraOptions;}
		//! Set if the parser allows extra options
		void allowExtraOptions(const bool v);


		/*!
		** \brief Reset the values of all options
		**
		** This methode is automatically used when execute() is called.
		** This method should not be used except for some special cases.
		** \see execute()
		*/
		void resetOptions();
		
		//@}

		
		//! \name Execute
		//@{
		/*!
		** \brief Parse the command line arguments
		** 
		** \param argc The count of arguments
		** \param argv The list of arguments
		** \return False if the program should stop
		*/
		bool execute(int argc, char* argv[]);
		//! \see execute()
		bool operator () (int argc, char* argv[]) {return execute(argc, argv);}
		//@}

		
		//! \name Help
		//@{
		/*!
		** \brief Display the help
		** \return Always 0
		*/
		int displayHelp() const;
		/*!
		** \brief Display the help if the option --help or -h  has been given
		** \return True if the help has been displayed, false otherwise
		*/
		bool displayHelpIfNeeded() const;
		//@} // Help

	private:
		//! Relationship between short option names and the options
		typedef std::map<char, AOption*> ShortOptionsNames;
		//! Relationship between long option names and the options
		typedef std::map<String, AOption*>  LongOptionsNames;
		//! All available options
		typedef std::list<AOption*> AllOptions;

	private:
		/*!
		** \brief Print the usage
		** \return Always false (the program should quit)
		*/
		bool help() const;

		/*!
		** \brief Display an error
		** \return Always false (the program should quit)
		*/
		bool error(const String& e) const;

		/*!
		** \brief Parse a single argument
		** \param argc The count of arguments
		** \param argv The list of arguments
		** \param[in,out] index The current index in the list of arguments
		** \param[in,out] Options have to be considered
		** \return True if successful, false otherwise
		*/
		bool parseSingleArgument(int argc, char* argv[], int& index, bool& parseOptions);

		/*!
		** \brief Analyze an argument considered a long option name
		**
		** \param argc The count of arguments
		** \param argv The list of arguments
		** \param[in,out] String of the argument
		** \param[in,out] index The current index in the list of arguments
		** \return True if successful, false otherwise
		*/
		bool parseLongArgument(int argc, char* argv[], const String& arg, int& index);

		/*!
		** \brief Analyze an argument considered a short option name
		**
		** \param argc The count of arguments
		** \param argv The list of arguments
		** \param[in,out] arg String of the argument
		** \param[in,out] index The current index in the list of arguments
		** \return True if successful, false otherwise
		*/
		bool parseShortArgument(int argc, char* argv[], const char arg, int& index);

		/*!
		** \brief Update the value of an option
		**
		** If the option needs an extra value, this value will be
		** pick up from the current index. Otherwise, the option is only
		** marked as `modified`.
		**
		** \param argc The count of arguments
		** \param argv The list of arguments
		** \param o The option to update
		** \param index The current index in the list of arguments 
		** \return True if successful, false otherwise
		*/
		bool updateOption(int argc, char* argv[], AOption& o, int& index);

		/*!
		** \brief Recreate the option `help` 
		*/
		void insertHelpOption();


	private:
		//! All available options
		AllOptions pAllOptions;
		//! All options with short names
		ShortOptionsNames  pShortNames;
		//! All options with long names
		LongOptionsNames pLongNames;
		//! The `help` option
		Option<bool>* pOptHelp;
		//! All unknown options
		Option<String> pOptionUnknown;
		//! Allow extra values (like files for example)
		bool pAllowExtraOptions;
		
	}; // class Parser





} // namespace GetOpt
} // namespace ToolBox
} // namespace Yuni


# include "parser.hxx"

#endif // __YUNI_TOOLBOX_GETOPT_PARSER_H__
