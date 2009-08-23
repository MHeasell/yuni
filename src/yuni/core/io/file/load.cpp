
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


	namespace
	{
		template<class T>
		bool TmplLoadFromFile(T& out, const char* filename, const bool emptyListBefore, const uint32 sizeLimit)
		{
			if (emptyListBefore)
				out.clear();
			if (filename && '\0' != *filename)
			{
				std::ifstream file(filename);
				if (!file)
					return false;
				if (sizeLimit)
				{
					file.seekg(0, std::ios_base::beg);
					std::ifstream::pos_type begin_pos = file.tellg();
					file.seekg(0, std::ios_base::end);
					if ((uint32)(file.tellg() - begin_pos) > sizeLimit)
						return false;
					file.seekg(0, std::ios_base::beg);
				}
				std::string line;
				while (std::getline(file, line))
					out.push_back(line);
				return true;
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

