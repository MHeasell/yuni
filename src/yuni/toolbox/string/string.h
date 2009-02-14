#ifndef __YUNI_TOOLBOX_STRING_STRING_H__
# define __YUNI_TOOLBOX_STRING_STRING_H__

# include <sstream>
# include <algorithm>
# include <list>
# include <vector>
# include <string>
# include <cstdarg>
# include "../../yuni.h"
# include "../static/assert.h"


//! \name Macros for Yuni::String
//@{

//! Macro to append some data to the string
# define YUNI_WSTR_APPEND	  std::stringstream out; \
								out << v; \
								static_cast<std::string*>(this)->append(out.str());\
								return *this

//! Macro to convert the string into a given type
# define YUNI_WSTR_CAST_OP(X)	if (this->empty()) \
									return def; \
								X v; \
								fromString<X>(v, *this, std::dec); \
								return v;

//! Macro to append the value of a boolean (true -> "true", false -> "false")
# define YUNI_WSTR_APPEND_BOOL(X)   static_cast<std::string*>(this)->append(X ? "true" : "false")

//@} // Macros for Yuni::String


# define YUNI_WSTR_SEPARATORS  " \t\r\n"



namespace Yuni
{

	/*!
	** \brief A String implementation for the Yuni framework 
	** \ingroup Toolbox
	**
	** Examples :
	**
	** \code
	**	  Yuni::String a("abcd");
	**	  std::cout << a << std::endl;  // display: `abcd`
	**	  Yuni::String b(10 + 2);
	**	  std::cout << b << std::endl;  // display: `12`
	**	  Yuni::String c(10.3);
	**	  std::cout << c << std::endl;  // display: `10.3`
	**
	**	  // The same with the operator `<<`
	**	  Yuni::String d;
	**	  d << "Value : " << 42;
	**	  std::cout << d << std::endl;  // display: `Value : 42`
	** \endcode
	**
	** \code
	**	  Yuni::String s = "HelLo wOrLd";
	**	  std::cout << Yuni::String::ToLower(s) << std::endl;  // `hello world`
	**	  std::cout << s << std::endl;  // `HelLo wOrLd`
	**	  std::cout << s.toLower() << std::endl;  // `hello world`
	**	  std::cout << s << std::endl;  // `hello world`
	** \endcode
	**
	** \code
	** 	 Yuni::String::Vector list;
	** 	 list.push_back("BMW");
	** 	 list.push_back("Audi");
	** 	 list.push_back("Ferrari");
	** 	 list.push_back("9FF");
	**
	** 	 std::cout << list << std::endl; // BMW, Audi, Ferrari, 9FF 
	**
	** 	 String s;
	** 	 s.append(list, ", ", "`");
	** 	 std::cout << s << std::endl; // `BMW`, `Audi`, `Ferrari`, `9FF`
	** \endcode
	*/
	class String : public std::string
	{
	public:
		//! A String list
		typedef std::list<String> List;
		//! A String vector
		typedef std::vector<String> Vector;

		//! Alias to the size type
		typedef std::string::size_type Size;
		//! Index type
		typedef std::string::size_type Index;
		
		//! Alias to the type of a char
		typedef std::string::value_type Char;
		
		//! iterator
		typedef std::string::iterator iterator;
		//! const_iterator
		typedef std::string::const_iterator  const_iterator;
		
		//! Char Case
		enum CharCase
		{
			//! The string should remain untouched
			soCaseSensitive,
			//! The string should be converted to lowercase
			soIgnoreCase
		};

	public:
		/*!
		** \brief Copy then Convert the case (lower case) of characters in the string using the UTF8 charset
		** \param s The string to convert
		** \return A new string
		*/
		static String ToLower(const char* s) {return String(s).toLower();}
		/*!
		** \brief Copy then Convert the case (lower case) of characters in the string using the UTF8 charset
		** \param s The string to convert
		** \return A new string
		*/
		static String ToLower(const wchar_t* s) {return String(s).toLower();}
		/*!
		** \brief Copy then Convert the case (lower case) of characters in the string using the UTF8 charset
		** \param s The string to convert
		** \return A new string
		*/
		static String ToLower(const String& s) {return String(s).toLower();}

