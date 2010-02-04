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
			Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(path));
		# else
		return Private::Core::IO::Directory::UnixMake(
			Traits::CString<typename Static::Remove::Const<C>::Type>::Buffer(path), mode);
		# endif
	}


	template<class AnyStringT1, class AnyStringT2>
	inline bool Copy(const AnyStringT1& src, const AnyStringT2& dst)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT1>::Type UType1;
		typedef typename Static::Remove::Const<AnyStringT2>::Type UType2;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType1>::valid, Copy_InvalidTypeForBuffer1);
		YUNI_STATIC_ASSERT(Traits::CString<UType2>::valid, Copy_InvalidTypeForBuffer2);

		return Private::Core::IO::Directory::Copy(
			Traits::CString<UType1>::Buffer(src), Traits::CString<UType2>::Buffer(dst));
	}


	template<class AnyStringT>
	inline bool Remove(const AnyStringT& path)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, DirectoryExists_InvalidTypeForBuffer);

		return Private::Core::IO::Directory::Remove(
			Traits::CString<UType>::Buffer(path));
	}


	template<class AnyStringT>
	inline bool Exists(const AnyStringT& path)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, DirectoryExists_InvalidTypeForBuffer);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  DirectoryExists_InvalidTypeForBufferSize);

		# ifdef YUNI_OS_WINDOWS
		return Private::IO::FilesystemImpl::IsDirectoryWindowsImpl(
			Traits::CString<UType>::Buffer(path),
			Traits::Length<UType, unsigned int>::Value(path));
		# else
		return Private::IO::FilesystemImpl::IsDirectoryUnixImpl(
			Traits::CString<UType>::Buffer(path));
		# endif
	}





} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_IO_DIRECTORY_H__
