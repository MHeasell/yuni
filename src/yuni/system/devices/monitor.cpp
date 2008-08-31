
#include "monitor.h"
#include "../../hash/checksum/md5.h"


namespace Yuni
{
namespace System
{
namespace Devices
{
namespace Display
{


	Monitor::Monitor()
		:pHandle(Monitor::InvalidHandle), pName(), pResolutions(),
		pPrimary(false), pHardwareAcceleration(false), pBuiltin(false)
	{}

	Monitor::Monitor(const String& nm, const Monitor::Handle hwn, const bool p, const bool a, const bool b)
		:pHandle(hwn), pName(nm), pResolutions(),
		pPrimary(p), pHardwareAcceleration(a), pBuiltin(b)
	{}

	Monitor::Monitor(const Monitor& c)
		:pHandle(c.pHandle), pName(c.pName), pResolutions(c.pResolutions), pPrimary(c.pPrimary),
		pHardwareAcceleration(c.pHardwareAcceleration), pBuiltin(c.pBuiltin)
	{}


	Monitor::~Monitor()
	{
		pResolutions.clear();
	}


	const String& Monitor::guid()
	{
		// We assume that `pResolutions` is not empty
		if (pMD5Cache.empty())
		{
			Hash::Checksum::MD5 md5;
			pMD5Cache = md5.fromString(String() << pName << "/"
				<< (*pResolutions.begin())->toString()
				<< "/" << pPrimary << "/" << pBuiltin << "/" << pHardwareAcceleration);
		}
		return pMD5Cache;
	}


	void Monitor::addResolution(SharedPtr<Resolution>& r)
	{
		pResolutions.push_back(r);
	}

} // namespace Display
} // namespace Devices
} // namespace System
} // namespace Yuni


