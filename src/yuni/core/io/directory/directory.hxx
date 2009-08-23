#ifndef __YUNI_CORE_IO_DIRECTORY_HXX__
# define __YUNI_CORE_IO_DIRECTORY_HXX__


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace Directory
{


	template<int N>
	inline bool MakeDir(const StringBase<char,N>& p, unsigned int mode)
	{
		return MakeDir(p.c_str(), mode);
	}


	template<int N, int M>
	inline bool Copy(const StringBase<char,N>& src, const StringBase<char,M>& dst)
	{
		return Copy(src.c_str(), dst.c_str());
	}


	template<int N>
	inline bool Remove(const StringBase<char,N>& p)
	{
		return RmDir(p.c_str());
	}


	template<typename C, int N>
	inline bool Exists(const StringBase<C,N>& p)
	{
		# ifdef YUNI_OS_WINDOWS
		return p.notEmpty() ? Private::IO::FilesystemImpl::IsDirectoryWindowsImpl(p, p.size()) : false;
		# else
		return p.notEmpty() ? Private::IO::FilesystemImpl::IsDirectoryUnixImpl(p.c_str()) : false;
		# endif

	}


	inline bool Exists(const char* p)
	{
		# ifdef YUNI_OS_WINDOWS
		return (p && '\0' != *p) ? Private::IO::FilesystemImpl::IsDirectoryWindowsImpl(p, ::strlen(p)) : false;
		# else
		return (p && '\0' != *p) ? Private::IO::FilesystemImpl::IsDirectoryUnixImpl(p) : false;
		# endif
	}



} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_IO_DIRECTORY_H__
