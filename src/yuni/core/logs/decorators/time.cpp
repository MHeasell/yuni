
#include "../../system/windows.hdr.h"
#include <time.h>
#include "time.h"



namespace Yuni
{
namespace Private
{
namespace LogsDecorator
{

    # ifdef YUNI_OS_MINGW
	
    char* WriteCurrentTimestampToBufferMinGW()
	{
		time_t rawtime;
		::time(&rawtime);

        /* MinGW */
        // Note that unlike on (all?) POSIX systems, in the Microsoft
        // C library locatime() and gmtime() are multi-thread-safe, as the
        // returned pointer points to a thread-local variable. So there is no
        // need for localtime_r() and gmtime_r().
		return ::asctime(::localtime(&rawtime));
	}
    
    # else

	void WriteCurrentTimestampToBuffer(char* buffer)
	{
		time_t rawtime;
		::time(&rawtime);
		struct tm timeinfo;

		# if defined(YUNI_OS_MSVC)
        /* Microsoft Visual Studio */
		::localtime_s(&timeinfo, &rawtime);
		::asctime_s(buffer, &timeinfo);
		# else
        /* Unixes */
        ::localtime_r(&rawtime, &timeinfo);
		::asctime_r(&timeinfo, buffer);
		# endif
	}

    # endif


} // namespace LogsDecorator
} // namespace Private
} // namespace Yuni


