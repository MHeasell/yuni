
#include <yuni/yuni.h>
#include "make.h"
#include <yuni/core/system/cpu.h>
#include <yuni/core/math.h>
#include <yuni/core/getopt.h>
#include "logs.h"


using namespace Yuni;


unsigned int Make::nbJobs = 1;
bool Make::debug    = false;
bool Make::verbose  = false;
bool Make::clean    = false;
bool Make::shortUrl = false;




Make::Make() :
	printVersion(false)
{
}


bool Make::parseCommandLine(int argc, char** argv)
{
	// The total number of CPU
	const unsigned int cpuCount = System::CPU::Count();
	// The most appropriate number of simultaneous jobs
	nbJobs = (cpuCount > 4) ? 4 : cpuCount;

	// The Command line parser
	GetOpt::Parser opts;

	// Compiler
	opts.addParagraph("\nOptions:");
	opts.add(input, ' ', "input", "Source folder");
	opts.add(htdocs, ' ', "htdocs", "htdocs folder");
	opts.addFlag(clean, 'c', "clean", "Clean the htdocs folder first");
	opts.addFlag(shortUrl, 's', "short-url", "Use short url");
	opts.add(nbJobs, 'j', "jobs", String() << "Number of concurrent jobs (default: " << nbJobs
			 << ", max: " << cpuCount  << ')');

	// Help
	opts.addParagraph("\nHelp");
	opts.addFlag(verbose, ' ', "verbose", "Print any error message");
	opts.addFlag(debug, ' ', "debug", "Print debug messages");
	opts.addFlag(printVersion, 'v', "version", "Print the version and exit");

	if (!opts(argc, argv))
	{
		int status = opts.errors() ? EXIT_FAILURE /*error*/ : 0;
		if (verbose || debug)
			logs.error() << "Error when parsing the command line";
		exit(status);
		return false;
	}

	if (!input)
	{
		logs.error() << "Please specify an input folder (--input, see --help for more informations)";
		return false;
	}
	if (!htdocs)
	{
		logs.error() << "Please specify a htdocs folder (--htdocs, see --help for more informations)";
		return false;
	}
	{
		String tmp;
		Core::IO::MakeAbsolute(tmp, input);
		Core::IO::Normalize(input, tmp);
		Core::IO::MakeAbsolute(tmp, htdocs);
		Core::IO::Normalize(htdocs, tmp);
	}
	if (!Core::IO::Directory::Exists(input))
	{
		logs.error() << "IO Error: Directory does not exist: " << input;
		return false;
	}
	if (!Core::IO::Directory::Exists(htdocs))
	{
		logs.error() << "IO Error: Directory does not exist: " << htdocs;
		return false;
	}

	nbJobs = Math::MinMax<unsigned int>(nbJobs, 1, cpuCount);
	return true;
}


