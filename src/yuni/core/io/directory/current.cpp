
#include "../io.h"
#include "../directory.h"
#include "../../system/windows.hdr.h"
#ifndef YUNI_OS_WINDOWS
#	include <unistd.h>
#endif




namespace Yuni
{
namespace Core
{
namespace IO
{
namespace Directory
{



	String Current()
	{
		char path[FILENAME_MAX];
		::memset(path, 0, FILENAME_MAX);
		# ifdef YUNI_OS_WINDOWS
		const char* p = _getcwd(path, FILENAME_MAX - 2);
		# else
		const char* p = ::getcwd(path, FILENAME_MAX - 2);
		# endif
		return String(p, ::strlen(p));
	}


	void Current(String& out)
	{
		char path[FILENAME_MAX];
		::memset(path, 0, FILENAME_MAX);
		# ifdef YUNI_OS_WINDOWS
		const char* p = _getcwd(path, FILENAME_MAX - 2);
		# else
		const char* p = ::getcwd(path, FILENAME_MAX - 2);
		# endif
		out.clear();
		out.append(p, ::strlen(p));
	}



} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

