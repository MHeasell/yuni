
#define YUNI_NO_THREAD_SAFE // disabling thread-safety
#include <yuni/yuni.h>
#include <yuni/core/string.h>
#include <yuni/core/getopt.h>
#include <iostream>
#include <list>
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
			pOptNoSystemPath(false), pOptModuleList(false),
			pOptSystemPathList(false),
			pOptCxxFlags(false), pOptLibFlags(false),
			pOptCompiler(YUNI_LIBCONFIG_DEFAULT_COMPILER)
		{}

		int execute(int argc, char** argv)
		{
			// Find the root path
			findRootPath(argv[0]);
			// Parse the command line
			if (!parseCommandLine(argc, argv))
				return pExitStatus;

			// Display informations if asked
			if (!displayInformations())
				return pExitStatus;

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
			opts.addParagraph("\nCompiler settings:");
			opts.addFlag(pOptCxxFlags, ' ', "cxxflags", "Print the CXX flags");
			opts.addFlag(pOptLibFlags, ' ', "libs", "Print the Libs flags");
			opts.add(pOptCompiler, 'c', "compiler", "Set the target compiler (gcc,vs9,mingw,icc,...)");

			// All required modules
			opts.addParagraph("\nModules:");
			opts.add(pOptModules, 'm', "modules", "Add one or several requested modules");
			opts.addFlag(pOptModuleList, ' ', "module-list", "Print all available modules and exit");

			// Prefix
			opts.addParagraph("\nSearching paths:");
			opts.add(pOptPrefix, 'p', "prefix", "Add a prefix folder for searching available versions of libyuni");
			opts.addFlag(pOptNoSystemPath, ' ', "no-system-path", "Do not use standard system paths to find available versions of libyuni");
			opts.addFlag(pOptSystemPathList, ' ', "system-path-list", "Print the standard system paths and exit");

			opts.addParagraph("\nVersions:");
			opts.addFlag(pOptList, 'l', "list", "Print the list of all versions of libyuni which have been found (with complete informations) and exit");
			opts.addFlag(pOptListOnlyVersions, ' ', "list-only-versions", "Print the list of all versions of libyuni which have been found and exit");

			// Help
			opts.addParagraph("\nHelp");
			opts.addFlag(pOptVersion, 'v', "version", "Print the version and exit");

			if (!opts(argc, argv))
			{
				pExitStatus = opts.errors() ? 1 /*error*/ : 0;
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
			if (!pOptNoSystemPath && pSystemPathList.empty())
			{
				# ifdef YUNI_OS_WINDOWS
				pSystemPathList.push_back("${PROGRAMFILES}\\libyuni");
				pSystemPathList.push_back("${PROGRAMFILES}\\Dev\\libyuni");
				pSystemPathList.push_back("C:\\Dev\\libyuni");
				# else
				pSystemPathList.push_back("/usr/share/libyuni");
				pSystemPathList.push_back("/usr/local/share/libyuni");
				pSystemPathList.push_back("/local/opt/usr/local/share/libyuni");
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
			if (pOptSystemPathList)
			{
				initializeSystemPathList();
				for (String::List::const_iterator i = pSystemPathList.begin(); i != pSystemPathList.end(); ++i)
					std::cout << *i << std::endl;
				return true;
			}

			pVersionList.compiler(pOptCompiler);
			pVersionList.checkRootFolder(pRootPath);
			pVersionList.findFromPrefixes(pOptPrefix);
			if (!pOptNoSystemPath)
			{
				initializeSystemPathList();
				pVersionList.findFromPrefixes(pSystemPathList);
			}

			// List
			if (pOptListOnlyVersions)
			{
				pVersionList.print();
				return true;
			}
			if (pOptList)
			{
				pVersionList.printWithInfos();
				return true;
			}
			return false;
		}

	private:
		int pExitStatus;
		String pRootPath;
		bool pOptVersion;
		bool pOptList;
		bool pOptListOnlyVersions;
		bool pOptNoSystemPath;
		bool pOptModuleList;
		bool pOptSystemPathList;
		bool pOptCxxFlags;
		bool pOptLibFlags;
		String::List pOptModules;
		String::List pOptPrefix;
		String::List pSystemPathList;
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
