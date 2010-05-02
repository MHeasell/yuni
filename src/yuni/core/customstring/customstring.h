#ifndef __YUNI_CORE_CUSTOMSTRING_CUSTOMSTRING_H__
# define __YUNI_CORE_CUSTOMSTRING_CUSTOMSTRING_H__

# include "../../yuni.h"
# include "../static/remove.h"
# include "../static/assert.h"
# include "../traits/cstring.h"
# include "../traits/length.h"
# include "../smartptr.h"

# include <stdio.h>
# include <stdarg.h>
# include <iostream>
# include <string>
# include <list>
# include <vector>

# include "traits/traits.h"
# include "traits/append.h"
# include "traits/assign.h"
# include "traits/fill.h"
# include "traits/vnsprintf.h"
# include "traits/into.h"



namespace Yuni
{

	/*!
	** \brief A string implementation
	**
	** The string class provides a useful way to manipulate and store sequences of
	** characters.
	**
	** This class is a template class, you should prefer the convenient alias
	** `Yuni::String`.
	**
	** The supported external types are the following :
	**  - C
	**  - char*
	**  - C[]
	**  - std::basic_string<cjar>
	**  - Yuni::CustomString<...>
	**  - SmartPtr<std::basic_string<char>, ...>
	**  - SmartPtr<CustomString<...>, ...>
	**
	** \warning This class is not thread-safe
	** \tparam char A pod type
	** \tparam ChunkSizeT The size for a single chunk (>= 2)
	** \tparam ZeroTerminatedT A non-zero value if the cstr must always be terminated by a zero
	** \tparam ExpandableT A non-zero value to make a growable cstr. Otherwise it will be a simple
	**   cstr with a length equals to ChunkSizeT * sizeof(char)
	*/
	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT>
	class CustomString
		:protected Private::CustomStringImpl::Data<ChunkSizeT,ExpandableT,ZeroTerminatedT, char>
	{
	public:
		//! POD type
		typedef char Char;
		//! Type for the POD type
		typedef char Type;

		//! Ancestor
		typedef Private::CustomStringImpl::Data<ChunkSizeT,ExpandableT,ZeroTerminatedT, char>  AncestorType;
		//! Size type
		typedef typename AncestorType::Size Size;
		//! Self
		typedef CustomString<ChunkSizeT,ExpandableT,ZeroTerminatedT>  CustomStringType;

		//! \name Compatibility with std::string
		//@{
		//! The type of object, charT, stored in the string
		typedef char value_type;
		//! Pointer to char
		typedef char* pointer;
		//! Reference to char
		typedef char& reference;
		//! Const reference to char
		typedef const char& const_reference;
		//! An unsigned integral type
		typedef Size size_type;
		//! A signed integral type
		typedef ssize_t difference_type;
		//@}

		//! Smartptr
		typedef SmartPtr<CustomStringType> Ptr;

		//! A String list
		typedef std::list<CustomStringType> List;
		//! A string list
		typedef std::list<typename CustomString::Ptr> ListPtr;
		//! A String vector
		typedef std::vector<CustomStringType> Vector;
		//! A String vector
		typedef std::vector<typename CustomStringType::Ptr> VectorPtr;

		enum
		{
			//! Size for a single chunk
			chunkSize          = AncestorType::chunkSize,
			//! A non-zero value if the cstr must be zero terminated
			zeroTerminated     = AncestorType::zeroTerminated,
			//! A non-zero value if the cstr can be expanded
			expandable         = AncestorType::expandable,
			//! Number of bits per element
			bitCountPerElement = sizeof(Char) * 8,

			//! Invalid offset
			npos = (Size)(-1),
		};

		//! char Case
		enum charCase
		{
			//! The string should remain untouched
			soCaseSensitive,
			//! The string should be converted to lowercase
			soIgnoreCase
		};

		// Checking for a minimal chunk size
		YUNI_STATIC_ASSERT(chunkSize > 3, CustomString_MinimalChunkSizeRequired);

	public:
		/*!
		** \brief Compare two string like strcmp()
		*/
		static int Compare(const char* s1, unsigned int l1, const char* s2, unsigned int l2);

		/*!
		** \brief Compare two string like strcmp() (insensitive)
		*/
		static int CompareInsensitive(const char* s1, unsigned int l1, const char* s2, unsigned int l2);


	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		CustomString();

		/*!
		** \brief Copy constructor
		*/
		CustomString(const CustomString& rhs);

		/*!
		** \brief Constructor with a null value
		*/
		CustomString(const NullPtr&);

		/*!
		** \brief Constructor from a mere CString
		*/
		CustomString(const char* block, const Size blockSize);

		/*!
		** \brief Constructor with a default value
		*/
		template<class U> CustomString(const U& rhs);

		//! Destructor
		~CustomString();
		//@}


		//! \name Append / Assign
		/*!
		** \brief Assign a new value to the cstr
		**
		** \param rhs Any supported value
		*/
		template<class U> void assign(const U& rhs);

		/*[!]
		** \brief Copy a raw cstr
		**
		** \param cstr A cstr
		** \param size Size of the given cstr
		*/
		void assign(const char* cstr, const Size size);

		/*!
		** \brief Append to the end of the cstr a new value
		**
		** \param rhs Any supported value
		*/
		template<class U> void append(const U& rhs);

		/*!
		** \brief Append to the end of the cstr a new value
		**
		** \param rhs Any supported value
		** \param size Size of the container
		*/
		template<class StringT> void append(const StringT& s, const Size size);

		//! \see template<class U> append(const U&, const Size)
		template<class U> void write(const U& cstr, const Size size);

		/*!
		** \brief Insert at the begining of the cstr a new value
		**
		** This is a convenient replacement for insert(0, u)
		** \param rhs Any supported value
		*/
		template<class U> void prepend(const U& u);

		/*!
		** \brief Insert at the begining of the cstr a new value
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
		void put(const char c);

		/*!
		** \brief Insert a raw cstr at a given position in the cstr
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param cstr A raw cstr
		** \param size Size of the cstr
		** \return True if the cstr has been inserted, false otherwise (size == 0 or offset out of bounds)
		*/
		bool insert(const Size offset, const char* cstr, const Size size);

		/*!
		** \brief Insert a single item at a given position in the cstr
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param c A single item
		** \return True if the cstr has been inserted, false otherwise (size == 0 or offset out of bounds)
		*/
		bool insert(const Size offset, const char c);

		/*!
		** \brief Insert an arbitrary CString container at a given position in the cstr
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param u Any CString container
		** \return True if the cstr has been inserted, false otherwise (size == 0 or offset out of bounds)
		*/
		template<class StringT> bool insert(const Size offset, const StringT& s);

		/*!
		** \brief Insert an arbitrary CString container at a given position in the cstr
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param s Any CString container
		** \param size The size to use for the given container
		** \return True if the cstr has been inserted, false otherwise (size == 0 or offset out of bounds)
		*/
		template<class StringT> bool insert(const Size offset, const StringT& u, const Size size);


		/*!
		** \brief Overwrite a region of the cstr
		**
		** The size of the cstr will remain untouched in any cases.
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param region A CString container
		*/
		template<class StringT> void overwrite(const Size offset, const StringT& s);

		/*!
		** \brief Overwrite a region of the cstr
		**
		** The size of the cstr will remain untouched in any cases.
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param region A raw cstr
		** \param size Size of the given cstr
		*/
		void overwrite(const Size offset, const char* region, const Size size);


		/*!
		** \brief Fill the whole cstr with a given pattern
		**
		** \code
		** CustomString<char>  cstr;
		** cstr.resize(80);
		**
		** // Preface
		** cstr.fill('.');
		** cstr.overwrite(0, " Preface ");
		** cstr.overwrite(78, " 1");
		** std::cout << cstr << std::endl;
		**
		** // Chapter 1
		** cstr.fill('.');
		** cstr.overwrite(0, " Chapter 1 ");
		** cstr.overwrite(78, " 4");
		** std::cout << cstr << std::endl;
		** \endcode
		*/
		template<class StringT> void fill(const StringT& pattern);

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
		** \param cstr An arbitrary string
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		Size find(const char c) const;

		/*!
		** \brief Find the offset of a sub-string from the left
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param cstr An arbitrary string
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		Size indexOf(Size offset, const char cstr) const;

		/*!
		** \brief Find the offset of a raw sub-string with a given length (in bytes)
		**
		** \param cstr An arbitrary string
		** \param len Size of the given cstr
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		Size find(const char* cstr, const Size len) const;

		/*!
		** \brief Find the offset of a raw sub-string with a given length (in bytes) from the left
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param cstr An arbitrary string
		** \param len Size of the given cstr
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		Size indexOf(Size offset, const char* cstr, const Size len) const;

		/*!
		** \brief Find the offset of any supported CString
		**
		** \param cstr Any supported CString
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		template<class StringT> Size find(const StringT& s) const;

		/*!
		** \brief Find the offset of any supported CString from the left
		**
		** \param offset Position of the first character in the string to be taken into consideration for possible matches. A value of 0 means that the entire string is considered
		** \param cstr Any supported CString
		** \return The offset of the first sub-string found, `npos` if not found
		*/
		template<class StringT> Size indexOf(Size offset, const StringT& s) const;

		/*!
		** \brief Find the offset of a sub-string (equivalent to the method `find()`)
		**
		** \param cstr An arbitrary string
		** \return The offset of the first sub-string found, `npos` if not found
		** \see find()
		*/
		template<class StringT> Size find_first_of(const StringT& u) const;

		/*!
		** \brief Get if a given string can be found at the begining of the cstr
		*/
		bool startsWith(const char* cstr, const Size len) const;

		/*!
		** \brief Get if a given string can be found at the begining of the cstr
		*/
		template<class StringT> bool startsWith(const StringT& s) const;

		/*!
		** \brief Get if a given string can be found at the end of the cstr
		*/
		bool endsWith(const char* cstr, const Size len) const;

		/*!
		** \brief Get if a given string can be found at the end of the cstr
		** \param s Any string
		*/
		template<class StringT> bool endsWith(const StringT& s) const;
		//@}


		//! \name Trimming
		//@{
		/*!
		** \brief Remove all white-spaces (" \t\r\n") from the begining and the end of the cstr
		*/
		void trim();
		/*!
		** \brief Remove all white-spaces from the begining and the end of the cstr
		*/
		void trim(const char c);
		/*!
		** \brief Removes all items equal to one of those in 'whitespaces' from the end of the cstr
		*/
		template<class StringT> void trim(const StringT& whitespaces);

		/*!
		** \brief Removes all items equal to one of those in 'u' from the end of the cstr
		*/
		template<class StringT> void trimRight(const StringT& whitespaces);

		/*!
		** \brief Remove all items equal to 'c' from the end of the cstr
		*/
		void trimRight(const char c);

		/*!
		** \brief Removes all items equal to one of those in 'u' from the begining of the cstr
		*/
		template<class StringT> void trimLeft(const StringT& whitespaces);
		/*!
		** \brief Remove all items equal to 'c' from the begining of the cstr
		*/
		void trimLeft(const char c);
		//@}


		//! \name Remove / Erase
		//@{
		// From the ancestor
		/*!
		** \brief Empty the cstr
		** \return *this
		*/
		CustomString& clear();

		/*!
		** \brief Erase a part of the cstr
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


		//! \name Case conversion
		//@{
		/*!
		** \brief Convert the case (lower case) of characters in the string (O(N))
		*/
		CustomString& toLower();
		/*!
		** \brief Convert the case (upper case) of characters in the string (O(N))
		*/
		CustomString& toUpper();
		//@}


		//! \name Conversions
		//@{
		/*!
		** \brief Convert the cstr into something else
		**
		** The supported types (by default) are :
		** - std::string
		** - const char* (equivalent to `c_str()`)
		** - numeric (int, long, unsigned int, double...)
		** - bool
		*/
		template<class U> U to() const;

		/*!
		** \brief Convert the string into something else
		**
		** This method is strictly equivalent to `to()`, except
		** that we know if the conversion succeeded or not.
		*/
		template<class U> bool to(U& out) const;
		//@}


		//! \name Memory management
		//@{
		/*!
		** \brief Get the item at a given position in a safe way
		**
		** Contrary to the operator [], it is safe to use an invalid offset
		** \return The item at position 'offset', a default value if the offset is out of bound
		*/
		char at(const Size offset) const;

		/*!
		** \brief Truncate the cstr to the given length
		**
		** Nothing will be done if the new size if greater than the current one.
		** \param newSize The new size of the cstr
		*/
		void truncate(const Size newSize);

		/*!
		** \brief Ensure that there is enough allocated space for X caracters
		**
		** \param min The minimum capacity of the cstr (in caracters)
		*/
		void reserve(Size minCapacity);

		/*!
		** \brief Resize the cstr to 'len' bytes
		**
		** The current content will remain untouched but all extra bytes will not be
		** initialized.
		** If the cstr can not be expanded, the new size will not greater than 'ChunkSize'.
		**
		** \param len The new length of the string
		*/
		void resize(const Size len);

		/*!
		** \brief Get the current size of the cstr (in number of element C)
		**
		** The returned value is less than or equal to the capacity.
		*/
		Size size() const;
		//! \see size()
		Size length() const;

		/*!
		** \brief Get the current size of the cstr (in bytes)
		*/
		uint64 sizeInBytes() const;

		/*!
		** \brief Get if the cstr is empty
		**
		** \code
		** CustomString<> s;
		** s.empty();          // returns true
		** s.null();           // returns true
		**
		** s = "hello world";  // returns false
		** s.empty();          // returns false
		** s.null();           // returns false
		**
		** s.clear();
		** s.empty();          // returns true
		** s.null();           // returns false
		**
		** s.shrink();
		** s.empty();          // returns true
		** s.null();           // returns true
		** \endcode
		*/
		bool empty() const;

		/*!
		** \brief Get if the cstr is null
		**
		** A null cstr means that no space is reserved, and that the
		** method `data()` will return NULL.
		**
		** \code
		** CustomString<> s;
		** s.empty();          // returns true
		** s.null();           // returns true
		**
		** s = "hello world";  // returns false
		** s.empty();          // returns false
		** s.null();           // returns false
		**
		** s.clear();
		** s.empty();          // returns true
		** s.null();           // returns false
		**
		** s.shrink();
		** s.empty();          // returns true
		** s.null();           // returns true
		** \endcode
		*/
		bool null() const;

		/*!
		** \brief Get if the cstr is not empty (the exact opposite of `empty()`)
		*/
		bool notEmpty() const;

		/*!
		** \brief Get the current capacity of the cstr (in number of element C)
		** \return A value greater or equal to `size()`
		*/
		Size capacity() const;

		/*!
		** \brief Get the current capacity of the cstr (in bytes)
		** \return A value greater or equal to `sizeInBytes()`
		*/
		uint64 capacityInBytes() const;

		/*!
		** \brief A pointer to the original cstr (might be NULL)
		** \see null()
		*/
		const char* c_str() const;

		/*!
		** \brief A pointer to the original cstr (might be NULL)
		** \see null()
		*/
		const char* data() const;
		char* data();
		//@}


		//! \name Formatted buffer
		//@{
		/*!
		** \brief Reset the current value with a formatted string
		**
		** The format is the standard printf format.
		** \param format The format, reprensented by a zero-terminated string
		** \return Always *this
		*/
		template<class StringT> CustomString& format(const StringT& format, ...);

		/*!
		** \brief Append formatted string
		**
		** The format is the standard printf format.
		** \param format The format, reprensented by a zero-terminated string
		** \return Always *this
		*/
		template<class StringT> CustomString& appendFormat(const StringT& format, ...);

		/*!
		** \brief Append a formatted string to the end of the current string
		**
		** The format is the standard printf format.
		** \param format The format, represented by a zero-terminated C-String
		*/
		void vappendFormat(const char* format, va_list args);
		//@}


		//! \name Misc
		//@{
		/*!
		** \brief Convert all backslashes into slashes
		*/
		void convertBackslashesIntoSlashes();

		/*!
		** \brief Convert all slashes into backslashes
		*/
		void convertSlashesIntoBackslashes();

		/*!
		** \brief Explode a string into several segments
		**
		** Here is an example of how to convert a string to a list of int :
		** \code
		** std::list<int>  list;
		** String("22::80::443::993").explode(list, ":");
		** std::cout << list << std::endl;
		** \endcode
		**
		** \param[out] out All segments that have been found
		** \param sep Sequence of chars considered as a separator
		** \param keepEmptyElements True to keep empty items
		** \param trimElements Trim each item found
		** \param emptyBefore True to clear the vector before fulfill it
		**
		** \warning Do not take care of string representation (with `'` or `"`)
		*/
		template<template<class,class> class U, class UType, class Alloc, typename StringT>
		void explode(U<UType,Alloc>& out, const StringT& sep,
			bool keepEmptyElements = false, bool trimElements = true, bool emptyBefore = true) const;

		/*!
		** \brief Dupplicate N times the content of the string
		*/
		void dupplicate(int n);
		//@}


		//! \name Operators
		//@{
		//! The operator `[]` (the offset must be valid)
		const char& operator [] (const Size offset) const;
		char& operator [] (const Size offset);
		const char& operator [] (const int offset) const;
		char& operator [] (const int offset);
		//! The operator `+=` (append)
		template<class U> CustomString& operator += (const U& rhs);
		//! The operator `<<` (append)
		template<class U> CustomString& operator << (const U& rhs);

		//! The operator `=` (assign - copy)
		CustomString& operator = (const CustomString& rhs);
		//! The operator `=` (assign)
		template<class U> CustomString& operator = (const U& rhs);

		//! The operator `<`
		template<class StringT> bool operator <  (const StringT& rhs) const;
		//! The operator `>`
		template<class StringT> bool operator >  (const StringT& rhs) const;

		//! The operator `<=`
		template<class StringT> bool operator <= (const StringT& rhs) const;
		//! The operator `>=`
		template<class StringT> bool operator >= (const StringT& rhs) const;

		//! The operator `==`
		bool operator == (const CustomString& rhs) const;
		//! The operator `==`
		template<class StringT> bool operator == (const StringT& rhs) const;

		//! The operator `!=`
		template<class StringT> bool operator != (const StringT& rhs) const;

		//! The operator `!`  (if (!s) ... - equivalent to if (s.empty()))
		bool operator ! () const;

		//! The operator *=, to dupplicate N times the content of the string
		CustomString& operator *= (int n);
		//@}


	protected:
		//! Assign without checking for pointer validity
		Size assignWithoutChecking(const char* block, const Size blockSize);
		//! Append without checking for pointer validity
		Size appendWithoutChecking(const char* block, const Size blockSize);
		//! Append without checking for pointer validity
		Size appendWithoutChecking(const char c);
		//! Assign without checking for pointer validity
		Size assignWithoutChecking(const char c);

	private:
		// our friends !
		template<class, class, int> friend class Private::CustomStringImpl::From;
		template<class, class> friend struct Yuni::Extension::CustomString::Append;
		template<class, class> friend struct Yuni::Extension::CustomString::Assign;
		template<class, class> friend struct Yuni::Extension::CustomString::Fill;

	}; // class CustomString





} // namespace Yuni

