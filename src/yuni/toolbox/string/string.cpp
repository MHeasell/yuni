
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES  1
#include <ctype.h>
#include "string.h"
#include <memory>




namespace Yuni
{



	String::String(const char* v)
		:std::string()
	{
		if (v)
			this->append(v);
	}

	String::String(const wchar_t* v)
		:std::string()
	{
		if (v)
			*this << v;
	}

	String&
	String::operator << (const wchar_t* v)
	{
		size_t l = wcslen(v);
		char* b = new char[l + 1];
		#if !defined(YUNI_OS_WINDOWS) || defined(YUNI_OS_MINGW)
		wcstombs(&b[0], v, l);
		#else
		size_t i;
		wcstombs_s(&i, &b[0], l, v, l);
		#endif
		this->append(b);
		delete b;
		return *this;
	}



	bool String::toBool() const
	{
		if (this->empty() || "0" == *this)
			return false;
		if (1 == this->length())
		{
			char c((*this)[0]);
			return ('1' == c || 'Y' == c || 'y' == c || 'O' == c || 'o' == c);
		}
		String s(*this);
		s.toLower();
		return ("true" == s || "on" == s || "yes" == s);
	}


	String&
	String::trim(const String& trimChars)
	{
		// Find the first character position after excluding leading blank spaces
		std::string::size_type startpos = this->find_first_not_of(trimChars);
		// Find the first character position from reverse af
		std::string::size_type endpos   = this->find_last_not_of(trimChars);

		// if all spaces or empty return an empty string
		if ((std::string::npos == startpos) || (std::string::npos == endpos))
			this->clear();
		else
			*this = this->substr(startpos, endpos - startpos + 1);
		return *this;
	}



	void String::ToKeyValue(const String& s, String& key, String& value, const enum String::CharCase chcase)
	{
		// The first useful character
		String::size_type pos = s.find_first_not_of(YUNI_WSTR_SEPARATORS);
		if (pos == String::npos)
		{
			// The string is empty
			key.clear();
			value.clear();
			return;
		}
		// Beginning of a section
		if ('[' == s[pos])
		{
			key = "[";
			pos = s.find_first_not_of(YUNI_WSTR_SEPARATORS, pos + 1);
			String::size_type end = s.find_first_of(']', pos);
			end = s.find_last_not_of(YUNI_WSTR_SEPARATORS, end - 1);
			value = s.substr(pos, end - pos + 1);
			return;
		}
		// The first `=` character
		String::size_type equal = s.find_first_of('=', pos);
		if (equal == String::npos)
		{
			// otherwise it is only a string
			value.clear();
			// But it may be a comment
			String::size_type slashes = s.find("//", pos);
			if (pos == slashes)
			{
				key.clear();
				return;
			}
			String::size_type end = s.find_last_not_of(YUNI_WSTR_SEPARATORS, slashes - 1);
			key = s.substr(pos, end - pos + 1);
			return;
		}

		// We can extract our key
		String::size_type end = s.find_last_not_of(YUNI_WSTR_SEPARATORS, equal - 1);
		key = s.substr(pos, 1 + end - pos);
		String::size_type slashes = key.rfind("//");
		// Remove any comments
		if (slashes != String::npos)
		{
			value.clear();
			if (slashes == 0) // the key is a comment actually
				key.clear();
			else
			{
				// Get only the good part
				slashes = key.find_last_not_of(YUNI_WSTR_SEPARATORS, slashes - 1);
				key = key.substr(0, slashes + 1);
				if (chcase == soIgnoreCase)
					key.toLower();
			}
			return;
		}
		if (chcase == soIgnoreCase)
			key.toLower();

		// Left-Trim for the value
		equal = s.find_first_not_of(YUNI_WSTR_SEPARATORS, equal + 1);
		if (String::npos == equal)
		{
			value.clear();
			return;
		}

		// Looking for the first semicolon
		bool needReplaceSemicolons(false);
		String::size_type semicolon = s.find_first_of(';', equal);
		while (semicolon != String::npos && s[semicolon - 1] == '\\')
		{
			semicolon = s.find_first_of(';', semicolon + 1);
			needReplaceSemicolons = true;
		}
		if (semicolon == String::npos)
		{
			// if none is present, look for a comment to strip it
			slashes = s.find("//", equal);
			slashes = s.find_last_not_of(YUNI_WSTR_SEPARATORS, slashes - 1);
			value = s.substr(equal, 1 + slashes - equal);
			value.findAndReplace("\\r", "", soCaseSensitive);
			value.findAndReplace("\\n", "\n", soCaseSensitive);
			if (needReplaceSemicolons)
				value.findAndReplace("\\;", ";", soCaseSensitive);
			return;
		}
		// Remove spaces before the semicolon and after the `=`
		semicolon = s.find_last_not_of(YUNI_WSTR_SEPARATORS, semicolon - 1);

		// We can extract the value
		if (semicolon >= equal)
		{
			value = s.substr(equal, 1 + semicolon - equal);
			value.findAndReplace("\\r", "", soCaseSensitive);
			value.findAndReplace("\\n", "\n", soCaseSensitive);
			if (needReplaceSemicolons)
				value.findAndReplace("\\;", ";", soCaseSensitive);
		}
		else
			value.clear();
	}



	String& String::convertBackSlashesIntoSlashes()
	{
		String::iterator end(this->end());
		for (String::iterator i = this->begin(); i != end; ++i)
		{
			if (*i == '\\')
				*i = '/';
		}
		return *this;
	}



	String& String::convertSlashesIntoBackSlashes()
	{
		String::iterator end(this->end());
		for (String::iterator i = this->begin(); i != end; ++i)
		{
			if (*i == '/')
				*i = '\\';
		}
		return *this;
	}



