#ifndef __YUNI_CORE_IO_DIRECTORY_SYSTEM_HXX__
# define __YUNI_CORE_IO_DIRECTORY_SYSTEM_HXX__

# include "../../../core/system/environment.h"


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace Directory
{
namespace System
{


	template<StringT>
	bool Temporary(StringT& out, bool emptyBefore = true)
	{
		if (emptyBefore)
			out.clear();
		# ifdef YUNI_OS_WINDOWS
		if (!System::Environment::Read("TEMP", out, false))
		{
			if (!System::Environment::Read("TMP", out, false))
				return false;
		}
		# else
		if (!System::Environment::Read("TMPDIR", out, false))
		{
			if (!System::Environment::Read("TMP", out, false))
			{
				if (!System::Environment::Read("TEMP", out, false))
					return false;
			}
		}
		# endif

		return true;
	}



	template<StringT>
	bool UserHome(StringT& out, bool emptyBefore)
	{
		if (emptyBefore)
			out.clear();

		# ifdef YUNI_OS_WINDOWS
		System::Environment::Read("HOMEDRIVE", out, false);
		return System::Environment::Read("HOMEPATH", out, false);
		# else
		return System::Environment::Read("HOME", out, false);
		# endif
	}






} // namespace System
} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

# include "system.hxx"

#endif // __YUNI_CORE_IO_DIRECTORY_HXX__
