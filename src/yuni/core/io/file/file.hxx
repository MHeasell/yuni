#ifndef __YUNI_CORE_FS_FILES_HXX__
# define __YUNI_CORE_FS_FILES_HXX__


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace File
{


	template<typename C, int N>
	inline bool Exists(const StringBase<C,N>& p)
	{
		# ifdef YUNI_OS_WINDOWS
		return p.notEmpty() ? Private::IO::FilesystemImpl::IsFileWindowsImpl(p, p.size()) : false;
		# else
		return p.notEmpty() ? Private::IO::FilesystemImpl::IsFileUnixImpl(p.c_str()) : false;
		# endif

	}


	inline bool Exists(const char* p)
	{
		# ifdef YUNI_OS_WINDOWS
		return (p && '\0' != *p) ? Private::IO::FilesystemImpl::IsFileWindowsImpl(p, ::strlen(p)) : false;
		# else
		return (p && '\0' != *p) ? Private::IO::FilesystemImpl::IsFileUnixImpl(p) : false;
		# endif
	}


	template<int N>
	inline bool Load(String::Vector& out, const StringBase<char,N>& filename, const bool emptyListBefore,
			const uint32 sizeLimit)
	{
		return Load(out, filename.c_str(), emptyListBefore, sizeLimit);
	}

	template<int N>
	inline bool Load(String::List& out, const StringBase<char,N>& filename, const bool emptyListBefore,
			const uint32 sizeLimit)
	{
		return Load(out, filename.c_str(), emptyListBefore, sizeLimit);
	}




} // namespace File
} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_FS_FILES_H__
