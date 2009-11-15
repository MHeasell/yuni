#ifndef __YUNI_CORE_IO_DIRECTORY_HXX__
# define __YUNI_CORE_IO_DIRECTORY_HXX__

# include "../../traits/cstring.h"
# include "../../traits/length.h"
# include "../../static/remove.h"


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

	# ifdef YUNI_OS_WINDOWS
	bool WindowsMake(const char* path);
	# else
	bool UnixMake(const char* path, unsigned int mode = 0755);
	# endif

	bool Copy(const char* src, const char* dst);

	bool Remove(const char* path);

} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Private
} // namespace Yuni



namespace Yuni
{
namespace Core
{
namespace IO
{
namespace Directory
{


	template<class C>
	inline bool Make(const C& path, unsigned int mode)
	{
		# ifdef YUNI_OS_WINDOWS
		(void) mode;
		return Private::Core::IO::Directory::WindowsMake(
			Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(path));
		# else
		return Private::Core::IO::Directory::UnixMake(
			Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(path), mode);
		# endif
	}


	template<class C, class D> inline bool Copy(const C& src, const D& dst)
	{
		return Private::Core::IO::Directory::Copy(
			Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(src),
			Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(dst));
	}


	template<class C>
	inline bool Remove(const C& path)
	{
		return Private::Core::IO::Directory::Remove(
			Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(path));
	}


	template<class C>
	inline bool Exists(const C& path)
	{
		# ifdef YUNI_OS_WINDOWS
		return Private::IO::FilesystemImpl::IsDirectoryWindowsImpl(
			Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(path),
			Core::Traits::Length<C>::Value(path));
		# else
		return Private::IO::FilesystemImpl::IsDirectoryUnixImpl(Core::Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(path));
		# endif
	}





} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_IO_DIRECTORY_H__
