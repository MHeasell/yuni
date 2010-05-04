
#include <sys/stat.h>
#include "../file.h"
#include "../directory.h"
#include <ctype.h>



namespace Yuni
{
namespace Private
{
namespace IO
{
namespace FilesystemImpl
{

	bool CopyFile(const char* from, const char* to)
	{
		// Open the source file
		Yuni::Core::IO::File::Stream fromFile(from, Yuni::Core::IO::File::OpenMode::read);
		if (fromFile.opened())
		{
			Yuni::Core::IO::File::Stream toFile(to,
				Yuni::Core::IO::File::OpenMode::write | Yuni::Core::IO::File::OpenMode::truncate);
			if (toFile.opened())
			{
				char buffer[4096];
				size_t numRead;
				while ((numRead = fromFile.read(buffer, sizeof(buffer))))
					toFile.write(buffer, numRead);
			}
		}
		return false;
	}


	bool Size(const char* filename, uint64& value)
	{
		struct stat results;
		if (filename && '\0' != *filename && stat(filename, &results) == 0)
		{
			value = results.st_size;
			return true;
		}
		value = 0;
		return false;
	}


	uint64 Size(const char* filename)
	{
		struct stat results;
		if (filename && '\0' != *filename && stat(filename, &results) == 0)
			return results.st_size;
		return 0;
	}



} // namespace FilesystemImpl
} // namespace IO
} // namespace Private
} // namespace Yuni


