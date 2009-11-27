
#include "openmode.h"


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace File
{
namespace OpenMode
{


	const char* ToCString(const int mode)
	{
		if (mode == OpenMode::append)
			// Shortcut for write|append
			return "a";
		if (mode == OpenMode::truncate)
			// Shortcut for write|append
			return "w";

		if (mode & OpenMode::write)
		{
			if (0 == (mode & OpenMode::read))
			{
				if (mode & OpenMode::truncate)
					return "w";
				if (mode & OpenMode::append)
					return "a";
			}
			else
			{
				if (mode & OpenMode::truncate)
					return "w+";
				if (mode & OpenMode::append)
					return "a+";
				return "r+";
			}
			return "w";
		}
		return (mode & OpenMode::read) ? "r" : "";
	}



	const wchar_t*  ToWCString(const int mode)
	{
		if (mode == OpenMode::append)
			// Shortcut for write|append
			return L"a";
		if (mode == OpenMode::truncate)
			// Shortcut for write|append
			return L"w";

		if (mode & OpenMode::write)
		{
			if (!(mode & OpenMode::read))
			{
				if (mode & OpenMode::truncate)
					return L"w";
				if (mode & OpenMode::append)
					return L"a";
			}
			else
			{
				if (mode & OpenMode::truncate)
					return L"w+";
				if (mode & OpenMode::append)
					return L"a+";
				return L"r+";
			}
			return L"w";
		}
		return (mode & OpenMode::read) ? L"r" : L"";
	}




} // namespace OpenMode
} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