		/*!
		** \brief Copy then Convert the case (upper case) of characters in the string using the UTF8 charset
		** \param s The string to convert
		** \return A new string
		*/
		static String ToUpper(const char* s) {return String(s).toUpper();}
		/*!
		** \brief Copy then Convert the case (upper case) of characters in the string using the UTF8 charset
		** \param s The string to convert
		** \return A new string
		*/
		static String ToUpper(const wchar_t* s) {return String(s).toUpper();}
		/*!
		** \brief Copy then Convert the case (upper case) of characters in the string using the UTF8 charset
		** \param s The string to convert
		** \return A new string
		*/
		static String ToUpper(const String& s) {return String(s).toUpper();}

		/*!
		** \brief Remove trailing and leading spaces
		** \param s The string to convert
		** \param trimChars The chars to remove
		** \return A new string
		*/
		static String Trim(const char* s, const String& trimChars = YUNI_WSTR_SEPARATORS) {return String(s).trim(trimChars);}
		/*!
		** \brief Remove trailing and leading spaces
		** \param s The string to convert
		** \param trimChars The chars to remove
		** \return A new string
		*/
		static String Trim(const wchar_t* s, const String& trimChars = YUNI_WSTR_SEPARATORS) {return String(s).trim(trimChars);}
		/*!
		** \brief Remove trailing and leading spaces
		** \param s The string to convert
		** \param trimChars The chars to remove
		** \return A new string
		*/
		static String Trim(const String& s, const String& trimChars = YUNI_WSTR_SEPARATORS) {return String(s).trim(trimChars);}

		/*!
		** \brief Convert all antislashes into slashes
		** \param s The string to convert
		** \return A new string
		*/
		static String ConvertAntiSlashesIntoSlashes(const String& s) {return String(s).convertAntiSlashesIntoSlashes();}

		/*!
		** \brief Convert all slashes into antislashes
		** \param s The string to convert
		** \return A new string
		*/ 
		static String ConvertSlashesIntoAntiSlashes(const String& s) {return String(s).convertSlashesIntoAntiSlashes();}


		/*!
		** \brief Get the number of occurences of a char
		**
		** \param s The string
		** \param c The char to find in the string
		*/
		static Size CountChar(const String& s, const String::Char c) {return s.countChar(c);}
		
		
		/*!
		** \brief Extract the key and its value from a string (mainly provided by TDF files)
		**
		** \param s A line (ex: `   category=core vtol ctrl_v level1 weapon  notsub ;`)
		** \param[out] key The key that has been found
		** \param[out] value The associated value
		** \param chcase The key will be converted to lowercase if equals to `soIgnoreCase`
		**
		** \code
		**	String k, v;
		**
		**	// -> k='category'
		**	// -> v='core vtol ctrl_v level1 weapon  notsub'
		**	String::ToKeyValue("  category=core vtol ctrl_v level1 weapon  notsub ;", k, v)
		**
		**	// -> k='foo'
		**	// -> v='bar'
		**	String::ToKeyValue("  foo  = bar ; ");
		**
		**	// -> k='}'  v=''
		**	String::ToKeyValue("  } ", k, v);
		**
		**	// -> k='['   v='Example of Section'
		**	String::ToKeyValue(" [Example of Section] ", k, v);
		**
		**	// -> k='foo'  v='bar'
		**	String::ToKeyValue(" foo=bar; // comment", k, v);
		**
		**	// -> k='foo'  v='bar'
		**	String::ToKeyValue(" foo=bar; // comments here; ", k, v);
		** \endcode
		*/
		static void ToKeyValue(const String& s, String& key, String& value, const enum CharCase chcase = soCaseSensitive);

