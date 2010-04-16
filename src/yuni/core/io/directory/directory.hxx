#ifndef __YUNI_CORE_IO_DIRECTORY_HXX__
# define __YUNI_CORE_IO_DIRECTORY_HXX__

# include "../../traits/cstring.h"
# include "../../traits/length.h"
# include "../../static/remove.h"
# include "../io.h"


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
	bool WindowsMake(const char* path, unsigned int len);
	# else
	bool UnixMake(const char* path, unsigned int len, unsigned int mode = 0755);
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


	template<class AnyStringT>
	inline bool Make(const AnyStringT& path, unsigned int mode)
	{
		if (Yuni::Core::IO::Exists(path))
			return true;
		# ifdef YUNI_OS_WINDOWS
		// `mode` is not used on Windows
		(void) mode;
		return Private::Core::IO::Directory::WindowsMake(
			Traits::CString<AnyStringT>::Perform(path), Traits::Length<AnyStringT>::Value(path)
			);
		# else
		return Private::Core::IO::Directory::UnixMake(
			Traits::CString<AnyStringT>::Perform(path), Traits::Length<AnyStringT>::Value(path),
			mode);
		# endif
	}


	template<class AnyStringT1, class AnyStringT2>
	inline bool Copy(const AnyStringT1& src, const AnyStringT2& dst)
	{
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<AnyStringT1>::valid, Copy_InvalidTypeForBuffer1);
		YUNI_STATIC_ASSERT(Traits::CString<AnyStringT2>::valid, Copy_InvalidTypeForBuffer2);

		return Private::Core::IO::Directory::Copy(
			Traits::CString<AnyStringT1>::Perform(src), Traits::CString<AnyStringT2>::Perform(dst));
	}


	template<class AnyStringT>
	inline bool Remove(const AnyStringT& path)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, DirectoryExists_InvalidTypeForBuffer);

		return Private::Core::IO::Directory::Remove(Traits::CString<UType>::Perform(path));
	}


	template<class AnyStringT>
	inline bool Exists(const AnyStringT& path)
	{
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<AnyStringT>::valid, DirectoryExists_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<AnyStringT>::valid,  DirectoryExists_InvalidTypeForBufferSize);

		# ifdef YUNI_OS_WINDOWS
		return Private::IO::FilesystemImpl::IsDirectoryWindowsImpl(
			Traits::CString<AnyStringT>::Perform(path),
			Traits::Length<AnyStringT, unsigned int>::Value(path));
		# else
		return Private::IO::FilesystemImpl::IsDirectoryUnixImpl(
			Traits::CString<AnyStringT>::Perform(path));
		# endif
	}





} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_IO_DIRECTORY_H__
