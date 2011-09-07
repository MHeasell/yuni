#ifndef __YUNI_IO_DIRECTORY_HXX__
# define __YUNI_IO_DIRECTORY_HXX__

# include "../../core/traits/cstring.h"
# include "../../core/traits/length.h"
# include "../../core/static/remove.h"
# include "../constants.h"
# ifdef YUNI_HAS_STDLIB_H
#	include <stdlib.h>
# endif


namespace Yuni
{
namespace Private
{
namespace IO
{
namespace Directory
{

	/*!
	** \brief Get the current directory which must be freed
	*/
	char* CurrentDirectory();

	bool ChangeCurrentDirectory(const char* src, unsigned int srclen);
	bool ChangeCurrentDirectoryNotZeroTerminated(const char* path, unsigned int length);


	bool RecursiveCopy(const char* src, unsigned int srclen, const char* dst, unsigned int dstlen, bool recursive,
		bool overwrite, const Yuni::IO::Directory::CopyOnUpdateBind& onUpdate);

	bool DummyCopyUpdateEvent(Yuni::IO::Directory::CopyState, const String&, const String&, uint64, uint64);



} // namespace Directory
} // namespace IO
} // namespace Private
} // namespace Yuni



namespace Yuni
{
namespace IO
{
namespace Directory
{



	template<class StringT>
	inline bool Exists(const StringT& path)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, DirectoryExists_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  DirectoryExists_InvalidTypeForBufferSize);

		return ((Yuni::IO::typeFolder & Yuni::IO::TypeOf(path)) != 0);
	}



	template<class StringT1, class StringT2>
	inline bool Copy(const StringT1& source, const StringT2& destination, bool recursive, bool overwrite)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT1>::valid, CString_InvalidTypeForBuffer1);
		YUNI_STATIC_ASSERT(Traits::CString<StringT2>::valid, CString_InvalidTypeForBuffer2);
		YUNI_STATIC_ASSERT(Traits::Length<StringT1>::valid,  CString_InvalidTypeForBufferSize1);
		YUNI_STATIC_ASSERT(Traits::Length<StringT2>::valid,  CString_InvalidTypeForBufferSize2);

		CopyOnUpdateBind e;
		e.bind(&Private::IO::Directory::DummyCopyUpdateEvent);
		return Private::IO::Directory::RecursiveCopy(
			Traits::CString<StringT1>::Perform(source),      Traits::Length<StringT1,unsigned int>::Value(source),
			Traits::CString<StringT2>::Perform(destination), Traits::Length<StringT1,unsigned int>::Value(destination),
			recursive, overwrite, e);
	}

	template<class StringT1, class StringT2>
	inline bool Copy(const StringT1& source, const StringT2& destination, bool recursive,
		bool overwrite, const CopyOnUpdateBind& onUpdate)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT1>::valid, CString_InvalidTypeForBuffer1);
		YUNI_STATIC_ASSERT(Traits::CString<StringT2>::valid, CString_InvalidTypeForBuffer2);
		YUNI_STATIC_ASSERT(Traits::Length<StringT1>::valid,  CString_InvalidTypeForBufferSize1);
		YUNI_STATIC_ASSERT(Traits::Length<StringT2>::valid,  CString_InvalidTypeForBufferSize2);

		return Private::IO::Directory::RecursiveCopy(
			Traits::CString<StringT1>::Perform(source),      Traits::Length<StringT1,unsigned int>::Value(source),
			Traits::CString<StringT2>::Perform(destination), Traits::Length<StringT1,unsigned int>::Value(destination),
			recursive, overwrite, onUpdate);
	}



} // namespace Directory
} // namespace IO
} // namespace Yuni





namespace Yuni
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
		char* c = Yuni::Private::IO::Directory::CurrentDirectory();
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
			return Yuni::Private::IO::Directory::ChangeCurrentDirectory(
				Traits::CString<StringT>::Perform(path), Traits::Length<StringT,unsigned int>::Value(path));
		}
		else
		{
			return Yuni::Private::IO::Directory::ChangeCurrentDirectoryNotZeroTerminated(
				Traits::CString<StringT>::Perform(path), Traits::Length<StringT,unsigned int>::Value(path));
		}
	}



} // namespace Current
} // namespace Directory
} // namespace IO
} // namespace Yuni

#endif // __YUNI_IO_DIRECTORY_H__
