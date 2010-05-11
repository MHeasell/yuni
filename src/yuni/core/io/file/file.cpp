
#include <sys/stat.h>
#include "../file.h"
#include "../directory.h"
#include <ctype.h>



namespace Yuni
{
namespace Private
{
namespace IO
{
namespace FilesystemImpl
{


	# ifdef YUNI_OS_WINDOWS

	bool Size(const char* const filename, unsigned int len, uint64& value)
	{
		if (!len)
		{
			value = 0;
			return false;
		}

		const char* const p = filename;

		if (p[len - 1] == '\\' || p[len - 1] == '/')
			--len;

		// Driver letters
		if (len == 2 && p[1] == ':')
		{
			value = 0;
			return true;
		}

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
			value = 0;
			delete[] buffer;
			return false;
		}
		for (int i = 4; i < n + 4; ++i)
		{
			if (buffer[i] == '/')
				buffer[i] = '\\';
		}
		buffer[n + 4] = L'\0';

		HANDLE hndl = CreateFileW(buffer, 0, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		delete[] buffer;
		if (hndl == INVALID_HANDLE_VALUE)
		{
			value = 0;
			return false;
		}
		LARGE_INTEGER v;
		if (!GetFileSizeEx(hndl, &v))
		{
			CloseHandle(hndl);
			value = 0;
			return false;
		}
		value = (uint64) v.QuadPart;

		CloseHandle(hndl);
		return true;
	}

	# else

	bool Size(const char* const filename, unsigned int len, uint64& value)
	{
		struct stat results;
		if (filename && '\0' != *filename && stat(filename, &results) == 0)
		{
			value = results.st_size;
			return true;
		}
		value = 0;
		return false;
	}

	# endif



} // namespace FilesystemImpl
} // namespace IO
} // namespace Private
} // namespace Yuni


