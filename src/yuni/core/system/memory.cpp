
// memory.h: The relative path is to avoid conflict with <memory.h>, which
// can sometimes occur...
#include "../system/memory.h"

// The define SYSTEM_MEMORY_IS_IMPLEMENTED will be used to know if
// a valid implementation is available.
// Otherwise we will use some fallbacks and generate a compiler warning


#ifdef YUNI_OS_WINDOWS
# include "windows.hdr.h"
#endif

#ifdef YUNI_OS_LINUX
# include <sys/sysinfo.h> // sysinfo (2)
#endif

#ifdef YUNI_OS_MAC
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <mach/mach.h>
#endif

#include <stdio.h>
#include <stdlib.h>




namespace Yuni
{
namespace System
{
namespace Memory
{


#ifdef YUNI_OS_WINDOWS
#define SYSTEM_MEMORY_IS_IMPLEMENTED

	size_t Total()
	{
		// see http://msdn.microsoft.com/en-us/library/aa366589(VS.85).aspx
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof(statex);
		return (GlobalMemoryStatusEx(&statex)) ? (size_t)statex.ullTotalPhys
			: (size_t)defaultTotal;
	}

	size_t Available()
	{
		// see http://msdn.microsoft.com/en-us/library/aa366589(VS.85).aspx
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof(statex);
		return (GlobalMemoryStatusEx(&statex)) ? (size_t)statex.ullAvailPhys
			: (size_t)defaultAvailable;
	}

	bool Usage::update()
	{
		// see http://msdn.microsoft.com/en-us/library/aa366589(VS.85).aspx
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof(statex);

		if (GlobalMemoryStatusEx(&statex))
		{
			total = (size_t)statex.ullTotalPhys;
			available = (size_t)statex.ullAvailPhys;
			return true;
		}
		available = defaultAvailable;
		total = defaultTotal;
		return false;
	}

#endif // YUNI_OS_WINDOWS






#ifdef YUNI_OS_LINUX
#define SYSTEM_MEMORY_IS_IMPLEMENTED

	/*!
	** \brief Read a line from a file
	*/
	static int fgetline(FILE* fp, char* s, int maxlen)
	{
		int i = 0;
		char c;

		while ((c = fgetc(fp)) != EOF)
		{
			if (c == '\n')
			{
				*s = '\0';
				return i;
			}
			if (i >= maxlen)
				return i;

			*s++ = c;
			++i;
		}

		return (!i) ? EOF : i;
	}


	static size_t readvalue(char* line)
	{
		// Here is a sample for /proc/meminfo :
		//
		// MemTotal:      1929228 kB
		// MemFree:         12732 kB
		// Buffers:         72176 kB
		// Cached:        1076572 kB
		// SwapCached:     151412 kB
		// Active:        1491184 kB
		// Inactive:       190832 kB
		// HighTotal:           0 kB
		// HighFree:            0 kB
		// LowTotal:      1929228 kB
		// LowFree:         12732 kB
		// SwapTotal:     2096472 kB
		// SwapFree:      1732964 kB
		// Dirty:             736 kB
		// Writeback:           0 kB
		// AnonPages:      512004 kB
		// Mapped:         702148 kB
		// Slab:           154320 kB
		// PageTables:      34712 kB
		// NFS_Unstable:        0 kB
		// Bounce:              0 kB
		// CommitLimit:   3061084 kB
		// Committed_AS:  1357596 kB
		// VmallocTotal: 34359738367 kB
		// VmallocUsed:    263492 kB
		// VmallocChunk: 34359474679 kB
		// HugePages_Total:     0
		// HugePages_Free:      0
		// HugePages_Rsvd:      0
		// Hugepagesize:     2048 kB

		// Trimming the string from the begining
		while (*line == ' ' && *line != '\0')
			++line;
		const char* first = line;

		// Looking for the end of the number
		while (*line != ' ' && *line != '\0')
			++line;
		// Tagging the end of the number
		*line = '\0';

		# ifdef YUNI_OS_32
		return (size_t) atol(first) * 1024u;
		# else
		return (size_t) atoll(first) * 1024u;
		# endif
	}


