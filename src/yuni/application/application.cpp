
#include "application.h"
#include "../core/io/directory.h"



namespace Yuni
{
namespace Application
{


	IApplication::IApplication(int, char* argv[])
		:pTerminated(false), pExitCode(0)
	{
		// Find the absolute folder of the application
		if (Core::IO::IsAbsolute(argv[0]))
			pRootFolder = Core::IO::ExtractFilePath(argv[0]);
		else
		{
			String r;
			Core::IO::Directory::Current::Get(r);
			r << Core::IO::Separator << (const char*) argv[0];
			if (r.notEmpty())
				pRootFolder = Core::IO::ExtractFilePath(r, true);
		}

		// Find The absolution exe name
		if (pRootFolder.empty())
			pExeName += Core::IO::ExtractFileName(argv[0]);
		else
			pExeName += pRootFolder	<< Core::IO::Separator << Core::IO::ExtractFileName(argv[0]);
	}



	void IApplication::arguments(int argc, char** argv)
	{
		GetOpt::Parser parser;
		bool optHelp = false;
		parser.addFlag(optHelp, 'h', "help", "Print this help and exit");

		if (!parser(argc, argv))
		{
			pExitCode = -1;
			pTerminated = true;
			return;
		}

		if (optHelp)
		{
			pTerminated = true;
			parser.helpUsage(argv[0]);
			return;
		}
	}



} // namespace Application
} // namespace Yuni
