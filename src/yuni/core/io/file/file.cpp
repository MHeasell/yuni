
#include <fstream>
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

	bool Stream::close()
	{
		if (pFd)
		{
			if (0 == ::fclose(pFd))
			{
				pFd = NULL;
				return true;
			}
			return false;
		}
		return true;
	}



	bool Size(const char* filename, uint64& size)
	{
		struct stat results;
		if (filename && '\0' != *filename && stat(filename, &results) == 0)
		{
			size = results.st_size;
			return true;
		}
		size = 0;
		return false;
	}


	bool Size(const String& filename, uint64& size)
	{
		struct stat results;
		if (filename.notEmpty() && stat(filename.c_str(), &results) == 0)
		{
			size = results.st_size;
			return true;
		}
		size = 0;
		return false;
	}



	char* LoadContentInMemory(const String& filename, const uint64 hardlimit)
	{
		uint64 s;
		return LoadContentInMemory(filename, s, hardlimit);
	}


	char* LoadContentInMemory(const String& filename, uint64& size, const uint64 hardlimit)
	{
		if (Size(filename, size))
		{
			if (0 == size)
			{
				char* ret = new char[1];
				*ret = '\0';
				return ret;
			}
			if (size > hardlimit)
				return NULL;
			std::ifstream f;
			f.open(filename.c_str(), std::ios::in | std::ios::binary);
			if (f.is_open())
			{
				char* ret = new char[(int)size + 1];
				f.read((char*)ret, (std::streamsize)size);
				f.close();
				ret[size] = '\0';
				return ret;
			}
		}
		return NULL;
	}



	bool SaveToFile(const String& filename, const String& content)
	{
		std::ofstream dst(filename.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
		if (dst.is_open())
		{
			dst << content;
			return true;
		}
		return false;
	}



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




	bool Copy(const String& from, const String& to, const bool overwrite)
	{
		if (!IO::File::Exists(from))
			return false;
		if (!overwrite && IO::File::Exists(to))
			return true;
		std::ifstream src(from.c_str(), std::ios::in | std::ios::binary);
		if (src.is_open())
		{
			std::ofstream dst(to.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
			if (dst.is_open())
			{
				dst << src.rdbuf();
				return true;
			}
		}
		return false;
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



	bool Stream::seek(ssize_t offset, SeekOrigin origin)
	{
		switch (origin)
		{
			case seekOriginBegin:   return (0 == ::fseeko(pFd, offset, SEEK_SET));
			case seekOriginCurrent: return (0 == ::fseeko(pFd, offset, SEEK_CUR));
			case seekOriginEnd:     return (0 == ::fseeko(pFd, offset, SEEK_END));
		}
		return false;
	}




} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

