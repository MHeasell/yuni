#include "io.h"
#include "../core/system/windows.hdr.h"
#include "../core/string.h"
#include "../core/string/wstring.h"
#include <sys/stat.h>

#ifndef YUNI_OS_WINDOWS
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
#endif

#ifdef YUNI_HAS_STRING_H
# include <string.h>
#endif


#ifndef S_ISDIR
# define S_ISDIR(mode) ( (mode & S_IFMT) == S_IFDIR)
#endif



namespace Yuni
{
namespace Private
{
namespace IO
{

	namespace // anonymous
	{
		Yuni::IO::NodeType TypeOfStaticBuffer(const char* p, unsigned int len)
		{
			char path[1024];
			(void)::memcpy(path, p, len * sizeof(char));
			path[len] = '\0';
			return Yuni::Private::IO::TypeOf(path, len);
		}

	} // anonymous namespace



	Yuni::IO::NodeType TypeOfNotZeroTerminated(const char* p, unsigned int len)
	{
		// As this routine may be extensively used, we should make it as fast as possible
		// Consequently we make here a tiny optimisation when the length of the path
		// can be safely contained into a static buffer
		// However, on Windows, we already use temporary buffers
		# ifdef YUNI_OS_WINDOWS
		return Yuni::Private::IO::TypeOf(p, len);
		# else
		if (len < 1020)
		{
			return TypeOfStaticBuffer(p, len);
		}
		else
		{
			char* path = new char[len + 1];
			memcpy(path, p, len * sizeof(char));
			path[len] = '\0';

			Yuni::IO::NodeType type = Yuni::Private::IO::TypeOf(path, len);
			delete[] path;
			return type;
		}
		# endif
	}


	Yuni::IO::NodeType TypeOf(const char* p, unsigned int len)
	{
		if (!p || !len)
			return Yuni::IO::typeUnknown;

		# ifdef YUNI_OS_WINDOWS
		if (p[len - 1] == '\\' || p[len - 1] == '/')
		{
			if (!--len)
			{
				# ifdef YUNI_OS_WINDOWS
				return Yuni::IO::typeUnknown;
				# else
				// On Unixes, `/` is a valid folder
				return Yuni::IO::typeFolder;
				# endif
			}
		}

		// Driver letters
		if (len == 2 && p[1] == ':')
			return Yuni::IO::typeFolder;

		String  norm;
		Yuni::IO::Normalize(norm, p, len);
		// Conversion into wchar_t
		WString<true> wstr(norm);
		if (wstr.empty())
			return Yuni::IO::typeUnknown;

		WIN32_FILE_ATTRIBUTE_DATA infoFile;
		if (!GetFileAttributesExW(wstr.c_str(), GetFileExInfoStandard, &infoFile))
			return Yuni::IO::typeUnknown;

		return ((infoFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			? Yuni::IO::typeFolder
			: Yuni::IO::typeFile;

		# else // WINDOWS

		struct stat s;
		if (stat(p, &s) != 0)
			return Yuni::IO::typeUnknown;

		return (S_ISDIR(s.st_mode))
			? Yuni::IO::typeFolder
			: Yuni::IO::typeFile;
		# endif
	}




} // namespace IO
} // namespace Private
} // namespace Yuni
