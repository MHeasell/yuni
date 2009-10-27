#ifndef __YUNI_CORE_TRAITS_LENGTH_H__
# define __YUNI_CORE_TRAITS_LENGTH_H__

# include "../../yuni.h"


namespace Yuni
{
namespace Core
{
namespace Traits
{

	/*!
	** \brief Length of standard types
	*/
	template<class C, class SizeT = unsigned int>
	struct Length {};


	// A zero-terminated buffer of any type
	template<class C, class SizeT>
	struct Length<C*, SizeT>
	{
		static SizeT Value(const C* buffer)
		{
			SizeT result(0);
			while (*(++buffer) != C(0))
				++result;
			return result;
		}
	};

	// A mere CString (zero-terminated)
	template<class SizeT>
	struct Length<char*, SizeT>
	{
		static SizeT Value(const char* buffer) {return (SizeT)::strlen(buffer);}
	};

	// A mere wide string (zero-terminated)
	template<class SizeT>
	struct Length<wchar_t*, SizeT>
	{
		static SizeT Value(const wchar_t* buffer) {return (SizeT)::wcslen(buffer);}
	};

	// A single  char
	template<class SizeT>
	struct Length<char, SizeT>
	{
		static SizeT Value(const char) {return (SizeT) 1;}
	};


	// A single wide char
	template<class SizeT>
	struct Length<wchar_t, SizeT>
	{
		static SizeT Value(const wchar_t) {return (SizeT) 1;}
	};


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT, class SizeT>
	struct Length<MemoryBuffer<C,ChunkSizeT, ZeroTerminatedT,ExpandableT>, SizeT>
	{
		typedef MemoryBuffer<C,ChunkSizeT, ZeroTerminatedT,ExpandableT> MemoryBufferType;
		static SizeT Value(const MemoryBufferType& buffer)
		{
			return (SizeT) buffer.size();
		}
	};


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT, class SizeT>
	struct Length<MemoryBuffer<C,ChunkSizeT, ZeroTerminatedT,ExpandableT>*, SizeT>
	{
		typedef MemoryBuffer<C,ChunkSizeT, ZeroTerminatedT,ExpandableT> MemoryBufferType;

		static SizeT Value(const MemoryBufferType* buffer)
		{
			return (buffer) ? (SizeT) buffer->size() : 0;
		}
	};


	template<class C, class T, class Alloc, class SizeT>
	struct Length<std::basic_string<C,T,Alloc>, SizeT>
	{
		typedef std::basic_string<C,T,Alloc> StringType;

		static SizeT Value(const StringType& buffer)
		{
			return buffer.size();
		}
	};


	template<class C, class T, class Alloc, class SizeT>
	struct Length<std::basic_string<C,T,Alloc>*, SizeT>
	{
		typedef std::basic_string<C,T,Alloc> StringType;

		static SizeT Value(const StringType* buffer)
		{
			return buffer ? buffer->size() : 0;
		}
	};


	template<class SizeT>
	struct Length<NullPtr, SizeT>
	{
		static SizeT Value(const Yuni::NullPtr& buffer)
		{
			return 0;
		}
	};





} // namespace Traits
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_TRAITS_LENGTH_H__
