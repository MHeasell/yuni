#ifndef __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_H__
# define __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_H__

# include "../../yuni.h"
# include "../static/remove.h"
# include "../static/assert.h"
# include "../traits/cstring.h"
# include "../traits/length.h"

# include <stdio.h>
# include "traits/traits.h"
# include "traits/append.h"
# include "traits/assign.h"
# include "traits/fill.h"

# include <iostream>


namespace Yuni
{


	/*!
	** \brief A dynamic/static memory buffer for POD types
	**
	** The supported external types are the following :
	**  - C
	**  - C*
	**  - C[]
	**  - std::basic_string<C>
	**  - Yuni::IString<...>
	**
	**
	** \tparam C A pod type
	** \tparam ChunkSizeT The size for a single chunk (>= 2)
	** \tparam ZeroTerminatedT A non-zero value if the buffer must always be terminated by a zero
	** \tparam ExpandableT A non-zero value to make a growable buffer. Otherwise it will be a simple
	**   buffer with a length equals to ChunkSizeT * sizeof(C)
	*/
	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	class IString : protected Private::IStringImpl::Data<ChunkSizeT,ZeroTerminatedT,ExpandableT,C>
	{
	public:
		//! Ancestor
		typedef Private::IStringImpl::Data<ChunkSizeT,ZeroTerminatedT,ExpandableT,C>  AncestorType;
		//! Size type
		typedef typename AncestorType::Size Size;
		//! Size type (STL Compliant)
		typedef typename AncestorType::Size size_type;

		//! Type for the POD type
		typedef C Type;
		//! Type for the POD type (STL compliant)
		typedef C value_type;
		//! Self
		typedef IString<ChunkSizeT,ExpandableT,ZeroTerminatedT,C>  IStringType;

		enum
		{
			//! Size for a single chunk
			chunkSize = AncestorType::chunkSize,
			//! A non-zero value if the buffer must be zero terminated
			zeroTerminated = AncestorType::zeroTerminated,
			//! A non-zero value if the buffer can be expanded
			expandable = AncestorType::expandable,
			//! Number of bits per element
			bitCountPerElement = sizeof(C) * 8,

			//! Invalid offset
			npos = (Size)(-1),
		};


	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		IString();

		/*!
		** \brief Copy constructor
		*/
		IString(const IString& rhs);

		/*!
		** \brief Constructor with a null value
		*/
		IString(const NullPtr&);
		IString(const NullPtr*);

		/*!
		** \brief Constructor with a default value
		*/
		template<class U> explicit IString(const U& rhs);

		/*!
		**
		*/
		IString(const C* block, const Size blockSize);

		//! Destructor
		~IString() {}
		//@}


		//! \name Append / Assign
		/*!
		** \brief Assign a new value to the buffer
		**
		** \param rhs Any supported value
		*/
		template<class U> void assign(const U& rhs);

		/*[!]
		** \brief Copy a raw buffer
		**
		** \param buffer A buffer
		** \param size Size of the given buffer
		*/
		void assign(const C* buffer, const Size size);

		/*!
		** \brief Append to the end of the buffer a new value
		**
		** \param rhs Any supported value
		*/
		template<class U> void append(const U& rhs);

		/*!
		** \brief Append to the end of the buffer a new value
		**
		** \param rhs Any supported value
		** \param size Size of the container
		*/
		template<class U> void append(const U& u, const Size size);

		//! \see append(const U*, const Size)
		void write(const C* buffer, const Size size);

		/*!
		** \brief Append a raw buffer
		**
		** \param buffer A buffer
		** \param size Size of the given buffer
		*/
		void append(const C* buffer, const Size size);

		/*!
		** \brief Insert at the begining of the buffer a new value
		**
		** This is a convenient replacement for insert(0, u)
		** \param rhs Any supported value
		*/
		template<class U> void prepend(const U& u);

		/*!
		** \brief Insert at the begining of the buffer a new value
		**
		** \param rhs Any supported value
		** \param size Size of the container
		*/
		template<class U> void prepend(const U& u, const Size size);

		/*!
		** \brief Append a single item (char)
		**
		** \param rhs A single item
		*/
		void put(const C c);

		/*!
		** \brief Insert a raw buffer at a given position in the buffer
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param buffer A raw buffer
		** \param size Size of the buffer
		** \return True if the buffer has been inserted, false otherwise (size == 0 or offset out of bounds)
		*/
		bool insert(const Size offset, const C* buffer, const Size size);

		/*!
		** \brief Insert a single item at a given position in the buffer
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param c A single item
		** \return True if the buffer has been inserted, false otherwise (size == 0 or offset out of bounds)
		*/
		bool insert(const Size offset, const C c);

		/*!
		** \brief Insert an arbitrary CString container at a given position in the buffer
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param u Any CString container
		** \return True if the buffer has been inserted, false otherwise (size == 0 or offset out of bounds)
		*/
		template<class U> bool insert(const Size offset, const U& u);

		/*!
		** \brief Insert an arbitrary CString container at a given position in the buffer
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param u Any CString container
		** \param size The size to use the given container
		** \return True if the buffer has been inserted, false otherwise (size == 0 or offset out of bounds)
		*/
		template<class U> bool insert(const Size offset, const U& u, const Size size);


		/*!
		** \brief Overwrite a region of the buffer
		**
		** The size of the buffer will remain untouched in any cases.
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param region A CString container
		*/
		template<class U> void overwrite(const Size offset, const U& u);

		/*!
		** \brief Overwrite a region of the buffer
		**
		** The size of the buffer will remain untouched in any cases.
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param region A raw buffer
		** \param size Size of the given buffer
		*/
		void overwrite(const Size offset, const C* region, const Size size);


		/*!
		** \brief Fill the whole buffer with a given pattern
		**
		** \code
		** IString<char>  buffer;
		** buffer.resize(80);
		**
		** // Preface
		** buffer.fill('.');
		** buffer.overwrite(0, " Preface ");
		** buffer.overwrite(78, " 1");
		** std::cout << buffer << std::endl;
		**
		** // Chapter 1
		** buffer.fill('.');
		** buffer.overwrite(0, " Chapter 1 ");
		** buffer.overwrite(78, " 4");
		** std::cout << buffer << std::endl;
		** \endcode
		*/
		template<class U> void fill(const U& pattern);

		//! Equivalent to append()
		template<class U> void push_back(const U& u);

		//! Equivalent to prepend()
		template<class U> void push_front(const U& u);
		//@}


		//! \name Search / Replace
		//@{
		/*!
		** \brief Find the offset of a sub-string
		**
		** \param buffer An arbitrary string
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		Size find(const C buffer) const;

		/*!
		** \brief Find the offset of a sub-string from the left
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param buffer An arbitrary string
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		Size indexOf(Size offset, const C buffer) const;

		/*!
		** \brief Find the offset of a raw sub-string with a given length (in bytes)
		**
		** \param buffer An arbitrary string
		** \param len Size of the given buffer
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		Size find(const C* buffer, const Size len) const;

		/*!
		** \brief Find the offset of a raw sub-string with a given length (in bytes) from the left
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param buffer An arbitrary string
		** \param len Size of the given buffer
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		Size indexOf(Size offset, const C* buffer, const Size len) const;

		/*!
		** \brief Find the offset of any supported CString
		**
		** \param buffer Any supported CString
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		template<class U> Size find(const U& u) const;

		/*!
		** \brief Find the offset of any supported CString from the left
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param buffer Any supported CString
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		template<class U> Size indexOf(Size offset, const U& u) const;

		/*!
		** \brief Find the offset of a sub-string (equivalent to the method `find()`)
		**
		** \param buffer An arbitrary string
		** \return The offset of the first sub-string found, `npos` if not found
		** \see find()
		*/
		template<class U> Size find_first_of(const U& u) const;

		/*!
		** \brief Get if a given string can be found at the begining of the buffer
		*/
		bool startsWith(const C* buffer, const Size len) const;

		/*!
		** \brief Get if a given string can be found at the begining of the buffer
		*/
		template<class U> bool startsWith(const U& u) const;

		/*!
		** \brief Get if a given string can be found at the end of the buffer
		*/
		bool endsWith(const C* buffer, const Size len) const;

		/*!
		** \brief Get if a given string can be found at the end of the buffer
		*/
		template<class U> bool endsWith(const U& u) const;
		//@}


		//! \name Trimming
		//@{
		/*!
		** \brief Remove all white-spaces from the begining and the end of the buffer
		*/
		void trim(const C c /* = ' ' */);
		/*!
		** \brief Removes all items equal to one of those in 'u' from the end of the buffer
		*/
		template<class U> void trim(const U& u = " \t");

		/*!
		** \brief Removes all items equal to one of those in 'u' from the end of the buffer
		*/
		template<class U> void trimRight(const U& u = " \t");

		/*!
		** \brief Remove all items equal to 'c' from the end of the buffer
		*/
		void trimRight(const C c);

		/*!
		** \brief Removes all items equal to one of those in 'u' from the begining of the buffer
		*/
		template<class U> void trimLeft(const U& u = " \t");
		/*!
		** \brief Remove all items equal to 'c' from the begining of the buffer
		*/
		void trimLeft(const C c);
		//@}

		//! \name Remove / Erase
		//@{
		// From the ancestor
		/*!
		** \brief Empty the buffer
		** \return *this
		*/
		IString& clear();

		/*!
		** \brief Erase a part of the buffer
		**
		** \param offset The offset (zero-based) of the first item to erase
		** \param len The length (in number of items) to erase
		*/
		void erase(const Size offset, const Size len);

		/*!
		** \brief Remove the 'n' first items
		*/
		void consume(const Size n);
		//@}


		//! \name Memory management
		//@{
		/*!
		** \brief Get the item at a given position in a safe way
		**
		** Contrary to the operator [], it is safe to use an invalid offset
		** \return The item at position 'offset', a default value if the offset is out of bound
		*/
		C at(const Size offset) const;

		/*!
		** \brief Truncate the buffer to the given length
		**
		** Nothing will be done if the new size if greater than the current one.
		** \param newSize The new size of the buffer
		*/
		void truncate(const Size newSize);

		/*!
		** \brief Ensure that there is enough allocated space for X caracters
		**
		** \param min The minimum capacity of the buffer (in caracters)
		*/
		void reserve(Size minCapacity);

		/*!
		** \brief Resize the buffer to 'len' bytes
		**
		** The current content will remain untouched but all extra bytes will not be
		** initialized.
		** If the buffer can not be expanded, the new size will not greater than 'ChunkSize'.
		**
		** \param len The new length of the string
		*/
		void resize(const Size len);

		/*!
		** \brief Get the current size of the buffer (in number of element C)
		**
		** The returned value is less than or equal to the capacity.
		*/
		Size size() const;

		/*!
		** \brief Get the current size of the buffer (in bytes)
		*/
		uint64 sizeInBytes() const;

		/*!
		** \brief Get if the buffer is empty
		*/
		bool empty() const;

		/*!
		** \brief Get if the buffer is not empty
		*/
		bool notEmpty() const;

		/*!
		** \brief Get the current capacity of the buffer (in number of element C)
		*/
		Size capacity() const;

		/*!
		** \brief Get the current capacity of the buffer (in bytes)
		*/
		uint64 capacityInBytes() const;

		/*!
		** \brief A pointer to the original buffer (might be NULL)
		*/
		const C* c_str() const;

		/*!
		** \brief A pointer to the original buffer (might be NULL)
		*/
		const C* data() const;
		C* data();
		//@}


		//! \name Operators
		//@{
		//! The operator `[]` (the offset must be valid)
		const C& operator [] (const Size offset) const;
		C& operator [] (const Size offset);
		//! The operator `+=` (append)
		template<class U> IString& operator += (const U& rhs);
		//! The operator `<<` (append)
		template<class U> IString& operator << (const U& rhs);

		//! The operator `=` (assign - copy)
		IString& operator = (const IString& rhs);
		//! The operator `=` (assign)
		template<class U> IString& operator = (const U& rhs);

		//! The operator `<`
		bool operator < (const IString& rhs) const;
		//! The operator `>`
		bool operator > (const IString& rhs) const;
		//! The operator `<=`
		bool operator <= (const IString& rhs) const;
		//! The operator `>=`
		bool operator >= (const IString& rhs) const;

		//! The operator `==`
		bool operator == (const IString& rhs) const;
		//! The operator `==`
		template<unsigned int C1, bool E1, bool Z1>
		bool operator == (const IString<C1, E1, Z1, C>& rhs) const;

		//! The operator `!=`
		template<class U> bool operator != (const U& rhs) const;

		//! The operator `!`  (if (!s) ... - equivalent to if (!s.empty()))
		bool operator ! () const;
		//@}


	protected:
		//! Assign without checking for pointer validity
		Size assignWithoutChecking(const C* block, const Size blockSize);
		//! Append without checking for pointer validity
		Size appendWithoutChecking(const C* block, const Size blockSize);
		//! Append without checking for pointer validity
		Size appendWithoutChecking(const C c);
		//! Assign without checking for pointer validity
		Size assignWithoutChecking(const C c);

	private:
		// our friends !
		template<class, class, int> friend class Private::IStringImpl::From;
		template<class, class> friend class Private::IStringImpl::Append;
		template<class, class> friend class Private::IStringImpl::Assign;
		template<class, class> friend class Private::IStringImpl::Fill;

	}; // class IString






} // namespace Yuni

