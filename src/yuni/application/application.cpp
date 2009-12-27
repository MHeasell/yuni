
#include "application.h"
#include "../core/io/directory.h"



namespace Yuni
{
namespace Application
{


	//! The global instance of the application
	AApplication::Ptr AApplication::pGlobalInstance = NULL;





	AApplication::AApplication(int, char* argv[])
		:pTerminated(false), pExitCode(0)
	{
		// Initializing the global instance
		if (NULL != pGlobalInstance)
			delete pGlobalInstance;
		pGlobalInstance = this;

		// Find the absolute folder of the application
		if (Core::IO::IsAbsolute(argv[0]))
			pRootFolder = Core::IO::ExtractFilePath(argv[0]);
		else
		{
			StringBase<char, 1024> r;
			r << Core::IO::Directory::Current() << Core::IO::Separator << argv[0];
			if (r.notEmpty())
				Core::IO::ExtractFilePath(pRootFolder, r, true);
		}

		// Find The absolution exe name
		if (pRootFolder.empty())
			pExeName += Core::IO::ExtractFileName(argv[0]);
		else
			pExeName += pRootFolder	<< Core::IO::Separator << Core::IO::ExtractFileName(argv[0]);
	}


	AApplication::~AApplication()
	{
		// Detaching the global instance
		pGlobalInstance = NULL;
	}


	void AApplication::arguments(int argc, char** argv)
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
