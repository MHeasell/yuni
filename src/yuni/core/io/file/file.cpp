
#include <sys/stat.h>
#include "../file.h"
#include "../directory.h"
#include <ctype.h>



namespace Yuni
{
namespace Core
{
namespace IO
{
namespace File
{




	String ReplaceExtension(const String& filename, const String& newExt)
	{
		if (filename.empty())
			return String();
		const String::size_type p = filename.find_last_of('.');
		if (p == String::npos)
			return filename + newExt;
		const String::size_type s = filename.find_last_of("\\/");
		if (s != String::npos && p < s)
			return filename + newExt;
		return filename.substr(0, p) + newExt;
	}



	String RemoveDotSegmentsFromUnixFilename(const String& filename)
	{
		if (filename.empty())
			return filename;

		const String::Size howManySlashes = filename.countChar('/');
		if (!howManySlashes)
			return filename;

		String::Vector stack(2 * (howManySlashes + 1) /* Ex: path/to/somewhere */);

		const String::Size length = filename.length();
		const bool isAbsolute = ('/' == filename.first());
		String::Size lastPosition = 0;
		String::Size posInStack = 0;
		String::Size realSegmentsFound = 0;

		// Index in the sequence
		String::Size indx = 0;
		String::Char c;

		for (; indx < length; ++indx)
		{
			if ('/' == (c = filename[indx])) // A slash has been found
			{
				const String::Size len = indx - lastPosition;
				switch (len)
				{
					case 0:
						break;
					case 1:
						{
							if ('.' != filename[lastPosition])
							{
								stack[posInStack++].assign(filename, lastPosition, 1);
								stack[posInStack++] = '/';
								++realSegmentsFound;
							}
							break;
						}
					case 2:
						{
							if ('.' == filename[lastPosition] && '.' == filename[lastPosition + 1])
							{
								if (realSegmentsFound)
								{
									// We have some segments, we have to the parent folder in any cases
									posInStack -= 2;
									--realSegmentsFound;
								}
								else
								{
									// We only have to go to the parent folder only if the path is absolute
									// For example : ../../somewhere
									if (!isAbsolute)
									{
										// We have to keep the `..`
										stack[posInStack++] = "..";
										stack[posInStack++] = '/';
									}
								}
							}
							else
							{
								stack[posInStack++].assign(filename, lastPosition, 2);
								stack[posInStack++] = '/';
								++realSegmentsFound;
							}
							break;
						}
					default:
						{
							stack[posInStack++].assign(filename, lastPosition, len);
							stack[posInStack++] = '/';
							++realSegmentsFound;
							break;
						}
				}
				lastPosition = indx + 1;
			}
		}

		if (lastPosition < length)
		{
			switch (length - lastPosition)
			{
				case 1:
					{
						if ('.' != filename[lastPosition])
							stack[posInStack++].assign(filename, lastPosition, 1);
						break;
					}
				case 2:
					{
						if ('.' == filename[lastPosition] && '.' == filename[lastPosition + 1])
						{
							if (realSegmentsFound)
								posInStack -= 2;
							else
							{
								if (!isAbsolute)
									stack[posInStack++] = "..";
							}
						}
						else
							stack[posInStack++].assign(filename, lastPosition, 2);
						break;
					}
				default:
					stack[posInStack++].assign(filename, lastPosition, length - lastPosition);
			}
		}
		if (posInStack)
		{
			String ret;
			if (isAbsolute)
				ret += '/';
			for (String::Size i = 0; i != posInStack; ++i)
				ret += stack[i];
			return ret;
		}
		return (isAbsolute) ? String('/') : String('.');
	}




} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni





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


