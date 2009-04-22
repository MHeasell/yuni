
#include "abstract.thread.h"
#if defined(YUNI_OS_DARWIN) || defined(YUNI_OS_FREEBSD)
#	include <sys/param.h>
#	include <sys/sysctl.h>
#endif
#ifdef YUNI_OS_LINUX
#	include <fstream>
#	include "../toolbox/string.h"
#endif
#include "../toolbox/system/windows.hdr.h"





namespace Yuni
{
namespace Threads
{
namespace Private
{



#if defined(YUNI_OS_DARWIN) || defined(YUNI_OS_FREEBSD)
# define YUNI_ATHREADMODEL_CPUCOUNT
	int AThreadModel::CPUCount()
	{
		int count;
		size_t size = sizeof(count);

		if (sysctlbyname("hw.ncpu", &count, &size, NULL, 0))
			return 1;
		return count;
	}
#endif


#ifdef YUNI_OS_WINDOWS
# define YUNI_ATHREADMODEL_CPUCOUNT
	int AThreadModel::CPUCount()
	{
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		return si.dwNumberOfProcessors;
	}
#endif

#ifdef YUNI_OS_LINUX
# define YUNI_ATHREADMODEL_CPUCOUNT
	int AThreadModel::CPUCount()
	{
		/*
		* It seems there's no better way to get this info on Linux systems.
		* If somebody can find it without depending on the location of /proc,
		* please patch this function.
		*/
		int count = 0;
		std::ifstream cpuInfo("/proc/cpuinfo", std::ifstream::in);
		std::string lineBuffer;

		std::getline(cpuInfo, lineBuffer);
		while (cpuInfo.good())
		{
			if (std::string::npos != lineBuffer.find("processor"))
				++count;
			std::getline(cpuInfo, lineBuffer);
		}
		cpuInfo.close();

		return (0 == count ? 1 : count);
	}
#endif




#ifndef YUNI_ATHREADMODEL_CPUCOUNT
#  warning "The method AThreadModel::CPUCount has not been implemented for the current platform"

	int AThreadModel::CPUCount()
	{
		return 1; // Default value
	}

#endif



} // namespace Private
} // namespace Threads
} // namespace Yuni




