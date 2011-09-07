#ifndef __YUNI_IO_IO_HXX__
# define __YUNI_IO_IO_HXX__

# include <cassert>
# include <ctype.h>

namespace Yuni
{
namespace Private
{
namespace IO
{

	Yuni::IO::NodeType TypeOf(const char* p, unsigned int length);
	Yuni::IO::NodeType TypeOfNotZeroTerminated(const char* p, unsigned int length);

} // namespace IO
} // namespace Private
} // namespace Yuni





namespace Yuni
{
namespace IO
{



	template<class StringT> inline bool Exists(const StringT& filename)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, IOExists_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  IOExists_InvalidTypeForBufferSize);
		return (Yuni::IO::typeUnknown != Yuni::IO::TypeOf(filename));
	}


	template<class StringT>
	inline NodeType TypeOf(const StringT& filename)
	{
		YUNI_STATIC_ASSERT(Traits::CString<StringT>::valid, TypeOF_InvalidTypeForBuffer);
		YUNI_STATIC_ASSERT(Traits::Length<StringT>::valid,  TypeOF_InvalidTypeForBufferSize);

		if (Traits::CString<StringT>::zeroTerminated) // static check
		{
			return Yuni::Private::IO::TypeOf(
				Traits::CString<StringT>::Perform(filename),
				Traits::Length<StringT, unsigned int>::Value(filename));
		}
		else
		{
			return Yuni::Private::IO::TypeOf(
				Traits::CString<StringT>::Perform(filename),
				Traits::Length<StringT, unsigned int>::Value(filename));
		}
	}




} // namespace IO
} // namespace Yuni

#endif // __YUNI_IO_IO_HXX__