		/*!
		** \brief Find the index of a string in a vector
		** \param l The vector
		** \param s The string to look for
		** \return The index of the string found, -1 otherwise
		*/
		static int FindInList(const String::Vector& l, const char* s);
		static int FindInList(const String::Vector& l, const String& s);

		/*!
		** \brief Formatted string 
		**
		** \param f The format of the new string
		** \return A new string
		*/ 
		static String Format(const String& f, ...);
		static String Format(const char* f, ...);


	public:
		//! \name Constructors and Destructor
		//@{
		//! Default constructor
		String() :std::string() {}
		//! Constructor by copy
		String(const String& v, size_type pos = 0, size_type n = npos) :std::string(v, pos, n) {}
		//! Constructor with a default value from a std::string
		String(const std::string& v) :std::string(v) {}
		//! Constructor with a default value from a wide string (wchar_t*)
		String(const wchar_t* v);
		//! Constructor with a default value from a string (char*)
		String(const char* v); 
		//! Constructor with a default value from a string (char*) and a length
		String(const char* v, String::size_type n) :std::string(v, n) {}
		//! Constructor with a default value from a single char
		String(const char v) :std::string() {*this += v;}
		//! Constructor with a default value from an int (16 bits)
		explicit String(const sint16 v) :std::string() {*this << v;}
		//! Constructor with a default value from an int (32 bits)
		explicit String(const sint32 v) :std::string() {*this << v;}
		//! Constructor with a default value from an int (64 bits)
		explicit String(const sint64 v) :std::string() {*this << v;}
		//! Constructor with a default value from an unsigned int (8 bits)
		explicit String(const uint8 v) :std::string() {*this << v;}
		//! Constructor with a default value from an unsigned int (16 bits)
		explicit String(const uint16 v) :std::string() {*this << v;}
		//! Constructor with a default value from an unsigned int (32 bits)
		explicit String(const uint32 v) :std::string() {*this << v;}
		//! Constructor with a default value from an unsigned int (64 bits)
		explicit String(const uint64 v) :std::string() {*this << v;}
		//! Constructor with a default value from a float
		explicit String(const float v) :std::string() {*this << v;}
		//! Constructor with a default value from a double
		explicit String(const double v) :std::string() {*this << v;}
		//! Constructor with a default value from a list of something 
		template<template<class,class> class U, class Type, class Alloc>
		String(const U<Type,Alloc>& v) :std::string() {this->append(v);}

		//! Destructor
		virtual ~String() {}
		//@}


		//! \name Append
		//@{

		/*!
		** \brief Append a string
		*/
		void append(const String& v) {std::string::append(v);}

		/*!
		** \brief Append a CString
		*/
		void append(const char* v) {std::string::append(v);}
		
		/*!
		** \brief Append a substring
		*/
		void append(const String& v, String::Index& p, const String::Size& n)
		{std::string::append(v, p, n);}

		/*!
		** \brief Append a substring
		*/
		void append(const String& v, int p, String::Size& n) {std::string::append(v, p, n);}

		/*!
		** \brief Append a list of string
		**
		** \param v The list of string
		** \param sep The separator to use when appending an item from the list
		** \param max The maximum number of items to append
		*/
		template<template<class,class> class U, class Type, class Alloc>
		void append(const U<Type,Alloc>& v, const String& sep = ", ", const unsigned int max = UINT_MAX);
	
		/*!
		** \brief Append a list of string
		**
		** \param v The list of string
		** \param sep The separator to use when appending an item from the list
		** \param enclosure The string to use as a prefix and a suffix when appending an item from the list
		** \param max The maximum number of items to append
		*/
		template<template<class,class> class U, class Type, class Alloc>
		void append(const U<Type,Alloc>& v, const String& sep, const String& enclosure, const unsigned int max = UINT_MAX);

