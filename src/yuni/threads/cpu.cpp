
#include <yuni/threads/abstract.thread.h>
#ifdef YUNI_OS_DARWIN
#   include <sys/param.h>
#   include <sys/sysctl.h>
#endif
#ifdef YUNI_OS_LINUX
#	include <fstream>
#   include <string>
#   include <yuni/misc/string.h>
#endif





namespace Yuni
{
namespace Threads
{
namespace Private
{



#ifdef YUNI_OS_DARWIN
# define YUNI_ABSTRACTTHREADMODEL_CPUCOUNT
	int AbstractThreadModel::CPUCount()
	{
		int count;
		size_t size = sizeof(count);

		if (sysctlbyname("hw.ncpu", &count, &size, NULL, 0))
			return 1;
		return count;
	}
#endif


#ifdef YUNI_OS_WINDOWS
# define YUNI_ABSTRACTTHREADMODEL_CPUCOUNT
	int AbstractThreadModel::CPUCount()
	{
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		return si.dwNumberOfProcessors;
	}
#endif

#ifdef YUNI_OS_LINUX
# define YUNI_ABSTRACTTHREADMODEL_CPUCOUNT
	int AbstractThreadModel::CPUCount()
	{
		/*
		 * It seems there's no better way to get this info on Linux systems.
		 * If somebody can find it without depending on the location of /proc,
		 * please patch this function.
		 */
		int count = 0;
		std::ifstream cpuInfo("/proc/cpuinfo", std::ifstream::in);
		String lineBuffer;

		std::getline(cpuInfo, lineBuffer);
		while (cpuInfo.good())
		{
			if (std::string::npos != lineBuffer.find("processor"))
				count++;
			std::getline(cpuInfo, lineBuffer);
		}
		cpuInfo.close();

		return (0 == count ? 1 : count);
	}
#endif



} // namespace Private
} // namespace Threads
} // namespace Yuni




#ifndef YUNI_ABSTRACTTHREADMODEL_CPUCOUNT
#  error "The method AbstractThreadModel::CPUCount has not been implemented for the current platform"
#endif


