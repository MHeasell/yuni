
#include "monitor.h"
#include "../../toolbox/hash/checksum/md5.h"


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


	void Monitor::addResolution(SmartPtr<Resolution>& r)
	{
		pResolutions.push_back(r);
	}

	
	bool Monitor::resolutionIsValid(const SmartPtr<Resolution>& rhs) const
	{
		if (NULL != rhs) // The pointer must be valid
		{
			// Browse all available resolutions
			// The lookup should be done in the usual way since it is a sorted descendant list
			for (Resolution::Vector::const_iterator it = pResolutions.begin(); it != pResolutions.end(); ++it)
			{
				if (NULL != (*it) && *(*it) == *rhs)
					return true;
			}
		}
		return false;
	}




} // namespace Display
} // namespace Devices
} // namespace System
} // namespace Yuni