		//@}


		//! \name Conversions
		//@{
		
		//! Convert this string into an int (8 bits)
		sint8 toInt8(const sint8 def = 0) const {YUNI_WSTR_CAST_OP(sint8);} 
		//! Convert this string into an int (16 bits)
		sint16 toInt16(const sint16 def = 0) const {YUNI_WSTR_CAST_OP(sint16);} 
		//! Convert this string into an int (32 bits)
		sint32 toInt32(const sint32 def = 0) const {YUNI_WSTR_CAST_OP(sint32);} 
		//! Convert this string into an int (64 bits)
		sint64 toInt64(const sint64 def = 0) const {YUNI_WSTR_CAST_OP(sint64);} 
		//! Convert this string into an unsigned int (8 bits)
		uint8 toUInt8(const uint8 def = 0) const {YUNI_WSTR_CAST_OP(uint8);} 
		//! Convert this string into an unsigned int (16 bits)
		uint16 toUInt16(const uint16 def = 0) const {YUNI_WSTR_CAST_OP(uint16);} 
		//! Convert this string into an unsigned int (32 bits)
		uint32 toUInt32(const uint32 def = 0) const {YUNI_WSTR_CAST_OP(uint32);} 
		//! Convert this string into an unsigned int (64 bits)
		uint64 toUInt64(const uint64 def = 0) const {YUNI_WSTR_CAST_OP(uint64);} 
		//! Convert this string into a float
		float toFloat(const float def = 0.0f) const {YUNI_WSTR_CAST_OP(float);} 
		//! Convert this string into a double
		double toDouble(const double def = 0.) const {YUNI_WSTR_CAST_OP(double);} 
		//! Convert this string into a bool (true if the lower case value is equals to "true", "1" or "on")
		bool toBool() const; 

		/*!
		** \brief Generic conversion
		** \tparam U The target type
		*/
		template<class U> U to() const;

		/*!
		** \brief Generic conversion
		** \tparam U The target type
		** \param[in,out] u The variable where to store the result
		*/
		template<class U> void to(U& u) const;

		//@}



		//! \name Case convertion
		//@{
		/*!
		** \brief Convert the case (lower case) of characters in the string using the UTF8 charset
		** \return Returns *this
		*/
		String& toLower()
		{std::transform (this->begin(), this->end(), this->begin(), tolower);return *this;}
		/*!
		** \brief Convert the case (upper case) of characters in the string using the UTF8 charset
		** \return Returns *this
		*/
		String& toUpper()
		{std::transform (this->begin(), this->end(), this->begin(), toupper);return *this;}
		//@} Case convertion


		
		//! \name Split
		//@{
		/*!
		** \brief Split a string into several segments
		**
		** Here is an example of howto convert a string to a list of int :
		** \code
		** std::list<int>  list;
		** String("22::80::443::993").split(list, ":");
		** std::cout << list << std::endl;
		** \endcode
		**
		** \param[out] out All segments that have been found
		** \param sep Sequence of chars considered as a separator
		** \param emptyBefore True to clear the vector before fulfill it
		** \return Always this
		**
		** \warning Do not take care of string representation (with `'` or `"`)
		*/
		template<template<class,class> class U, class Type, class Alloc>
		const String&
		split(U<Type,Alloc>& out, const String& sep = YUNI_WSTR_SEPARATORS, const bool emptyBefore = true) const;
		//@}


		//! \name Trimming
		//@{
		/*!
		** \brief Remove trailing and leading spaces
		** \param trimChars The chars to remove
		** \return Returns *this
		*/
		String& trim(const String& trimChars = YUNI_WSTR_SEPARATORS);
		//@}

		

		//! \name Find & Replace
		//@{