# include "istring.hxx"




//! \name Operator overload for stream printing
//@{

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline std::ostream& operator << (std::ostream& out, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	out.write(rhs.data(), rhs.size());
	return out;
}


template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator == (const U& u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs == u);
}

template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator != (const U& u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs != u);
}

template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator < (const U& u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs >= u);
}

template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator > (const U& u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs <= u);
}

template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator <= (const U& u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs > u);
}

template<class U, class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline bool operator >= (const U& u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return (rhs < u);
}





template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::IString<C,SizeT,ZeroT,ExpT>
operator + (const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs, const char* u)
{
	return Yuni::IString<C,SizeT,ZeroT,ExpT>(rhs) += u;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::IString<C,SizeT,ZeroT,ExpT>
operator + (const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs, const wchar_t* u)
{
	return Yuni::IString<C,SizeT,ZeroT,ExpT>(rhs) += u;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::IString<C,SizeT,ZeroT,ExpT>
operator + (const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs, const char u)
{
	return Yuni::IString<C,SizeT,ZeroT,ExpT>(rhs) += u;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::IString<C,SizeT,ZeroT,ExpT>
operator + (const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs, const wchar_t u)
{
	return Yuni::IString<C,SizeT,ZeroT,ExpT>(rhs) += u;
}



template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::IString<C,SizeT,ZeroT,ExpT>
operator + (const wchar_t* u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return Yuni::IString<C,SizeT,ZeroT,ExpT>(u) += rhs;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::IString<C,SizeT,ZeroT,ExpT>
operator + (const char* u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return Yuni::IString<C,SizeT,ZeroT,ExpT>(u) += rhs;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::IString<C,SizeT,ZeroT,ExpT>
operator + (const char u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return Yuni::IString<C,SizeT,ZeroT,ExpT>(u) += rhs;
}

template<class C, unsigned int SizeT, bool ZeroT, bool ExpT>
inline Yuni::IString<C,SizeT,ZeroT,ExpT>
operator + (const wchar_t u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return Yuni::IString<C,SizeT,ZeroT,ExpT>(u) += rhs;
}




template<class C, unsigned int SizeT, bool ZeroT, bool ExpT, class U>
inline Yuni::IString<C,SizeT,ZeroT,ExpT>
operator + (const std::basic_string<U>& u, const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs)
{
	return Yuni::IString<C,SizeT,ZeroT,ExpT>(u) += rhs;
}


template<class C, unsigned int SizeT, bool ZeroT, bool ExpT, class U>
inline Yuni::IString<C,SizeT,ZeroT,ExpT>
operator + (const Yuni::IString<C,SizeT,ZeroT,ExpT>& rhs, const std::basic_string<U>& u)
{
	return Yuni::IString<C,SizeT,ZeroT,ExpT>(rhs) += u;
}

//@}


#endif // __YUNI_CORE_MEMORY_BUFFER_MEMORY_BUFFER_H__
