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

	bool Remove(const char* path);

	/*!
	** \brief Get the current directory which must be freed
	*/
	char* CurrentDirectory();

	bool ChangeCurrentDirectory(const char* src, size_t srclen);
	bool ChangeCurrentDirectoryNotZeroTerminated(const char* path, size_t length);


	bool RecursiveCopy(const char* src, size_t srclen, const char* dst, size_t dstlen, bool recursive,
		bool overwrite, const Yuni::Core::IO::Directory::CopyOnUpdateBind& onUpdate);

	bool DummyCopyUpdateEvent(Yuni::Core::IO::Directory::CopyState, const String&, const String&, uint64, uint64);


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
	inline bool Create(const StringT& path, unsigned int mode)
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



	template<class StringT1, class StringT2>
	inline bool Copy(const StringT1& source, const StringT2& destination, bool recursive, bool overwrite)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT1>::valid, CustomString_InvalidTypeForBuffer1);
		YUNI_STATIC_ASSERT(Traits::CString<StringT2>::valid, CustomString_InvalidTypeForBuffer2);
		YUNI_STATIC_ASSERT(Traits::Length<StringT1>::valid,  CustomString_InvalidTypeForBufferSize1);
		YUNI_STATIC_ASSERT(Traits::Length<StringT2>::valid,  CustomString_InvalidTypeForBufferSize2);

		CopyOnUpdateBind e;
		e.bind(&Private::Core::IO::Directory::DummyCopyUpdateEvent);
		return Private::Core::IO::Directory::RecursiveCopy(
			Traits::CString<StringT1>::Perform(source),      Traits::Length<StringT1,size_t>::Value(source),
			Traits::CString<StringT2>::Perform(destination), Traits::Length<StringT1,size_t>::Value(destination),
			recursive, overwrite, e);
	}

	template<class StringT1, class StringT2>
	inline bool Copy(const StringT1& source, const StringT2& destination, bool recursive,
		bool overwrite, const CopyOnUpdateBind& onUpdate)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT1>::valid, CustomString_InvalidTypeForBuffer1);
		YUNI_STATIC_ASSERT(Traits::CString<StringT2>::valid, CustomString_InvalidTypeForBuffer2);
		YUNI_STATIC_ASSERT(Traits::Length<StringT1>::valid,  CustomString_InvalidTypeForBufferSize1);
		YUNI_STATIC_ASSERT(Traits::Length<StringT2>::valid,  CustomString_InvalidTypeForBufferSize2);

		return Private::Core::IO::Directory::RecursiveCopy(
			Traits::CString<StringT1>::Perform(source),      Traits::Length<StringT1,size_t>::Value(source),
			Traits::CString<StringT2>::Perform(destination), Traits::Length<StringT1,size_t>::Value(destination),
			recursive, overwrite, onUpdate);
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
