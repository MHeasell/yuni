
#define YUNI_NO_THREAD_SAFE // disabling thread-safety
#include <yuni/yuni.h>
#include <yuni/core/string.h>
#include <yuni/core/getopt.h>
#include <iostream>
#include <list>
#include <set>
#include "versions.h"
#include <yuni/core/io/directory.h>

using namespace Yuni;



namespace
{
	class LibConfigProgram
	{
	public:
		LibConfigProgram()
			:pExitStatus(0), pOptVersion(false), pOptList(false), pOptListOnlyVersions(false),
			pOptNoDefaultPath(false), pOptModuleList(false),
			pOptDefaultPathList(false),
			pOptCxxFlags(false), pOptLibFlags(false), pOptPrintCompilerByDefault(false),
			pOptPrintErrors(false),
			pOptCompiler(YUNI_LIBCONFIG_DEFAULT_COMPILER)
		{
			// Default module
			pOptModules.push_back("core");
		}

		int execute(int argc, char** argv)
		{
			// Find the root path
			findRootPath(argv[0]);
			// Parse the command line
			if (!parseCommandLine(argc, argv))
				return pExitStatus;

			// Display information if asked
			if (!displayInformations())
				return pExitStatus;

			// Display information
			displayInformationAboutYuniVersion();

			return pExitStatus;
		}

	private:
		void findRootPath(const char* a0)
		{
			const String argv0 = a0;
			if (Core::IO::IsAbsolute(argv0))
				pRootPath = argv0;
			else
			{
				pRootPath = Core::IO::Directory::Current();
				pRootPath << Core::IO::Separator << Core::IO::ExtractFilePath(argv0);
				pRootPath.removeTrailingSlash();
			}
		}

		bool parseCommandLine(int argc, char** argv)
		{
			// The Command line parser
			GetOpt::Parser opts;

			// Compiler
			opts.addParagraph("\nTypical usage example :\n  $ libyuni-config -c gcc -m script --cxxflags\n\nCompiler settings:");
			opts.addFlag(pOptCxxFlags, ' ', "cxxflags", "Print the CXX flags (*)");
			opts.addFlag(pOptLibFlags, ' ', "libs", "Print the Libs flags (*)");
			opts.add(pOptCompiler, 'c', "compiler", "Set the target compiler (gcc,vs9,mingw,icc,...)");
			opts.addFlag(pOptPrintCompilerByDefault, ' ', "compiler-default", "Print the compiler used by default and exit");

			// All required modules
			opts.addParagraph("\nModules:");
			opts.add(pOptModules, 'm', "modules", "Add one or several requested modules (*)");
			opts.addFlag(pOptModuleList, ' ', "module-list", "Print all available modules and exit (*)");

			// Prefix
			opts.addParagraph("\nSearching paths:");
			opts.add(pOptPrefix, 'p', "prefix", "Add a prefix folder for searching available versions of libyuni");
			opts.addFlag(pOptNoDefaultPath, ' ', "no-default-path", "Do not use standard system paths to find available versions of libyuni");
			opts.addFlag(pOptDefaultPathList, ' ', "default-path-list", "Print the standard system paths that would be used and exit (empty if 'no-default-path' is enabled)");

			opts.addParagraph("\nVersions:");
			opts.addFlag(pOptList, 'l', "list", "Print the list of all versions of libyuni which have been found (with complete informations) and exit");
			opts.addFlag(pOptListOnlyVersions, ' ', "list-only-versions", "Print the list of all versions of libyuni which have been found and exit");

			// Help
			opts.addParagraph("\nHelp\n  * : Option related to the selected version of libyuni");
			opts.addFlag(pOptPrintErrors, ' ', "verbose", "Print any error message");
			opts.addFlag(pOptVersion, 'v', "version", "Print the version and exit");

			if (!opts(argc, argv))
			{
				pExitStatus = opts.errors() ? 1 /*error*/ : 0;
				if (pOptPrintErrors)
					std::cout << "Error when parsing the command line\n";
				return false;
			}

			if (pOptPrintCompilerByDefault)
			{
				std::cout << YUNI_LIBCONFIG_DEFAULT_COMPILER << "\n";
				return false;
			}

			// Clean the prefix paths (make them absolute)
			cleanPrefixPaths();
			normalizeCompiler();

			return true;
		}


		void cleanPrefixPaths()
		{
			if (!pOptPrefix.empty())
			{
				String pwd = Core::IO::Directory::Current();
				const String::List::iterator end = pOptPrefix.end();
				for (String::List::iterator i = pOptPrefix.begin(); i != end; ++i)
					*i = Core::IO::MakeAbsolute(*i, pwd);
			}
		}

