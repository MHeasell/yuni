
#include "sleep.h"
#if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
# include "windows.hdr.h"
#else
# include <time.h>
#endif



namespace Yuni
{

    void Sleep(const uint32 milliseconds)
    {
        # if defined(YUNI_OS_WINDOWS) && defined(YUNI_OS_MSVC)
        ::Sleep(milliseconds);
        # else
        nanosleep(milliseconds * 1000);
        # endif
    }


} // namespace Yuni