	uint32 String::hashValue() const
	{
		String::const_iterator end(this->end());
		uint32 hash = 0;
		for (String::const_iterator i = this->begin(); i != end; ++i)
			hash = (hash << 5) - hash + *i;
		return hash;
	}



	int String::FindInList(const String::Vector& l, const char* s)
	{
		String::Vector::const_iterator end(l.end());
		int indx(0);
		for (String::Vector::const_iterator i = l.begin(); i != end; ++i, ++indx)
		{
			if(s == *i)
				return indx;
		}
		return -1;
	}


	int String::FindInList(const String::Vector& l, const String& s)
	{
		String::Vector::const_iterator end(l.end());
		int indx(0);
		for (String::Vector::const_iterator i = l.begin(); i != end; ++i, ++indx)
		{
			if(s == *i)
				return indx;
		}
		return -1;
	}



	String& String::findAndReplace(char toSearch, const char replaceWith, const enum String::CharCase option)
	{
		if (option == soIgnoreCase)
		{
			toSearch = (char)tolower(toSearch);
			for (String::iterator i = this->begin(); i != this->end(); ++i)
			{
				if (tolower(*i) == toSearch)
					*i = replaceWith;
			}
		}
		else
		{
			for (String::iterator i = this->begin(); i != this->end(); ++i)
			{
				if (*i == toSearch)
					*i = replaceWith;
			}
		}
		return *this;
	}



	String& String::findAndReplace(const String& toSearch, const String& replaceWith, const enum String::CharCase option)
	{
		if (soCaseSensitive == option)
		{
			String::size_type p = 0;
			String::size_type siz = toSearch.size();
			while (String::npos != (p = this->find(toSearch, p)))
				this->replace(p, siz, replaceWith);
		}
		else
		{
			*this = String::ToLower(*this).findAndReplace(String::ToLower(toSearch), replaceWith, soCaseSensitive);
		}
		return *this;
	}


	String& String::format(const String& f, ...)
	{
		va_list parg;
		va_start(parg, f);

		this->clear();
		vappendFormat(f.c_str(), parg);

		va_end(parg);
		return *this;
	}


	String& String::format(const char* f, ...)
	{
		va_list parg;
		va_start(parg, f);

		this->clear();
		vappendFormat(f, parg);

		va_end(parg);
		return *this;
	}


	String& String::appendFormat(const String& f, ...)
	{
		va_list parg;
		va_start(parg, f);

		vappendFormat(f.c_str(), parg);

		va_end(parg);
		return *this;
	}


	String& String::appendFormat(const char* f, ...)
	{
		va_list parg;
		va_start(parg, f);

		vappendFormat(f, parg);

		va_end(parg);
		return *this;
	}




	template<class char_type> int
	vprintf_generic(char_type* buffer, size_t bufferSize, const char_type* format, va_list argptr);

	template<> inline int
	vprintf_generic<char>(char* buffer, size_t bufferSize, const char* format, va_list argptr)
	{
		# if defined YUNI_OS_MSVC
		#	ifdef SECURE_VSPRINTF
			return _vsnprintf_s(buffer, bufferSize-1, _TRUNCATE, format, argptr);
		#	else
			return _vsnprintf(buffer, bufferSize-1, format, argptr);
		#	endif
		# else
			return vsnprintf(buffer, bufferSize-1, format, argptr);
		# endif
	}

	# ifdef YUNI_OS_WINDOWS
	template<> inline int
	vprintf_generic<wchar_t>(wchar_t* buffer, size_t bufferSize, const wchar_t* format, va_list argptr)
	{
		# if defined YUNI_OS_MSVC
		#	ifdef SECURE_VSPRINTF
			return _vsnwprintf_s(buffer, bufferSize-1, _TRUNCATE, format, argptr);
		#	else
			return _vsnwprintf(buffer, bufferSize-1, format, argptr);
		#	endif
		# else
			return vsnwprintf(buffer, bufferSize-1, format, argptr);
		# endif
	}
	# endif


	template<class Type, class Traits>
	static int
	impl_vsprintf(std::basic_string<Type,Traits> & outStr, const Type* format, va_list args)
	{
		if (!format)
			return 0;

		static const size_t ChunkSize = 1024;
		size_t curBufSize = 0;

		// keep trying to write the string to an ever-increasing buffer until
		// either we get the string written or we run out of memory
		while (1)
		{
			// allocate a local buffer
			curBufSize += ChunkSize;
			std::auto_ptr<Type> localBuffer(new Type[curBufSize]);
			if (!localBuffer.get())
				return -1;

			// format output to local buffer
			int i = vprintf_generic(localBuffer.get(), curBufSize * sizeof(Type), format, args);
			if (-1 == i)
				continue;
			else
			{
				if (i < 0)
					return i;
			}

			outStr.append(localBuffer.get(), i);
			return i;
		}
		return -1;
	}


	String& String::vappendFormat(const char* f, va_list parg)
	{
		impl_vsprintf(*this, f, parg);
		return *this;
	}


	String String::Format(const String& f, ...)
	{
		va_list parg;
		va_start(parg, f);

		String s;
		s.vappendFormat(f.c_str(), parg);

		va_end(parg);
		return s;
	}

	String String::Format(const char* f, ...)
	{
		va_list parg;
		va_start(parg, f);

		String s;
		s.vappendFormat(f, parg);

		va_end(parg);
		return s;
	}


	String::Size String::countChar(const String::Char c) const
	{
		if (this->empty())
			return 0;
		String::Size ret = 0;
		String::const_iterator end = this->end();
		for (String::const_iterator i = this->begin(); i != end; ++i)
		{
			if (c == *i)
				++ret;
		}
		return ret;
	}





} // namespace Yuni
