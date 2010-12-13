#include "io.h"
#include "../system/windows.hdr.h"
#ifndef YUNI_OS_WINDOWS
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
#else
#include <sys/stat.h>
#endif
#include "../customstring.h"
#ifdef YUNI_HAS_STRING_H
# include <string.h>
#endif


#ifndef S_ISDIR
#	define S_ISDIR(mode) ( (mode & S_IFMT) == S_IFDIR)
#endif



namespace Yuni
{
namespace Private
{
namespace Core
{
namespace IO
{

	namespace // anonymous
	{
		Yuni::Core::IO::NodeType TypeOfStaticBuffer(const char* p, unsigned int len)
		{
			char path[1024];
			(void)::memcpy(path, p, len * sizeof(char));
			path[len] = '\0';
			return Yuni::Private::Core::IO::TypeOf(path, len);
		}

	} // anonymous namespace


	Yuni::Core::IO::NodeType TypeOfNotZeroTerminated(const char* p, unsigned int len)
	{
		// As this routine may be extensively used, we should make it as fast as possible
		// Consequently we make here a tiny optimisation when the length of the path
		// can be safely contained into a static buffer
		// However, on Windows, we already use temporary buffers
		# ifdef YUNI_OS_WINDOWS
		return Yuni::Private::Core::IO::TypeOf(p, len);
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

			Yuni::Core::IO::NodeType type = Yuni::Private::Core::IO::TypeOf(path, len);
			delete[] path;
			return type;
		}
		# endif
	}


	Yuni::Core::IO::NodeType TypeOf(const char* p, unsigned int len)
	{
		if (!p || !len)
			return Yuni::Core::IO::typeUnknown;

		# ifdef YUNI_OS_WINDOWS
		if (p[len - 1] == '\\' || p[len - 1] == '/')
		{
			if (!--len)
			{
				# ifdef YUNI_OS_WINDOWS
				return Yuni::Core::IO::typeUnknown;
				# else
				// On Unixes, `/` is a valid folder
				return Yuni::Core::IO::typeFolder;
				# endif
			}
		}

		// Driver letters
		if (len == 2 && p[1] == ':')
			return Yuni::Core::IO::typeFolder;

		CustomString<>  norm;
		Yuni::Core::IO::Normalize(norm, p, len);
		// Conversion into wchar_t
		wchar_t* buffer = new wchar_t[norm.size() + 10];
		buffer[0] = L'\\';
		buffer[1] = L'\\';
		buffer[2] = L'?';
		buffer[3] = L'\\';
		int n = MultiByteToWideChar(CP_UTF8, 0, norm.c_str(), norm.size(), buffer + 4, norm.size());
		if (n <= 0)
		{
			delete[] buffer;
			return Yuni::Core::IO::typeUnknown;
		}
		for (int i = 4; i < n + 4; ++i)
		{
			if (buffer[i] == '/')
				buffer[i] = '\\';
		}
		buffer[n + 4] = L'\0';

		WIN32_FILE_ATTRIBUTE_DATA infoFile;
		if (!GetFileAttributesExW(buffer, GetFileExInfoStandard, &infoFile))
		{
			delete[] buffer;
			return Yuni::Core::IO::typeUnknown;
		}
		delete[] buffer;

		return ((infoFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
			? Yuni::Core::IO::typeFolder
			: Yuni::Core::IO::typeFile;

		# else // WINDOWS

		struct stat s;
		if (stat(p, &s) != 0)
			return Yuni::Core::IO::typeUnknown;

		return (S_ISDIR(s.st_mode))
			? Yuni::Core::IO::typeFolder
			: Yuni::Core::IO::typeFile;
		# endif
	}




} // namespace IO
} // namespace Core
} // namespace Private
} // namespace Yuni
