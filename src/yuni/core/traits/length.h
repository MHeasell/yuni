#ifndef __YUNI_CORE_TRAITS_LENGTH_H__
# define __YUNI_CORE_TRAITS_LENGTH_H__

# include "../../yuni.h"
# include <string.h>


namespace Yuni
{
namespace Core
{
namespace Traits
{


	/*!
	** \brief Traits: Length (number of items) of an arbitrary container
	**
	** The length is the number of items contained in the container.
	**
	** \tparam C Any class (Static::Remove::Const<> should be used with this parameter)
	** \tparam SizeT The type to use for the returned length
	*/
	template<class C, class SizeT = size_t>
	struct Length
	{
	public:
		//! The type to use for the returned length
		typedef SizeT SizeType;

		enum
		{
			//! A non-zero value if the specialization is valid
			valid = 0,
			//! A non-zero value when the size is known at compile time
			isFixed = 1,
			//! The fixed length value when it can be known at compile time (can be 0), 0 otherwise
			fixedLength = 0,
		};

	public:
		/*!
		** \brief Get the length of the container
		**
		** \param rhs A arbitrary container
		** \return The length of the container
		*/
		static SizeT Value(const C& rhs) { return (SizeT) 0 /* Default value */; }

	}; // class Length<>









	// A zero-terminated container of any type
	template<class C, class SizeT>
	struct Length<C*, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	public:
		static SizeT Value(const C* container)
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
		static SizeT Value(const C* container)
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
		static SizeT Value(const char* container) {return (SizeT)::strlen(container);}
	};


	// A mere wide string (zero-terminated)
	template<class SizeT>
	struct Length<wchar_t*, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	public:
		static SizeT Value(const wchar_t* container) {return (SizeT)::wcslen(container);}
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





	// MemoryBuffer

	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT, class SizeT>
	struct Length<MemoryBuffer<C,ChunkSizeT, ZeroTerminatedT,ExpandableT>, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	private:
		typedef MemoryBuffer<C,ChunkSizeT, ZeroTerminatedT,ExpandableT> MemoryBufferType;

	public:
		static SizeT Value(const MemoryBufferType& container)
		{
			return (SizeT) container.size();
		}
	};


	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT, class SizeT>
	struct Length<MemoryBuffer<C,ChunkSizeT, ZeroTerminatedT,ExpandableT>*, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	private:
		typedef MemoryBuffer<C,ChunkSizeT, ZeroTerminatedT,ExpandableT> MemoryBufferType;

	public:
		static SizeT Value(const MemoryBufferType* container)
		{
			return (container) ? (SizeT) container->size() : 0;
		}
	};



	// Yuni::String

	template<class C, unsigned int ChunkSizeT, class SizeT>
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

	template<class C, unsigned int ChunkSizeT, class SizeT>
	struct Length<StringBase<C,ChunkSizeT>*, SizeT>
	{
	public:
		typedef SizeT SizeType;
		enum { valid = 1, isFixed = 0, fixedLength = 0, };

	private:
		typedef StringBase<C,ChunkSizeT> StringType;

	public:
		static SizeT Value(const StringType* container)
		{
			return (SizeT) container.size();
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
		static SizeT Value(const StringType* container)
		{
			return container ? container->size() : 0;
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





} // namespace Traits
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_TRAITS_LENGTH_H__
