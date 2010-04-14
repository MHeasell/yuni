#ifndef __YUNI_CORE_TRAITS_EXTENSION_INTO_LENGTH_H__
# define __YUNI_CORE_TRAITS_EXTENSION_INTO_LENGTH_H__

# include <string>
# include <cstring>


namespace Yuni
{
namespace Extension
{



	// A zero-terminated container of any type
	template<class C, class SizeT>
	struct Length<C*, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	public:
		static SizeT Value(const C* const container)
		{
			SizeT result(0);
			while (*(++container) != C())
				++result;
			return result;
		}
	};


	// C{N}
	template<class C, int N, class SizeT>
	struct Length<C[N], SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	public:
		static SizeT Value(const C* const container)
		{
			// This value can not really be known at compile time
			// We may encounter literal strings :
			// "abc" -> N = 4 but the real length is 3
			// or a static buffer  char v[42] where the real length is 42
			return (N == 0) ? 0 : (C() == container[N-1] ? N-1 : N);
		}
	};


	// A mere CString (zero-terminated)
	template<class SizeT>
	struct Length<char*, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	public:
		static SizeT Value(const char* const container) {return (SizeT)::strlen(container);}
	};


	// A mere wide string (zero-terminated)
	template<class SizeT>
	struct Length<wchar_t*, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	public:
		static SizeT Value(const wchar_t* const container) {return (SizeT)::wcslen(container);}
	};



	// single char

	template<class SizeT>
	struct Length<char, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 1, fixedLength = 1, };

	public:
		static SizeT Value(const char) {return (SizeT) 1;}
	};


	// A single wide char
	template<class SizeT>
	struct Length<wchar_t, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 1, fixedLength = 1, };

	public:
		static SizeT Value(const wchar_t) {return (SizeT) 1;}
	};





	// CustomString

	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class SizeT>
	struct Length<CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT>, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	private:
		typedef CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT> CustomStringType;

	public:
		static SizeT Value(const CustomStringType& container)
		{
			return (SizeT) container.size();
		}
	};


	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class SizeT>
	struct Length<CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT>*, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	private:
		typedef CustomString<ChunkSizeT, ExpandableT,ZeroTerminatedT> CustomStringType;

	public:
		static SizeT Value(const CustomStringType* const container)
		{
			return (container) ? (SizeT) container->size() : 0;
		}
	};



	// Yuni::String

	template<class C, int ChunkSizeT, class SizeT>
	struct Length<StringBase<C,ChunkSizeT>, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	private:
		typedef StringBase<C,ChunkSizeT> StringType;

	public:
		static SizeT Value(const StringType& container)
		{
			return (SizeT) container.size();
		}
	};

	template<class C, int ChunkSizeT, class SizeT>
	struct Length<StringBase<C,ChunkSizeT>*, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	private:
		typedef StringBase<C,ChunkSizeT> StringType;

	public:
		static SizeT Value(const StringType* const container)
		{
			return container ? (SizeT)container->size() : 0;
		}
	};



	// std::string

	template<class C, class T, class Alloc, class SizeT>
	struct Length<std::basic_string<C,T,Alloc>, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	private:
		typedef std::basic_string<C,T,Alloc> StringType;

	public:
		static SizeT Value(const StringType& container)
		{
			return container.size();
		}
	};


	template<class C, class T, class Alloc, class SizeT>
	struct Length<std::basic_string<C,T,Alloc>*, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	private:
		typedef std::basic_string<C,T,Alloc> StringType;

	public:
		static SizeT Value(const StringType* const container)
		{
			return container ? (SizeT) container->size() : 0;
		}
	};




	// nulptr

	template<class SizeT>
	struct Length<NullPtr, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 1, fixedLength = 0, };

	public:
		static SizeT Value(const Yuni::NullPtr&)
		{
			return 0;
		}
	};




} // namespace Extension
} // namespace Yuni

#endif // __YUNI_CORE_TRAITS_EXTENSION_INTO_LENGTH_H__
