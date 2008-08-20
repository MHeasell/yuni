
#include <yuni/application/console.h>


namespace Yuni
{
namespace Application
{

    Console& Console::Instance()
    {
        return *(dynamic_cast<Console*>(Abstract::Instance()));
    }

    Console::Console(int argc, char* argv[])
        :Abstract(argc, argv)
    {}

    Console::~Console()
    {}


} // namespace Application
} // namespace Yuni


