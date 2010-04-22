#ifndef __YUNI_CORE_TRAITS_EXTENSION_INTO_CSTRING_H__
# define __YUNI_CORE_TRAITS_EXTENSION_INTO_CSTRING_H__

# include <string>


namespace Yuni
{
namespace Extension
{


	template<>
	struct IntoCString<char*>
	{
	public:
		enum { valid = 1, converted = 0, zeroTerminated = 1, };

	public:
		static const char* Perform(const char* const container)
		{
			return container; /* identity */
		}
	};


	template<int N>
	struct IntoCString<char[N]>
	{
	public:
		enum { valid = 1, converted = 0, zeroTerminated = 1, };

	public:
		static const char* Perform(const char* const container)
		{
			return container; /* identity */
		}
	};


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	struct IntoCString<CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT> >
	{
	public:
		typedef Yuni::CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT> CustomStringType;
		enum { valid = 1, converted = 0, zeroTerminated = CustomStringType::zeroTerminated, };

	public:
		static const char* Perform(const CustomStringType& container)
		{
			return container.data();
		}
	};


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	struct IntoCString<CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT>* >
	{
	public:
		typedef CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT> CustomStringType;
		enum { valid = 1, converted = 0, zeroTerminated = CustomStringType::zeroTerminated, };

	public:
		static const char* Perform(const CustomStringType* const container)
		{
			return container ? container->data() : NULL;
		}
	};



	template<int ChunkSizeT>
	struct IntoCString<StringBase<char,ChunkSizeT> >
	{
	public:
		enum { valid = 1, converted = 0, zeroTerminated = 1, };

	public:
		static const char* Perform(const StringBase<char,ChunkSizeT>& container)
		{
			return container.c_str();
		}
	};



	template<int ChunkSizeT>
	struct IntoCString<StringBase<char,ChunkSizeT>* >
	{
	public:
		enum { valid = 1, converted = 0, zeroTerminated = 1, };

	public:
		static const char* Perform(const StringBase<char,ChunkSizeT>* const container)
		{
			return container ? container->c_str() : NULL;
		}
	};


	template<class T, class Alloc>
	struct IntoCString<std::basic_string<char,T,Alloc> >
	{
	public:
		enum { valid = 1, converted = 0, zeroTerminated = 1, };

	public:
		static const char* Perform(const std::basic_string<char,T,Alloc>& container)
		{
			return container.c_str();
		}
	};


	template<class T, class Alloc>
	struct IntoCString<std::basic_string<char,T,Alloc>* >
	{
	public:
		enum { valid = 1, converted = 0, zeroTerminated = 1, };

	public:
		static const char* Perform(const std::basic_string<char,T,Alloc>* const container)
		{
			return container ? container->c_str() : NULL;
		}
	};


	template<>
	struct IntoCString<NullPtr>
	{
	public:
		enum { valid = 1, converted = 0, zeroTerminated = 1, };

	public:
		static const char* Perform(const Yuni::NullPtr&)
		{
			return NULL;
		}
	};





} // namespace Extension
} // namespace Yuni

#endif // __YUNI_CORE_TRAITS_EXTENSION_INTO_CSTRING_H__
