#ifndef __YUNI_CORE_TRAITS_C_STRING_H__
# define __YUNI_CORE_TRAITS_C_STRING_H__

# include "../../yuni.h"


namespace Yuni
{
namespace Core
{
namespace Traits
{


	/*!
	** \brief Traits: C-String (const char*) representation of an arbitrary contrainer
	**
	** \tparam C Any class (Static::Remove::Const<> should be used with this parameter)
	*/
	template<class C>
	struct CString
	{
	public:
		enum
		{
			//! A non-zero value if the specialization is valid
			valid = 0,
			//! A non-zero value if the data have been converted
			converted = 0,
		};

	public:
		/*!
		** \brief Get a C-String representation of an arbitrary contrainer
		**
		** \param container A arbitrary container
		** \return The equivalent of a `const char*` pointer (can be NULL)
		*/
		static const char* Buffer(const C& /*container*/) { return NULL; /* Default */ }

	}; // class CString<>






	template<>
	struct CString<char*>
	{
	public:
		enum { valid = 1, converted = 0, };
	
	public:
		static const char* Buffer(const char* container)
		{
			return container; /* identity */
		}
	};



	template<unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	struct CString<MemoryBuffer<char,ChunkSizeT, ZeroTerminatedT,ExpandableT> >
	{
	public:
		enum { valid = 1, converted = 0, };
	
	public:
		static const char* Buffer(const MemoryBuffer<char,ChunkSizeT, ZeroTerminatedT,ExpandableT>& container)
		{
			return container.data();
		}
	};


	template<unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	struct CString<MemoryBuffer<char,ChunkSizeT, ZeroTerminatedT,ExpandableT>* >
	{
	public:
		enum { valid = 1, converted = 0, };
	
	public:
		static const char* Buffer(const MemoryBuffer<char,ChunkSizeT, ZeroTerminatedT,ExpandableT>* container)
		{
			return container ? container->data() : NULL;
		}
	};



	template<unsigned int ChunkSizeT>
	struct CString<StringBase<char,ChunkSizeT> >
	{
	public:
		enum { valid = 1, converted = 0, };
	
	public:
		static const char* Buffer(const StringBase<char,ChunkSizeT>& container)
		{
			return container.c_str();
		}
	};



	template<unsigned int ChunkSizeT>
	struct CString<StringBase<char,ChunkSizeT>* >
	{
	public:
		enum { valid = 1, converted = 0, };
	
	public:
		static const char* Buffer(const StringBase<char,ChunkSizeT>* container)
		{
			return container ? container->c_str() : NULL;
		}
	};


	template<class T, class Alloc>
	struct CString<std::basic_string<char,T,Alloc> >
	{
	public:
		enum { valid = 1, converted = 0, };
	
	public:
		static const char* Buffer(const std::basic_string<char,T,Alloc>& container)
		{
			return container.c_str();
		}
	};


	template<class T, class Alloc>
	struct CString<std::basic_string<char,T,Alloc>* >
	{
	public:
		enum { valid = 1, converted = 0, };
	
	public:
		static const char* Buffer(const std::basic_string<char,T,Alloc>* container)
		{
			return container ? container->c_str() : NULL;
		}
	};





} // namespace Traits
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_TRAITS_C_STRING_H__