		void initializeSystemPathList()
		{
			if (!pOptNoDefaultPath && pDefaultPathList.empty())
			{
				# ifdef YUNI_OS_WINDOWS
				pDefaultPathList.push_back("${PROGRAMFILES}\\libyuni");
				pDefaultPathList.push_back("${PROGRAMFILES}\\Dev\\libyuni");
				pDefaultPathList.push_back("C:\\Dev\\libyuni");
				# else
				pDefaultPathList.push_back("/usr/share/libyuni");
				pDefaultPathList.push_back("/usr/local/share/libyuni");
				pDefaultPathList.push_back("/local/opt/usr/local/share/libyuni");
				# endif
			}
		}


		void normalizeCompiler()
		{
			if (pOptCompiler == "g++")
				pOptCompiler = "gcc";
			if (pOptCompiler == "sun++")
				pOptCompiler = "suncc";
			if (pOptCompiler == "i++")
				pOptCompiler = "icc";
		}

		bool displayInformations()
		{
			if (pOptVersion)
			{
				std::cout << YUNI_VERSION_LITE_STRING << "\n";
				return true;
			}
			if (pOptDefaultPathList)
			{
				initializeSystemPathList();
				for (String::List::const_iterator i = pDefaultPathList.begin(); i != pDefaultPathList.end(); ++i)
					std::cout << *i << std::endl;
				return true;
			}

			pVersionList.compiler(pOptCompiler);
			pVersionList.checkRootFolder(pRootPath);
			pVersionList.findFromPrefixes(pOptPrefix);
			if (!pOptNoDefaultPath)
			{
				initializeSystemPathList();
				pVersionList.findFromPrefixes(pDefaultPathList);
			}

			// List
			if (pOptListOnlyVersions)
			{
				pVersionList.print();
				return false;
			}
			if (pOptList)
			{
				pVersionList.printWithInfos();
				return false;
			}
			return true;
		}

		
		void displayInformationAboutYuniVersion()
		{
			Yuni::LibConfig::VersionInfo::Settings* version = pVersionList.selected();
			if (version)
				displayInformationAboutYuniVersion(*version);
			else
			{
				pExitStatus = 1;
				if (pOptPrintErrors)
					std::cout << "Error: There is no available version of the yuni library\n";
			}
		}

		void displayInformationAboutYuniVersion(Yuni::LibConfig::VersionInfo::Settings& version)
		{
			// Getting the config file
			String::List options;
			if (!version.configFile(options, pOptPrintErrors) || !version.parserModulesOptions(options, pOptPrintErrors))
			{
				pExitStatus = 1;
				return;
			}
			// Computing dependencies
			{
				String::List deps;
				do
				{
					deps.clear();
					{
						const String::List::const_iterator end = pOptModules.end();
						for (String::List::const_iterator i = pOptModules.begin(); i != end; ++i)
						{
							if (!version.moduleExists(*i))
							{
								if (pOptPrintErrors)
									std::cout << "Error: The module '" << *i << "' can not be found\n";
								pExitStatus = 2;
								return;
							}
							const String::List& modDeps = version.moduleSettings[*i].dependencies;
							const String::List::const_iterator endJ = modDeps.end();
							for (String::List::const_iterator j = modDeps.begin(); j != endJ; ++j)
							{
								//if (pOptModules.find(*j) == pOptModules.end())
								//	deps.push_back(*j);
							}
						}
					}
					if (!deps.empty())
					{
						// Merge results
						const String::List::const_iterator end = deps.end();
						for (String::List::const_iterator i = deps.begin(); i != end; ++i)
						{
							//if (pOptModules.find(*i) == pOptModules.end())
						//		pOptModules.push_back(*i);
						}
					}
				} while (!deps.empty());
			}
		}


	private:
		int pExitStatus;
		String pRootPath;
		bool pOptVersion;
		bool pOptList;
		bool pOptListOnlyVersions;
		bool pOptNoDefaultPath;
		bool pOptModuleList;
		bool pOptDefaultPathList;
		bool pOptCxxFlags;
		bool pOptLibFlags;
		bool pOptPrintCompilerByDefault;
		bool pOptPrintErrors;
		String::List pOptModules;
		String::List pOptPrefix;
		String::List pDefaultPathList;
		Yuni::LibConfig::VersionInfo::List pVersionList;
		String pOptCompiler;

	}; // class Options


} // anonymous namespace




int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		LibConfigProgram libconfig;
		return libconfig.execute(argc, argv);
	}
	return 0;
}
