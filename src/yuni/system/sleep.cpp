
#include "sleep.h"
#if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
# include "windows.hdr.h"
#else
# include <unistd.h>
#endif



namespace Yuni
{

    void Sleep(const uint32 seconds)
    {
        # if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
        ::Sleep(1000 * seconds);
        # else
        sleep(seconds);
        # endif
    }


} // namespace Yuni

