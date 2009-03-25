
#include "application.h"
#include "../toolbox/paths.h"



namespace Yuni
{
namespace Application
{


	namespace
	{
		//! The global instance of the application
		AApplication* gApplicationInstance = NULL;

	} // anonymous namespace





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
		if (Toolbox::Paths::IsAbsolute(argv[0]))
			pRootFolder = Toolbox::Paths::ExtractFilePath(argv[0]);
		else
		{
			pRootFolder.clear();
			String r;
			r << Toolbox::Paths::CurrentDirectory() << Toolbox::Paths::Separator << argv[0];
			if (!r.empty())
				pRootFolder = Toolbox::Paths::ExtractFilePath(r);
		}
  
		// Find The absolution exe name
		pExeName.clear();
		if (pRootFolder.empty())
			pExeName = Toolbox::Paths::ExtractFileName(argv[0]);
		else
			pExeName << pRootFolder << Toolbox::Paths::Separator << Toolbox::Paths::ExtractFileName(argv[0]); 

		return false;
	}



} // namespace Application
} // namespace Yuni
