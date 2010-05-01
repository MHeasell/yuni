
#include "iterator.h"

#ifdef YUNI_OS_WINDOWS
# include "../../../system/windows.hdr.h"
# include <wchar.h>
# include <io.h>
#else
# include <errno.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
#endif

namespace Yuni
{
namespace Private
{
namespace Core
{
namespace IO
{
namespace Directory
{
namespace Iterator
{


	enum
	{
		pollingInterval = 5,
	};


# ifndef YUNI_OS_WINDOWS

	Flow TraverseUnixFolder(const String& filename, Options& opts, IDetachedThread* thread)
	{
		// Opening the folder
		DIR* pdir = opendir(filename.c_str());
		if (!pdir)
			return opts.self->onError(filename);

		struct dirent *pent;
		struct stat s;
		String newName;
		String newFilename;

		// iterating trough files and folders
		while ((pent = readdir(pdir)))
		{
			// Checking from time to time if the thread should stop
			if (thread && ++opts.counter == pollingInterval) // arbitrary value
			{
				// reset counter
				opts.counter = 0;
				if (thread->suspend())
					return Yuni::Core::IO::flowAbort;
			}

			// Avoid `.` and `..`
			if (*(pent->d_name) == '.')
			{
				if ((pent->d_name[1] == '.' && pent->d_name[2] == '\0') || (pent->d_name[1] == '\0'))
					continue;
			}

			newName = (const char*) pent->d_name;
			newFilename.clear();
			newFilename << filename << Yuni::Core::IO::Separator << newName;
			if (stat(newFilename.c_str(), &s) != 0)
			{
				if (opts.self->onAccessError(newFilename) == Yuni::Core::IO::flowAbort)
					return Yuni::Core::IO::flowAbort;
				continue;
			}

			if (S_ISDIR(s.st_mode))
			{
				// The node is a folder
				switch (opts.self->onBeginFolder(newFilename, filename, newName))
				{
					case Yuni::Core::IO::flowContinue:
						{
							if (Yuni::Core::IO::flowAbort == TraverseUnixFolder(newFilename, opts, thread))
							{
								opts.self->onEndFolder(newFilename, filename, newName);
								return Yuni::Core::IO::flowAbort;
							}
							opts.self->onEndFolder(newFilename, filename, newName);
							break;
						}
					case Yuni::Core::IO::flowAbort:
						return Yuni::Core::IO::flowAbort;
					case Yuni::Core::IO::flowSkip:
						break;
				}
			}
			else
			{
				// The node is a file
				if (Yuni::Core::IO::flowAbort == opts.self->onFile(newFilename, filename, newName, s.st_size))
					return Yuni::Core::IO::flowAbort;
			}
		}
		closedir(pdir);
		return Yuni::Core::IO::flowContinue;
	}


# else

	Flow TraverseWindowsFolder(const String& filename, Options& opts, IDetachedThread* thread)
	{
		struct _wfinddatai64_t data;

		// Convertir the filename
		opts.wbuffer[0] = L'\\';
		opts.wbuffer[1] = L'\\';
		opts.wbuffer[2] = L'?';
		opts.wbuffer[3] = L'\\';
		int n = MultiByteToWideChar(CP_UTF8, 0, filename.c_str(), filename.size(), opts.wbuffer + 4, 4080);
		if (!n)
			return opts.self->onError(filename);
		// Making sure that our string is zero-terminated
		opts.wbuffer[n + 4] = L'\\';
		opts.wbuffer[n + 5] = L'*';
		opts.wbuffer[n + 6] = L'.';
		opts.wbuffer[n + 7] = L'*';
		opts.wbuffer[n + 8] = L'\0';

		// Opening the folder
		long h = _wfindfirsti64(opts.wbuffer, &data);
		if (h < 0)
			return Yuni::Core::IO::flowContinue;

		String newName;
		String newFilename;

		// iterating trough files and folders
		do
		{
			// Checking from time to time if the thread should stop
			if (thread && ++opts.counter == pollingInterval) // arbitrary value
			{
				// reset counter
				opts.counter = 0;
				if (thread->suspend())
					return Yuni::Core::IO::flowAbort;
			}

			// Avoid `.` and `..`
			if (*(data.name) == L'.')
			{
				if ((data.name[1] == L'.' && data.name[2] == L'\0') || (data.name[1] == L'\0'))
					continue;
			}

			const size_t sizeRequired = WideCharToMultiByte(CP_UTF8, 0, data.name, -1, NULL, 0,  NULL, NULL);
			if (!sizeRequired)
				continue;
			newName.reserve(sizeRequired);
			WideCharToMultiByte(CP_UTF8, 0, data.name, -1, (char*)newName.data(), sizeRequired,  NULL, NULL);
			newName.resize(sizeRequired - 1);

			newFilename.clear();
			newFilename << filename << '\\' << newName;

			if( (data.attrib & _A_SUBDIR) )
			{
				// The node is a folder
				switch (opts.self->onBeginFolder(newFilename, filename, newName))
				{
					case Yuni::Core::IO::flowContinue:
						{
							if (Yuni::Core::IO::flowAbort == TraverseWindowsFolder(newFilename, opts, thread))
							{
								opts.self->onEndFolder(newFilename, filename, newName);
								return Yuni::Core::IO::flowAbort;
							}
							opts.self->onEndFolder(newFilename, filename, newName);
							break;
						}
					case Yuni::Core::IO::flowAbort:
						return Yuni::Core::IO::flowAbort;
					case Yuni::Core::IO::flowSkip:
						break;
				}
			}
			else
			{
				// The node is a file
				if (Yuni::Core::IO::flowAbort == opts.self->onFile(newFilename, filename, newName, (size_t)data.size))
					return Yuni::Core::IO::flowAbort;
			}
		} while (_wfindnexti64(h, &data) == 0);
		_findclose(h);

		return Yuni::Core::IO::flowContinue;
	}
# endif // ifndef YUNI_OS_WINDOWS











	void Traverse(Options& options, IDetachedThread* thread)
	{
		if (options.rootFolder.empty())
			return;
		# ifdef YUNI_OS_WINDOWS
		options.wbuffer = new wchar_t[4096];
		# endif

		String::VectorPtr::const_iterator end = options.rootFolder.end();
		for (String::VectorPtr::const_iterator i = options.rootFolder.begin(); i != end; ++i)
		{
			const String& path = *(*i);

			// This routine can only be called if the parameter is not empty
			if (path.empty() || !options.self->onStart(path))
				continue;

			// Making sure that the counter is properly initialized
			options.counter = 0;

			# ifdef YUNI_OS_WINDOWS
			const Flow result = TraverseWindowsFolder(path, options, thread);
			# else
			const Flow result = TraverseUnixFolder(path, options, thread);
			# endif

			if ((result == Yuni::Core::IO::flowAbort) || (thread && thread->suspend()))
			{
				# ifdef YUNI_OS_WINDOWS
				delete[] options.wbuffer;
				# endif
				options.self->onAbort();
				return;
			}
		}

		// Final events
		options.self->onTerminate();

		# ifdef YUNI_OS_WINDOWS
		delete[] options.wbuffer;
		# endif
	}





} // namespace Iterator
} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Private
} // namespace Yuni