		/*!
		** \brief Replace a substr by another one
		** \param toSearch The string to look for
		** \param replaceWith The string replacement
		** \param option Option when looking for the string `toSearch`
		** \return Always *this
		*/
		String& findAndReplace(const String& toSearch, const String& replaceWith,
				const enum String::CharCase option = soCaseSensitive);
		String& findAndReplace(char toSearch, const char replaceWith,
				const enum String::CharCase option = soCaseSensitive);

		/*!
		** \brief Get the number of occurence of a char
		**
		** \param s The string
		** \param c The char to find in the string
		*/
		Size countChar(const String::Char c) const;

		//@}



		//! \name Format
		//@{

		/*!
		** \brief Reset the current value with a formatted string 
		**
		** \param f The format of the new string
		** \return Always *this
		*/
		String& format(const String& f, ...);
		String& format(const char* f, ...);

		/*!
		** \brief Append a formatted string 
		** \param f The format of the new string
		** \return Always *this
		*/
		String& appendFormat(const String& f, ...);
		String& appendFormat(const char* f, ...);
		String& vappendFormat(const char* f, va_list parg);

		//@}


		//! \name Misc
		//@{

		/*!
		** \brief Extract the key and its value from a string (mainly provided by TDF files)
		**
		** \param[out] key The key that has been found
		** \param[out] value The associated value
		** \param chcase Options for the extraction
		**
		** \see String::ToKeyValue()
		*/
		void toKeyValue(String& key, String& value, const enum CharCase chcase = soCaseSensitive) const
		{ToKeyValue(*this, key, value, chcase);}

		/*!
		** \brief Convert all antislashes into slashes
		** \return Returns *this
		*/
		String& convertAntiSlashesIntoSlashes();

		/*!
		** \brief Convert all slashes into antislashes
		** \return Returns *this
		*/
		String& convertSlashesIntoAntiSlashes();

		/*!
		** \brief Get the hash value of this string
		*/
		uint32 hashValue() const;

		//@}



		//! \name The operator `<<`
		//@{
		//! Append a string (char*) 
		String& operator << (const char* v) {static_cast<std::string*>(this)->append(v);return *this;}
		//! Append a string (stl)
		String& operator << (const std::string& v) {static_cast<std::string*>(this)->append(v);return *this;}
		//! Append a string (Yuni::String)
		String& operator << (const String& v) {static_cast<std::string*>(this)->append(v);return *this;}
		//! Append a single char
		String& operator << (const char v) {*(static_cast<std::string*>(this)) += v; return *this;}
		//! Append a wide string (wchar_t*)
		String& operator << (const wchar_t* v);
		//! Append an unsigned int (8 bits)
		String& operator << (const uint8 v) {YUNI_WSTR_APPEND;}
		//! Append an int (16 bits)
		String& operator << (const sint16 v) {YUNI_WSTR_APPEND;}
		//! Append an unsigned int (16 bits)
		String& operator << (const uint16 v) {YUNI_WSTR_APPEND;}
		//! Append an int (32 bits)
		String& operator << (const sint32 v) {YUNI_WSTR_APPEND;}
		//! Append an unsigned int (32 bits)
		String& operator << (const uint32 v) {YUNI_WSTR_APPEND;}
		//! Append an int (64 bits)
		String& operator << (const sint64 v) {YUNI_WSTR_APPEND;}
		//! Append an unsigned int (64 bits)
		String& operator << (const uint64 v) {YUNI_WSTR_APPEND;}
		//! Convert then Append a float
		String& operator << (const float v) {YUNI_WSTR_APPEND;}
		//! Convert then Append a double 
		String& operator << (const double v) {YUNI_WSTR_APPEND;}
		//! Convert then Append a boolean (will be converted into "true" or "false")
		String& operator << (const bool v) {YUNI_WSTR_APPEND_BOOL(v);return *this;}
		//! Append (Concate) a list of something 
		template<template<class,class> class U, class Type, class Alloc>
		String& operator << (const U<Type,Alloc>& v) {this->append(v);return *this;}
		//@}


