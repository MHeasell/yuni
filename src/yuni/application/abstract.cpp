
#include <yuni/application/abstract.h>
#include <yuni/paths.h>


namespace Yuni
{
namespace Application
{

    namespace
    {
        //! The global instance of the application
        Abstract* gApplicationInstance = NULL;

    } // anonymous namespace

    Abstract* Abstract::Instance()
    {
        return gApplicationInstance;
    }

    Abstract::Abstract(int argc, char* argv[])
        :pTerminated(false), pExeName(), pRootFolder()
    {
        if (NULL != gApplicationInstance)
            delete gApplicationInstance;
        gApplicationInstance = this;
        pTerminated = parseCommandLine(argc, argv);
    }

    Abstract::~Abstract()
    {
        gApplicationInstance = NULL;
    }


    bool Abstract::parseCommandLine(int /*argc*/, char* argv[])
    {
        // Find the absolute folder of the application
        if (Paths::IsAbsolute(argv[0]))
            pRootFolder = Paths::ExtractFilePath(argv[0]);
        else
        {
            pRootFolder.clear();
            String r;
            r << Paths::CurrentDirectory() << Paths::Separator << argv[0];
            if (!r.empty())
                pRootFolder = Paths::ExtractFilePath(r);
        }
   
        // Find The absolution exe name
        pExeName.clear();
        if (pRootFolder.empty())
            pExeName = Paths::ExtractFileName(argv[0]);
        else
            pExeName << pRootFolder << Paths::Separator << Paths::ExtractFileName(argv[0]); 

        return false;
    }

} // namespace Application
} // namespace Yuni