# include "customstring.hxx"




//! \name Operator overload for stream printing
//@{

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline std::ostream& operator << (std::ostream& out, const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs)
{
	out.write(rhs.data(), rhs.size());
	return out;
}





template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CustomString<SizeT,ExpT,ZeroT>
operator + (const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs, const char* u)
{
	return Yuni::CustomString<SizeT,ExpT,ZeroT>(rhs) += u;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CustomString<SizeT,ExpT,ZeroT>
operator + (const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs, const wchar_t* u)
{
	return Yuni::CustomString<SizeT,ExpT,ZeroT>(rhs) += u;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CustomString<SizeT,ExpT,ZeroT>
operator + (const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs, const char u)
{
	return Yuni::CustomString<SizeT,ExpT,ZeroT>(rhs) += u;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CustomString<SizeT,ExpT,ZeroT>
operator + (const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs, const wchar_t u)
{
	return Yuni::CustomString<SizeT,ExpT,ZeroT>(rhs) += u;
}



template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CustomString<SizeT,ExpT,ZeroT>
operator + (const wchar_t* u, const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs)
{
	return Yuni::CustomString<SizeT,ExpT,ZeroT>(u) += rhs;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CustomString<SizeT,ExpT,ZeroT>
operator + (const char* u, const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs)
{
	return Yuni::CustomString<SizeT,ExpT,ZeroT>(u) += rhs;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CustomString<SizeT,ExpT,ZeroT>
operator + (const char u, const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs)
{
	return Yuni::CustomString<SizeT,ExpT,ZeroT>(u) += rhs;
}

template<unsigned int SizeT, bool ExpT,bool ZeroT>
inline Yuni::CustomString<SizeT,ExpT,ZeroT>
operator + (const wchar_t u, const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs)
{
	return Yuni::CustomString<SizeT,ExpT,ZeroT>(u) += rhs;
}




template<unsigned int SizeT, bool ExpT,bool ZeroT, class U>
inline Yuni::CustomString<SizeT,ExpT,ZeroT>
operator + (const std::basic_string<U>& u, const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs)
{
	return Yuni::CustomString<SizeT,ExpT,ZeroT>(u) += rhs;
}


template<unsigned int SizeT, bool ExpT,bool ZeroT, class U>
inline Yuni::CustomString<SizeT,ExpT,ZeroT>
operator + (const Yuni::CustomString<SizeT,ExpT,ZeroT>& rhs, const std::basic_string<U>& u)
{
	return Yuni::CustomString<SizeT,ExpT,ZeroT>(rhs) += u;
}

//@}


#endif // __YUNI_CORE_CUSTOMSTRING_CUSTOMSTRING_H__
