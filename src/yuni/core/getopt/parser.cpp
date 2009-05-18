#include <iostream>
#include <iomanip>
#include <string.h>
#include "parser.h"


#define YUNI_GETOPT_COLUMN_WIDTH    30



namespace Yuni
{
namespace Toolbox
{
namespace GetOpt
{


	Parser::Parser()
		:pOptHelp(NULL), pOptionUnknown(' '), pAllowExtraOptions(true)
	{
		insertHelpOption();
	}


	Parser::Parser(const Parser& c)
		:pAllOptions(c.pAllOptions), pShortNames(c.pShortNames),
		pLongNames(c.pLongNames), pOptionUnknown(c.pOptionUnknown),
		pAllowExtraOptions(c.pAllowExtraOptions)
	{
		pOptHelp = new Option<bool>('h', "help", "Print this help");
	}


	Parser::~Parser()
	{
		// The method `clear()` is here useless. The destructor of the
		// list will be called and all resources will be properly destroyed.
		// this->clear();
	}


	void Parser::clear()
	{
		pLongNames.clear();
		pShortNames.clear();
		pAllOptions.clear();
		// As the `help` option will be destroyed, we have to recreate
		// a new one
		insertHelpOption();
	}


	void Parser::insertHelpOption()
	{
		# ifdef YUNI_OS_WINDOWS
		pOptHelp = new Option<bool>('?', "help", "Print this help");
		# else
		pOptHelp = new Option<bool>('h', "help", "Print this help");
		# endif
		this->add(pOptHelp);
	}



	void Parser::add(AOption* opt)
	{
		if (NULL != opt)
		{
			if (' ' != opt->shortName())
				pShortNames.insert(std::pair<char, AOption*>(opt->shortName(), opt));
			if (!opt->longName().empty())
				pLongNames.insert(std::pair<String, AOption*>(opt->longName(), opt));
			pAllOptions.push_back(opt);
		}
	}


	void Parser::resetOptions()
	{
		AllOptions::iterator end = pAllOptions.end();
		for (AllOptions::iterator i = pAllOptions.begin(); i != end; ++i)
			(*i)->reset();
	}


	bool Parser::error(const String& e) const
	{
		std::cerr << "Error: " << e << std::endl;
		std::cerr << "Try --help for more information." << std::endl;
		return false;
	}


	bool Parser::help() const
	{
		// Usage
		std::cout << "Usage:" << std::endl;
		// All available options
		AllOptions::const_iterator end = pAllOptions.end();
		for (AllOptions::const_iterator i = pAllOptions.begin(); i != end; ++i)
		{
			String title = (*i)->fullNameForHelp();
			if (!title.empty())
			{
				if (title.length() < YUNI_GETOPT_COLUMN_WIDTH)
				{
					std::cout << "  " << std::setw(YUNI_GETOPT_COLUMN_WIDTH) << std::left
						<< title
						<< std::setw(0)
						<< (*i)->comments() << std::endl;
				}
				else
					std::cout << std::setw(0) << "  " << title << std::endl;
			}
		}
		return false;
	}


	bool Parser::updateOption(int argc, char* argv[], AOption& o, int& index)
	{
		if (o.valueIsRequired())
		{
			if (++index < argc)
				o.addValue(argv[index]);
			else
				// Need an extra value
				return error(String("The option `") << o.bestSuitableName() << "` requires an extra value");
		}
		else
			// Toggle the value
			o.modified(true);
		return true;
	}


	bool Parser::parseShortArgument(int argc, char* argv[], const char arg, int& index)
	{
		ShortOptionsNames::iterator o = pShortNames.find(arg);
		return (o != pShortNames.end())
			? updateOption(argc, argv, *(o->second), index)
			: error("Invalid option -");
	}


	bool Parser::parseLongArgument(int argc, char* argv[], const String& arg, int& index)
	{
		// Long options
		LongOptionsNames::iterator o = pLongNames.find(arg);
		return (o != pLongNames.end())
			? updateOption(argc, argv, *(o->second), index)
			: error(String("Invalid option --") << arg);
	}


	bool Parser::parseSingleArgument(int argc, char* argv[], int& index, bool& parseOptions)
	{
		const char* opt = argv[index];
		if ('\0' == *opt)
			return true;
		// The argument
		if (parseOptions)
		{
			if (opt[1] != '\0') // length > 1
			{
				if ('-' == *opt) // maybe an option
				{
					if ('-' == opt[1]) // maybe a long option
					{
						if ('\0' == opt[2]) // got "--", end of options
						{
							parseOptions = false;
							return true;
						}
						// Long argument detected
						return parseLongArgument(argc, argv, (const char*)(opt + 2), index);
					}
					// It is a short option
					// Browsing all chars
					while('\0' != *(++opt))
					{
						if (!parseShortArgument(argc, argv, *opt, index))
							return false;
					}
					return true;
				}
				# ifdef YUNI_OS_WINDOWS
				if ('/' == *opt && (isalnum(opt[1]) || '?' == opt[1]))
				{
					if ('\0' == opt[2]) // short option
						return parseShortArgument(argc, argv, opt[1], index);
					// long option
					return parseLongArgument(argc, argv, (const char*)(opt + 1), index);
				}
				# endif
			}
		}
		// Not an option
		if (!pAllowExtraOptions)
		{
			String s("Unknown option: `");
			s += argv[index];
			s += "`";
			return error(s);
		}
		pOptionUnknown.addValue(opt);
		return true;
	}


	bool Parser::execute(int argc, char* argv[])
	{
		// Reset the value for all options
		this->resetOptions();
		pOptionUnknown.reset();
		// We have to parse the option
		// This variable is disabled when "--" is encountered
		bool parseOptions(true);

		// Browse all arguments
		for (int i = 1; i < argc; ++i)
		{
			if (!this->parseSingleArgument(argc, argv, i, parseOptions))
				return false;
		}
		return true;
	}


	int Parser::displayHelp() const
	{
		this->help();
		return 0;
	}

	bool Parser::displayHelpIfNeeded() const
	{
		if (pOptHelp->modified())
		{
			this->help();
			return true;
		}
		return false;
	}


	void Parser::allowExtraOptions(const bool v)
	{
		pAllowExtraOptions = v;
	}



} // namespace GetOpt
} // namespace Toolbox
} // namespace Yuni