	bool Usage::update()
	{
		// The only good way to retrieve the memory usage is to read /proc/meminfo.
		// The routine sysinfo (2) is not enough since it does not take care of
		// the cache memory, returning a not valid amount of available physsical
		// memory for our uses.
		FILE* fd;
		if ((fd = fopen("/proc/meminfo", "r")))
		{
			// Resetting the amount of the total physical memory
			total = 0;
			// The amount of the available physical memory is the sum of 3 values :
			// MemFree, Cached and Buffers.
			available = 0;

			// A small buffer
			char line[90];
			// A counter to reduce to abort as soon as we have read all
			int remains = 8;

			// Analysing each line in /proc/meminfo, until the end-of-file or
			// until we have read the 4 values that interrest us.
			while (EOF != fgetline(fd, line, sizeof(line)))
			{
				if (!strncmp("MemTotal:", line, 9))
				{
					total = readvalue(line + 10);
					if (!(remains >> 1))
						break;
				}
				if (!strncmp("MemFree:", line, 8))
				{
					available += readvalue(line + 9);
					if (!(remains >> 1))
						break;
				}
				if (!strncmp("Cached:", line, 7))
				{
					available += readvalue(line + 8);
					if (!(remains >> 1))
						break;
				}
				if (!strncmp("Buffers:", line, 8))
				{
					available += readvalue(line + 9);
					if (!(remains >> 1))
						break;
				}
			}

			// Closing /proc/meminfo
			fclose(fd);

			// Checking the amount of the total physical memory, which can not be equal to 0
			if (!total)
			{
				total = (size_t) defaultTotal;
				return false;
			}
			return true;
		}

		// Error, using default values
		total     = (size_t) defaultTotal;
		available = (size_t) defaultAvailable;
		return false;
	}

	size_t Available()
	{
		return Usage().available;
	}

	size_t Total()
	{
		// Directly using sysinfo (2), which should be faster than parsing /proc/meminfo
		struct sysinfo s;
		return (!sysinfo(&s)) ? (s.mem_unit * s.totalram) : (size_t) defaultTotal;
	}

#endif // YUNI_OS_LINUX



#ifdef YUNI_OS_MAC
#define SYSTEM_MEMORY_IS_IMPLEMENTED

	size_t Total()
	{
		int mib[2] = {CTL_HW, HW_MEMSIZE};
		uint64 memory;
		size_t len = sizeof(uint64);
		return (!sysctl(mib, 2, &memory, &len, NULL, 0)) ? memory : (size_t) defaultTotal;
	}

	size_t Available()
	{
		// Good readings :)
		// http://www.booktou.com/node/148/0321278542/ch06lev1sec3.html

		// Host
		host_name_port_t host = mach_host_self();
		// Statistics about the VM
		vm_statistics_data_t vm_stat;
		mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
		host_statistics(host, HOST_VM_INFO, (host_info_t) &vm_stat, &count);
		// A page size
		vm_size_t  page_size;
		host_page_size(host, &page_size);

		return (size_t) (vm_stat.free_count) * (size_t) page_size;
	}

	bool Usage::update()
	{
		// Available
		available = Available();

		// Total
		int mib[2] = {CTL_HW, HW_MEMSIZE};
		size_t len = sizeof(uint64);
		if (sysctl(mib, 2, &total, &len, NULL, 0))
		{
			total = (size_t) defaultTotal;
			return false;
		}
		return true;
	}

#endif // YUNI_OS_MAC








#ifndef SYSTEM_MEMORY_IS_IMPLEMENTED
#warning Yuni::System::Memory: The implementation is missing for this operating system

	size_t Total()
	{
		return defaultTotal;
	}

	size_t Available()
	{
		return defaultAvailable;
	}

	bool Usage::update()
	{
		available = defaultAvailable;
		total     = defaultTotal;
		return false;
	}

#endif // Fallback



} // namespace Memory
} // namespace System
} // namespace Yuni


