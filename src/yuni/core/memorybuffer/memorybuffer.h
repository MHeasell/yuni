#ifndef __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_H__
# define __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_H__

# include "../../yuni.h"
# include "../static/remove.h"
# include "../static/assert.h"

# include "traits/length.h"
# include "traits/traits.h"
# include "traits/append.h"
# include "traits/assign.h"
# include "traits/fill.h"


namespace Yuni
{
namespace Core
{


	/*!
	** \brief A dynamic/static memory buffer for POD types
	**
	** The supported external types are the following :
	**  - C
	**  - C*
	**  - C[]
	**  - std::basic_string<C>
	**  - Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>Base<C>
	**  - Yuni::Core::MemoryBuffer<C>
	**
	** \tparam C A pod type
	** \tparam ChunkSizeT The size for a single chunk (>= 2)
	** \tparam ZeroTerminatedT A non-zero value if the buffer must always be terminated by a zero
	** \tparam ExpandableT A non-zero value to make a growable buffer. Otherwise it will be a simple
	**   buffer with a length equals to ChunkSizeT * sizeof(C)
	*/
	template<class C, unsigned int ChunkSizeT, bool ZeroTerminatedT, bool ExpandableT>
	class MemoryBuffer : public Private::MemoryBufferImpl::Data<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>
	{
	public:
		//! Ancestor
		typedef Private::MemoryBufferImpl::Data<C,ChunkSizeT,ZeroTerminatedT,ExpandableT>  AncestorType;
		//! Size type
		typedef typename AncestorType::Size Size;
		//! Size type (STL Compliant)
		typedef typename AncestorType::Size size_type;

		//! Type for the POD type
		typedef C Type;
		//! Type for the POD type (STL compliant)
		typedef C value_type;
		//! Self
		typedef MemoryBuffer<C,ChunkSizeT,ZeroTerminatedT, ExpandableT>  MemoryBufferType;

		enum
		{
			//! Size for a single chunk
			chunkSize = AncestorType::chunkSize,
			//! A non-zero value if the buffer must be zero terminated
			zeroTerminated = AncestorType::zeroTerminated,
			//! A non-zero value if the buffer can be expanded
			expandable = AncestorType::expandable,
		};

		static const Size npos = (Size)(-1);

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		MemoryBuffer();

		/*!
		** \brief Copy constructor
		*/
		MemoryBuffer(const MemoryBuffer& rhs);

		/*!
		** \brief Constructor with a default value
		*/
		template<class U> explicit MemoryBuffer(const U& rhs);

		/*!
		**
		*/
		MemoryBuffer(const C* block, const Size blockSize);

		//! Destructor
		~MemoryBuffer() {}
		//@}


		/*!
		** \brief Assign a new value to the buffer
		**
		** \param rhs Any supported value
		*/
		template<class U> void assign(const U& rhs);

		/*[!]
		** \brief Copy a raw buffer
		**
		** \param block A buffer
		** \param blockSize Size of the given buffer
		*/
		// void assign(const C* block, const Size blockSize); - from Ancestor

		/*!
		** \brief Append to the end of the buffer a new value
		**
		** \param rhs Any supported value
		*/
		template<class U> void append(const U& rhs);

		/*[!]
		** \brief Append a raw buffer
		**
		** \param block A buffer
		** \param blockSize Size of the given buffer
		*/
		// void append(const C* block, const Size blockSize); - from Ancestor

		/*[!]
		** \brief Append a single item (char)
		**
		** \param rhs A single item
		*/
		// void putc(const C rhs); - from Ancestor

		/*!
		** \brief
		*/
		template<class U> void fill(const U& pattern);

		//! \name Search
		//@{
		/*!
		** \brief Find the offset of a sub-string
		**
		** \param buffer An arbitrary string
		** \return The offset of the first sub-string found, npos otherwise
		*/
		Size find(const C buffer) const;

		/*!
		** \brief Find the offset of a raw sub-string with a given length (in bytes)
		**
		** \param buffer An arbitrary string
		** \param len Size of the given buffer
		** \return The offset of the first sub-string found, npos otherwise
		*/
		Size find(const C* buffer, const Size len) const;

		/*!
		** \brief Find the offset of a sub-string (equivalent to the method `find()`)
		**
		** \param buffer An arbitrary string
		** \return The offset of the first sub-string found, npos otherwise
		** \see find()
		*/
		template<class U> Size find_first_of(const U& u) const;
		//@}

