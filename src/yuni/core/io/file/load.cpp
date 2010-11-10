
#include "../file.h"
#include <fstream>



namespace Yuni
{
namespace Core
{
namespace IO
{
namespace File
{


	namespace // anonymous
	{

		template<class T>
		bool TmplLoadFromFile(T& out, const char* filename, const bool emptyListBefore, const uint64 sizeLimit)
		{
			if (emptyListBefore)
				out.clear();
			if (filename && '\0' != *filename)
			{
				Core::IO::File::Stream file(filename);
				if (file.opened())
				{
					uint64 totalSize = 0;
					CustomString<4096> line;
					while (file.readline(line))
					{
						if ((totalSize += line.size()) > sizeLimit)
							return false;
						out.push_back(line.c_str());
					}
					return true;
				}
			}
			return false;
		}

	} // anonymous namespace




	bool Load(String::List& out, const char* filename, const bool emptyListBefore, const uint64 sizeLimit)
	{
		return TmplLoadFromFile< String::List >(out, filename, emptyListBefore, sizeLimit);
	}

	bool Load(String::Vector& out, const char* filename, const bool emptyListBefore, const uint64 sizeLimit)
	{
		return TmplLoadFromFile< String::Vector >(out, filename, emptyListBefore, sizeLimit);
	}





} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

