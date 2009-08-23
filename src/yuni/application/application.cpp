
#include "application.h"
#include "../core/io/directory.h"



namespace Yuni
{
namespace Application
{


	//! The global instance of the application
	static AApplication* gApplicationInstance = NULL;





	AApplication* AApplication::Instance()
	{
		return gApplicationInstance;
	}


	AApplication::AApplication(int argc, char* argv[])
		:pTerminated(false), pExeName(), pRootFolder()
	{
		if (NULL != gApplicationInstance)
			delete gApplicationInstance;
		gApplicationInstance = this;
		pTerminated = parseCommandLine(argc, argv);
	}


	AApplication::~AApplication()
	{
		gApplicationInstance = NULL;
	}


	bool AApplication::parseCommandLine(int /*argc*/, char* argv[])
	{
		// Find the absolute folder of the application
		if (Core::IO::IsAbsolute(argv[0]))
			pRootFolder = Core::IO::ExtractFilePath(argv[0]);
		else
		{
			pRootFolder.clear();
			String r;
			r << Core::IO::Directory::Current() << Core::IO::Separator << argv[0];
			if (!r.empty())
				pRootFolder.append(Core::IO::ExtractFilePath(r, true));
		}

		// Find The absolution exe name
		pExeName.clear();
		if (pRootFolder.empty())
			pExeName.append(Core::IO::ExtractFileName(argv[0]));
		else
			pExeName << pRootFolder	<< Core::IO::Separator << Core::IO::ExtractFileName(argv[0]);
		return false;
	}



} // namespace Application
} // namespace Yuni