		//! \name Remove / Erase
		//@{
		// From the ancestor
		/*[!]
		** \brief Empty the buffer
		*/
		// void clear();
		
		/*!
		** \brief Erase a part of the buffer
		**
		** \param offset The offset (zero-based) of the first item to erase
		** \param len The length (in number of items) to erase
		*/
		void erase(const Size offset, const Size len);


		void truncate(const Size newSize);

		Size size() const;

		Size capacity() const;

		/*!
		** \brief A pointer to the original buffer (might be NULL)
		*/
		const C* data() const;
		C* data();


		//! \name Operators
		//@{
		//! The operator `+=` (append)
		template<class U> MemoryBuffer& operator += (const U& rhs);
		//! The operator `<<` (append)
		template<class U> MemoryBuffer& operator << (const U& rhs);

		//! The operator `=` (assign - copy)
		MemoryBuffer& operator = (const MemoryBuffer& rhs);
		//! The operator `=` (assign)
		template<class U> MemoryBuffer& operator = (const U& rhs);

		bool operator < (const MemoryBuffer& rhs) const
		{
			return (!AncestorType::size || (AncestorType::size < rhs.size()
				&& ::memcmp(AncestorType::data, rhs.data(), AncestorType::size * sizeof(C)) <= 0));
		}

		bool operator > (const MemoryBuffer& rhs) const
		{
			return (AncestorType::size > rhs.size()
				&& ::memcmp(AncestorType::data, rhs.data(), rhs.size() * sizeof(C)) >= 0);
		}

		bool operator <= (const MemoryBuffer& rhs) const
		{
			return (!AncestorType::size || (AncestorType::size <= rhs.size()
				&& ::memcmp(AncestorType::data, rhs.data(), AncestorType::size * sizeof(C)) <= 0));
		}

		bool operator >= (const MemoryBuffer& rhs) const
		{
			return (AncestorType::size && AncestorType::size >= rhs.size()
				&& ::memcmp(AncestorType::data, rhs.data(), rhs.size() * sizeof(C)) >= 0);
		}

		bool operator == (const MemoryBuffer& rhs) const
		{
			return (AncestorType::size > 0 && AncestorType::size == rhs.size()
				&& !::memcmp(AncestorType::data, rhs.data(), AncestorType::size * sizeof(C)));
		}

		template<unsigned int C1, bool Z1, bool E1>
		bool operator == (const MemoryBuffer<C, C1, Z1, E1>& rhs) const
		{
			return (AncestorType::size == rhs.size()
				&& !::memcmp(AncestorType::data, rhs.data(), AncestorType::size * sizeof(C)));
		}

		//! The operator `!=`
		template<class U> bool operator != (const U& rhs) const;

		//! The operator `!`  (if (!s) ... - equivalent to if (!s.empty()))
		bool operator ! () const;
		//@}

	}; // class MemoryBuffer





} // namespace Core
} // namespace Yuni

# include "memoryBuffer.hxx"




//! \name Operator overload for stream printing
//@{

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline std::ostream& operator << (std::ostream& out, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	out.write(rhs.data(), rhs.size());
	return out;
}


template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator == (const U& u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs == u);
}

template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator != (const U& u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs != u);
}

template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator < (const U& u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs >= u);
}

template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator > (const U& u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs <= u);
}

template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator <= (const U& u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs > u);
}

template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator >= (const U& u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs < u);
}





template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>
operator + (const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs, const char* u)
{
	return Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>(rhs) += u;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>
operator + (const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs, const wchar_t* u)
{
	return Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>(rhs) += u;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>
operator + (const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs, const char u)
{
	return Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>(rhs) += u;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>
operator + (const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs, const wchar_t u)
{
	return Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>(rhs) += u;
}



template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>
operator + (const wchar_t* u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>(u) += rhs;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>
operator + (const char* u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>(u) += rhs;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>
operator + (const char u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>(u) += rhs;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>
operator + (const wchar_t u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>(u) += rhs;
}




template<class C, unsigned int SizeT, bool ZeroT, bool ExpT, class U>
inline Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>
operator + (const std::basic_string<U>& u, const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs)
{
	return Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>(u) += rhs;
}


template<class C, unsigned int SizeT, bool ZeroT, bool ExpT, class U>
inline Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>
operator + (const Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>& rhs, const std::basic_string<U>& u)
{
	return Yuni::Core::MemoryBuffer<C,SizeT,ZeroT,ExpT>(rhs) += u;
}

//@}


#endif // __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_H__
