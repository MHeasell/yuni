
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


