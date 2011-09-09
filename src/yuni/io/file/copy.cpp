
#include "../file.h"
#if defined(YUNI_OS_LINUX) && defined(YUNI_HAS_SYS_SENDFILE_H)
# include <sys/sendfile.h>
#endif
#include <sys/stat.h>



namespace Yuni
{
namespace IO
{
namespace File
{


	Error Copy(const StringAdapter& from, const StringAdapter& to, bool overwrite)
	{
		if (!overwrite && IO::Exists(to))
			return errOverwriteNotAllowed;

		// Open the source file
		Yuni::IO::File::Stream fromFile;
		if (fromFile.open(from))
		{
			Yuni::IO::File::Stream toFile;
			if (toFile.openRW(to))
			{
				enum { size = 8192 };

				# if defined(YUNI_OS_LINUX) && defined(YUNI_HAS_SYS_SENDFILE_H)
				const int fdIN  = fileno(fromFile. nativeHandle());
				const int fdOUT = fileno(toFile.   nativeHandle());

				// Trying sendfile first
				struct stat st;
				if (!fstat(fdIN, &st))
				{
					off_t offset = 0;
					if (-1 != sendfile(fdOUT, fdIN, &offset, (size_t) st.st_size))
						return Yuni::IO::errNone;
				}

				// fallback to the standard copy
				char* buffer = new char[size];
				size_t numRead;

				while ((numRead = read(fdIN, buffer, size)) > 0)
					(void)::write(fdOUT, buffer, numRead);

				delete[] buffer;
				return Yuni::IO::errNone;

				# else

				// Generic implementation
				char* buffer = new char[size];
				size_t numRead;
				while ((numRead = fromFile.read(buffer, size)) != 0)
					toFile.write(buffer, numRead);
				delete[] buffer;
				return Yuni::IO::errNone;

				# endif

			}
		}
		return errNotFound;
	}




} // namespace File
} // namespace IO
} // namespace Yuni