		//! \name The operator `+=` (with the same abilities than the operator `<<`)
		//@{
		//! Append a string (char*) 
		String& operator += (const char* v) {static_cast<std::string*>(this)->append(v); return *this;}
		//! Append a string (stl)
		String& operator += (const std::string& v) {static_cast<std::string*>(this)->append(v); return *this;}
		//! Append a string (Yuni::String)
		String& operator += (const Yuni::String& v) {static_cast<std::string*>(this)->append(v); return *this; }
		//! Append a single char
		String& operator += (const char v) {*(static_cast<std::string*>(this)) += (char)v; return *this;}
		//! Append a wide string (wchar_t*)
		String& operator += (const wchar_t* v) {*this << v; return *this;}
		//! Append an unsigned int (8 bits)
		String& operator += (const uint8 v) {*this << v; return *this;}
		//! Append an int (16 bits)
		String& operator += (const sint16 v) {*this << v; return *this; }
		//! Append an unsigned int (16 bits)
		String& operator += (const uint16 v) {*this << v; return *this; }
		//! Append an int (32 bits)
		String& operator += (const sint32 v) {*this << v; return *this; }
		//! Append an unsigned int (32 bits)
		String& operator += (const uint32 v) {*this << v; return *this; }
		//! Append an int (64 bits)
		String& operator += (const sint64 v) {*this << v; return *this; }
		//! Append an unsigned int (64 bits)
		String& operator += (const uint64 v) {*this << v; return *this; }
		//! Convert then Append a float
		String& operator += (const float v) {*this << v; return *this; }
		//! Convert then Append a double 
		String& operator += (const double v) {*this << v; return *this; }
		//! Convert then Append a boolean (will be converted into "true" or "false")
		String& operator += (const bool v) {YUNI_WSTR_APPEND_BOOL(v); return *this; }
		//! Append (Concate) a list of string
		template<template<class,class> class U, class Type, class Alloc>
		String& operator += (const U<Type,Alloc>& v) {this->append(v); return *this; }
		//@}


		//! \name The operator `+`
		//@{
		//! Create a new String from the concatenation of *this and a string
		const String operator + (const String& rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and a char
		const String operator + (const char rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and a widechar
		const String operator + (const wchar_t rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and a const char*
		const String operator + (const char* rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and a wide string
		const String operator + (const wchar_t* rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and a signed int (16 bits)
		const String operator + (const sint16 rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and a signed int (32 bits)
		const String operator + (const sint32 rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and a signed int (64 bits)
		const String operator + (const sint64 rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and an unsigned int (8 bits)
		const String operator + (const uint8 rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and an unsigned int (16 bits)
		const String operator + (const uint16 rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and an unsigned int (32 bits)
		const String operator + (const uint32 rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and an unsigned int (64 bits)
		const String operator + (const uint64 rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and a float
		const String operator + (const float rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and a double
		const String operator + (const double rhs) { return String(*this) += rhs; }
		//! Create a new String from the concatenation of *this and a list of something
		template<template<class,class> class U, class Type, class Alloc>
		const String operator + (const U<Type,Alloc>& rhs) { return String(*this) += rhs; }
		//@}


	private:
		/*!
		** \brief Convert a string into another type, given by the template parameter `T`
		** \param[out] t The destination variable
		** \param s The string to convert
		** \param f The base to use for the convertion (std::hex, std::dec, ...)
		** \return True if the operation succeeded, False otherwise
		*/
		template <class T>
		inline bool fromString(T& t, const String& s, std::ios_base& (*f)(std::ios_base&)) const
		{
			std::istringstream iss(s);
			return !(iss >> f >> t).fail();
		}

	}; // class String





} // namespace Yuni



// Overload operators for template<class, class> class in the .hxx file
# include "string.hxx"

#endif // __YUNI_TOOLBOX_STRING_STRING_H__
