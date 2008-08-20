
#include <yuni/application/abstract.h>


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


    bool Abstract::parseCommandLine(int /*argc*/, char* /*argv*/[])
    {
        return false;
    }

} // namespace Application
} // namespace Yuni


