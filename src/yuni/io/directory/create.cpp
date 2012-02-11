
#include "../io.h"
#include "../directory.h"
#include "commons.h"
#include "../file.h"
#ifdef YUNI_OS_WINDOWS
# include "../../core/string/wstring.h"
#endif


namespace Yuni
{
namespace IO
{
namespace Directory
{


	namespace // anonymous
	{


		# ifdef YUNI_OS_WINDOWS

		static bool WindowsMake(const StringAdapter& path)
		{
			unsigned int len = path.size();
			String norm;
			Yuni::IO::Normalize(norm, path, len);

			Private::WString<true> wstr(norm);
			if (wstr.size() < 4)
				return false;
			wchar_t* t = wstr.c_str() + 4;

			while (*t != L'\0')
			{
				if ((*t == L'\\' || *t == L'/') && (*(t-1) != ':'))
				{
					*t = L'\0';
					if (!CreateDirectoryW(wstr.c_str(), nullptr))
					{
						if (GetLastError() != ERROR_ALREADY_EXISTS)
							return false;
					}
					*t = L'\\';
				}
				++t;
			}

			if (!CreateDirectoryW(wstr.c_str(), nullptr))
			{
				if (GetLastError() != ERROR_ALREADY_EXISTS)
					return false;
			}
			return true;
		}


		
		# else



		static bool UnixMake(const StringAdapter& path, unsigned int mode)
		{
			unsigned int len = path.size();

			char* buffer = new char[len + 1];
			memcpy(buffer, path.c_str(), len);
			buffer[len] = '\0';
			char* pt = buffer;
			char tmp;

			while (1)
			{
				if ('\\' == *pt || '/' == *pt || '\0' == *pt)
				{
					tmp = *pt;
					*pt = '\0';
					if ('\0' != buffer[0] && '\0' != buffer[1] && '\0' != buffer[2])
					{
						if (mkdir(buffer, static_cast<mode_t>(mode)) < 0 && errno != EEXIST && errno != EISDIR && errno != ENOSYS)
						{
							delete[] buffer;
							return false;
						}
					}
					if ('\0' == tmp)
						break;
					*pt = tmp;
				}
				++pt;
			}
			delete[] buffer;
			return true;
		}

	# endif

	} // anonymous namespace





	bool Create(const StringAdapter& path, unsigned int mode)
	{
		if (path.notEmpty() && !Yuni::IO::Exists(path))
		{
			# ifdef YUNI_OS_WINDOWS
			// `mode` is not used on Windows
			(void) mode;
			return WindowsMake(path);
			# else
			return UnixMake(path, mode);
			# endif
		}
		return true;
	}





} // namespace Directory
} // namespace IO
} // namespace Yuni

