
#ifdef YUNI_OS_WINDOWS
#  ifndef WIN32_LEAN_AND_MEAN
#	 define WIN32_LEAN_AND_MEAN
#  endif
#  include <windows.h>
#endif // ifdef YUNI_OS_WINDOWS
#include "monitor.h"
#include "../../hash/checksum/md5.h"



namespace Yuni
{
namespace System
{
namespace Devices
{


	String Monitor::guid() const
	{
		String hash;
		hash << pName << " :: ";
		for (Resolution::Vector::const_iterator i = pResolutions.begin(); i != pResolutions.end(); ++i)
			hash << i->width() << "x" << i->height() << "-";
		Hash::Checksum::MD5 md5;
		return md5.fromString(hash);
	}



} // namespace Devices
} // namespace System
} // namespace Yuni


