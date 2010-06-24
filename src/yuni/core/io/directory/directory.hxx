#ifndef __YUNI_CORE_IO_DIRECTORY_HXX__
# define __YUNI_CORE_IO_DIRECTORY_HXX__

# include "../../traits/cstring.h"
# include "../../traits/length.h"
# include "../../static/remove.h"
# include "../io.h"
# ifdef YUNI_HAS_STDLIB_H
#	include <stdlib.h>
# endif


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
	bool WindowsMake(const char* path, size_t len);
	# else
	bool UnixMake(const char* path, size_t len, unsigned int mode = 0755);
	# endif

	bool Copy(const char* src, unsigned int srclen, const char* dst, unsigned int dstlen);

	bool Remove(const char* path);

	/*!
	** \brief Get the current directory which must be freed
	*/
	char* CurrentDirectory();

	bool ChangeCurrentDirectory(const char* src, size_t srclen);
	bool ChangeCurrentDirectoryNotZeroTerminated(const char* path, size_t length);


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


	template<class StringT>
	inline bool Make(const StringT& path, unsigned int mode)
	{
		if (Yuni::Core::IO::Exists(path))
			return true;
		# ifdef YUNI_OS_WINDOWS
		// `mode` is not used on Windows
		(void) mode;
		return Private::Core::IO::Directory::WindowsMake(
			Traits::CString<StringT>::Perform(path), Traits::Length<StringT,size_t>::Value(path)
			);
		# else
		return Private::Core::IO::Directory::UnixMake(
			Traits::CString<StringT>::Perform(path), Traits::Length<StringT,size_t>::Value(path),
			mode);
		# endif
	}


	template<class StringT1, class StringT2>
	inline bool Copy(const StringT1& src, const StringT2& dst)
	{
		// Assert, if a typename CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>::Char* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<StringT1>::valid, Copy_InvalidTypeForBuffer1);
		YUNI_STATIC_ASSERT(Traits::CString<StringT2>::valid, Copy_InvalidTypeForBuffer2);

		return Private::Core::IO::Directory::Copy(
			Traits::CString<StringT1>::Perform(src), Traits::Length<StringT1,unsigned int>::Value(src),
			Traits::CString<StringT2>::Perform(dst), Traits::Length<StringT2,unsigned int>::Value(dst));
	}


	template<class StringT>
	inline bool Remove(const StringT& path)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, Remove_InvalidTypeForBuffer);

		return Private::Core::IO::Directory::Remove(Traits::CString<StringT>::Perform(path));
	}


	template<class StringT>
	inline bool Exists(const StringT& path)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, DirectoryExists_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  DirectoryExists_InvalidTypeForBufferSize);

		return ((Yuni::Core::IO::typeFolder & Yuni::Core::IO::TypeOf(path)) != 0);
	}



} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace Directory
{
namespace Current
{

	template<class StringT>
	inline void Get(StringT& out, bool clearBefore)
	{
		char* c = Yuni::Private::Core::IO::Directory::CurrentDirectory();
		if (clearBefore)
			out = c;
		else
			out += c;
		::free(c);
	}


	template<class StringT>
	inline bool Set(const StringT& path)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, DirectoryExists_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  DirectoryExists_InvalidTypeForBufferSize);

		if (Traits::CString<StringT>::zeroTerminated)
		{
			return Yuni::Private::Core::IO::Directory::ChangeCurrentDirectory(
				Traits::CString<StringT>::Perform(path), Traits::Length<StringT,size_t>::Value(path));
		}
		else
		{
			return Yuni::Private::Core::IO::Directory::ChangeCurrentDirectoryNotZeroTerminated(
				Traits::CString<StringT>::Perform(path), Traits::Length<StringT,size_t>::Value(path));
		}
	}



} // namespace Current
} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni



#endif // __YUNI_CORE_IO_DIRECTORY_H__
