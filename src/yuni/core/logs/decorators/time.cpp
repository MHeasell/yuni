
#include <time.h>
#include "time.h"



namespace Yuni
{
namespace Private
{
namespace LogsDecorator
{


	void WriteCurrentTimestampToBuffer(char* buffer)
	{
		time_t rawtime;
		::time (&rawtime);

		struct tm timeinfo;

		# ifdef YUNI_OS_WINDOWS
		::localtime_s(&timeinfo, &rawtime);
		::asctime_s(buffer, &timeinfo);
		# else
		::localtime_r(&rawtime, &timeinfo);
		::asctime_r(&timeinfo, buffer);
		# endif
	}



} // namespace LogsDecorator
} // namespace Private
} // namespace Yuni


