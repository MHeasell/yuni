
#include "../directory.h"
#include "../../slist.h"
#include "info.h"
#include "../file.h"



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


	bool DummyCopyUpdateEvent(Yuni::Core::IO::Directory::CopyState, const String&, const String&, uint64, uint64)
	{
		return true;
	}


	struct InfoItem
	{
		bool isFile;
		uint64  size;
		String filename;
	};
	typedef LinkedList<InfoItem> List;



	bool RecursiveCopy(const char* src, size_t srclen, const char* dst, size_t dstlen, bool recursive,
		bool overwrite, const Yuni::Core::IO::Directory::CopyOnUpdateBind& onUpdate)
	{
		// normalize paths
		String fsrc(src, srclen);
		Yuni::Core::IO::Normalize(fsrc, src, (unsigned int)srclen);
		String fdst(dst, dstlen);
		Yuni::Core::IO::Normalize(fdst, dst, (unsigned int)dstlen);

		// The list of files to copy
		List list;
		uint64 totalSize = 0;

		// Adding the target folder, to create it if required
		{
			list.push_back();
			InfoItem& info = list.back();
			info.filename = fdst;
			info.isFile   = false;
		}

		{
			Yuni::Core::IO::Directory::Info info(fsrc);
			unsigned int count = 0;
			if (recursive)
			{
				const Yuni::Core::IO::Directory::Info::recursive_iterator end = info.recursive_end();
				for (Yuni::Core::IO::Directory::Info::recursive_iterator i = info.recursive_begin(); i != end; ++i)
				{
					list.push_back();
					InfoItem& info = list.back();
					info.filename = i.filename();
					info.isFile   = i.isFile();
					totalSize += i.size();
					if (++count >> 5)
					{
						if (!onUpdate(Yuni::Core::IO::Directory::cpsGatheringInformation, *i, *i, 0, list.size()))
							return false;
						count = 0;
					}
				}
			}
			else
			{
				const Yuni::Core::IO::Directory::Info::recursive_iterator end = info.recursive_end();
				for (Yuni::Core::IO::Directory::Info::recursive_iterator i = info.recursive_begin(); i != end; ++i)
				{
					list.push_back();
					InfoItem& info = list.back();
					info.filename = i.filename();
					info.isFile   = i.isFile();
					totalSize += i.size();

					if (++count >> 5)
					{
						if (!onUpdate(Yuni::Core::IO::Directory::cpsGatheringInformation, *i, *i, 0, list.size()))
							return false;
						count = 0;
					}
				}
			}
		}

		uint64 current = 0;
		// A temporary string
		String tmp;

		Yuni::Core::IO::File::Stream fromFile;
		Yuni::Core::IO::File::Stream toFile;
		enum { bufferSize = 8192 };
		char* buffer = new char[bufferSize];
		size_t numRead;

		unsigned int count = 0;
		const List::const_iterator end = list.end();
		for (List::const_iterator i = list.begin(); i != end; ++i)
		{
			const InfoItem& info = *i;
			tmp.clear() << fdst << Yuni::Core::IO::Separator;
			tmp.append(info.filename.c_str() + fsrc.size() + 1, info.filename.size() - fsrc.size() - 1);

			if (!info.isFile)
			{
				if (++count >> 5)
				{
					if (!onUpdate(Yuni::Core::IO::Directory::cpsCopying, info.filename, tmp, current, totalSize))
					{
						delete[] buffer;
						return false;
					}
				}
				count = 0;

				if (!Yuni::Core::IO::Directory::Create(tmp))
				{
					delete[] buffer;
					return false;
				}
			}
			else
			{
				if (!overwrite && Yuni::Core::IO::Exists(tmp))
					continue;

				// Open the source file
				if (fromFile.open(info.filename, Yuni::Core::IO::OpenMode::read))
				{
					if (toFile.open(tmp, Yuni::Core::IO::OpenMode::write | Yuni::Core::IO::OpenMode::truncate))
					{
						while ((numRead = fromFile.read(buffer, bufferSize)) != 0)
						{
							current += numRead;
							if (numRead != toFile.write((const char*)buffer, numRead))
							{
								delete[] buffer;
								return false;
							}

							if (++count >> 7)
							{
								if (!onUpdate(Yuni::Core::IO::Directory::cpsCopying, info.filename, tmp, current, totalSize))
								{
									delete[] buffer;
									return false;
								}

								count = 0;
							}
						}
					}
				}
			}
		}

		delete[] buffer;

		return true;
	}




} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Private
} // namespace Yuni

