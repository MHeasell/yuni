
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
		bool TmplLoadFromFile(T& out, const char* filename, const bool emptyListBefore, const uint32 sizeLimit)
		{
			if (emptyListBefore)
				out.clear();
			if (filename && '\0' != *filename)
			{
				Core::IO::File::Stream file(filename);
				if (file.opened())
				{
					size_t totalSize = 0;
					String line;
					line.reserve(4096);
					while (file.gets(line.data(), 4096))
					{
						size_t size = strlen(line.data());
						totalSize += size;
						if (totalSize > sizeLimit)
							return false;
						line.resize(size);
						out.push_back(line);
					}
					return true;
				}
			}
			return false;
		}

	} // anonymous namespace




	bool Load(String::List& out, const char* filename, const bool emptyListBefore, const uint32 sizeLimit)
	{
		return TmplLoadFromFile< String::List >(out, filename, emptyListBefore, sizeLimit);
	}

	bool Load(String::Vector& out, const char* filename, const bool emptyListBefore, const uint32 sizeLimit)
	{
		return TmplLoadFromFile< String::Vector >(out, filename, emptyListBefore, sizeLimit);
	}





} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

