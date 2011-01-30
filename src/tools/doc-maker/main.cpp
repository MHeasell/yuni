
#include <yuni/yuni.h>
#ifndef YUNI_NO_THREAD_SAFE
#	define YUNI_NO_THREAD_SAFE // disabling thread-safety
#endif
#include <yuni/core/getopt.h>

using namespace Yuni;


class Options
{
public:
	void parseCommandLine(int argc, char** argv)
	{
		// The Command line parser
		GetOpt::Parser opts;

		// Compiler
		opts.addParagraph("\nOptions:");
		opts.add(input, ' ', "input", "Source folder");
		opts.add(htdocs, ' ', "htdocs", "htdocs folder");

		// Help
		opts.addParagraph("\nHelp");
		opts.addFlag(verbose, ' ', "verbose", "Print any error message");
		opts.addFlag(debug, ' ', "debug", "Print debug messages");
		opts.addFlag(printVersion, 'v', "version", "Print the version and exit");

		if (!opts(argc, argv))
		{
			int status = opts.errors() ? 1 /*error*/ : 0;
			if (verbose || debug)
				std::cout << "Error when parsing the command line\n";
			exit(status);
			return;
		}
	}

public:
	String input;
	String htdocs;
	bool printVersion;
	bool debug;
	bool verbose;

}; // class Options


int main(int argc, char** argv)
{
	Options options;
	options.parseCommandLine(argc, argv);
	return 0;
}

