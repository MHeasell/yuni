#ifndef __YUNI_CORE_IO_IO_HXX__
# define __YUNI_CORE_IO_IO_HXX__

# include <assert.h>
# include "private.h"


namespace Yuni
{
namespace Core
{
namespace IO
{
namespace Directory
{

	// Forward declaration
	template<typename C> struct Constant;

} // namespace Directory
} // namespace IO
} // namespace Core
} // namespace Yuni



namespace Yuni
{
namespace Core
{
namespace IO
{

	template<>
	struct Constant<wchar_t>
	{
		//! The path-separator character according to the platform (ex: `/`)
		static const wchar_t  Separator = L'/';
		//! The path-separator character according to the platform (stored in a string instead of a char)
		static const wchar_t* SeparatorAsString; // = L"/";
		//! All path-separator characters, for all platforms
		static const wchar_t* AllSeparators; // = L"\\/";
		//! Dot
		static const wchar_t  Dot = L'/';
	};



	template<int N>
	inline bool IsAbsolute(const StringBase<char,N>& p)
	{
		# ifdef YUNI_OS_WINDOWS
		return (p.empty() || (p.size() > 2 && ':' == p[1] && '\\' == p[2]));
		# else
		return (p.empty() || '/' == p.first());
		# endif
	}

	template<int N>
	inline bool IsAbsolute(const StringBase<wchar_t,N>& p)
	{
		# ifdef YUNI_OS_WINDOWS
		return (p.empty() || (p.size() > 2 && L':' == p[1] && L'\\' == p[2]));
		# else
		return (p.empty() || L'/' == p.first());
		# endif
	}


	inline bool IsAbsolute(const char* p)
	{
		# ifdef YUNI_OS_WINDOWS
		return (!p || (L'\0' != *p && ':' == p[1] && '\\' == p[2]));
		# else
		return (!p || '/' == *p);
		# endif
	}

	inline bool IsAbsolute(const wchar_t* p)
	{
		# ifdef YUNI_OS_WINDOWS
		return (!p || ('\0' != *p && L':' == p[1] && L'\\' == p[2]));
		# else
		return (!p || L'/' == *p);
		# endif
	}



	template<typename C, int N, int M>
	void ExtractFilePath(StringBase<C,N>& out, const StringBase<C,M>& p, const bool systemDependant)
	{
		typedef StringBase<C,N> StringT;
		assert(&p != &out && "The behavior can be undefined");
		out.clear();
		const typename StringT::size_type pos = (systemDependant)
			? p.find_last_of(IO::Constant<C>::Separator)
			: p.find_last_of(IO::Constant<C>::AllSeparators);
		if (StringT::npos != pos)
		{
			if (!pos)
				out.append(p[pos]);
			else
				out.append(p, 0, pos - 1);
		}
	}


	template<typename C, int N>
	StringBase<C,N> ExtractFilePath(const StringBase<C,N>& p, const bool systemDependant)
	{
		typedef StringBase<C,N> StringT;
		if (p.notEmpty())
		{
			const typename StringT::size_type pos = (systemDependant)
				? p.find_last_of(IO::Constant<C>::Separator)
				: p.find_last_of(IO::Constant<C>::AllSeparators);
			return (StringT::npos == pos) ? StringT() : StringT(p, 0, pos + 1);
		}
		return StringT();
	}


	template<typename C>
	inline StringBase<C> ExtractFilePath(const C* p, const bool systemDependant)
	{
		return (p && 0 != *p)
			? ExtractFilePath(StringBase<C>(p), systemDependant)
			: StringBase<C>();
	}



	template<typename C, int N>
	StringBase<C,N> ExtractFileName(const StringBase<C,N>& p, const bool systemDependant)
	{
		typedef StringBase<C,N> StringT;
		if (p.notEmpty())
		{
			const typename StringT::size_type pos = (systemDependant)
				? p.find_last_of(IO::Constant<C>::Separator)
				: p.find_last_of(IO::Constant<C>::AllSeparators);
			return (StringT::npos == pos) ? p : StringT(p, pos + 1);
		}
		return StringT();
	}

	template<typename C>
	StringBase<C> ExtractFileName(const C* p, const bool systemDependant)
	{
		return (p && 0 != *p)
			? ExtractFileName(StringBase<C>(p), systemDependant)
			: StringBase<C>();
	}



	template<typename C, int N>
	void ExtractFileName(typename StringBase<C,N>::List& p, const bool systemDependant)
	{
		typedef StringBase<C,N> StringT;
		if (!p.empty())
		{
			const typename StringT::List::iterator end = p.end();
			for (typename StringT::List::iterator i = p.begin(); i != end; ++i)
				*i = ExtractFileName(*i, systemDependant);
		}
	}


	template<typename C, int N>
	void ExtractFileName(typename StringBase<C,N>::Vector& p, const bool systemDependant)
	{
		typedef StringBase<C,N> StringT;
		if (!p.empty())
		{
			const typename StringT::Vector::iterator end = p.end();
			for (typename StringT::Vector::iterator i = p.begin(); i != end; ++i)
				*i = ExtractFileName(*i, systemDependant);
		}
	}


	template<typename C, int N>
	StringBase<C,N> ExtractFileNameWithoutExtension(const StringBase<C,N>& p, const bool systemDependant)
	{
		typedef StringBase<C,N> StringT;

		const typename StringT::size_type pos = (systemDependant)
			? p.find_last_of(IO::Constant<C>::Separator)
			: p.find_last_of(IO::Constant<C>::AllSeparators);
		const typename StringT::size_type n = p.find_last_of('.');

		if (StringT::npos == n && StringT::npos == pos)
			return p;
		if (n == pos)
			return StringT();
		if (n == StringT::npos && n > pos + 1)
		{
			if (StringT::npos == pos)
				return p;
			return p.substr(pos + 1);
		}
		if (pos == StringT::npos)
			return p.substr(0, n);
		return p.substr(pos + 1, n - pos - 1);
	}



	inline String ExtractFileExt(const String& s, String::CharCase option)
	{
		const String::size_type n = s.find_last_of(".\\/");
		if (n == String::npos || '.' != s[n])
			return String();
		return (String::soIgnoreCase == option) ? String(s, n).toLower() : String(s, n);
	}




	template<typename C, int N>
	inline StringBase<C,N> MakeAbsolute(const StringBase<C,N>& p)
	{
		return MakeAbsolute(p, IO::Directory::Current());
	}


	template<typename C, int N, typename U>
	StringBase<C,N> MakeAbsolute(const StringBase<C,N>& p, const U& currentDirectory)
	{
		if (IsAbsolute(p))
			return p;
		typedef StringBase<C,N> StringT;
		StringT ret(currentDirectory);
		ret << IO::Constant<C>::Separator << p;
		ret.removeTrailingSlash();
		return ret;
	}


	template<typename C, int N, typename U>
	inline StringBase<C,N> ReplaceExtension(const StringBase<C,N>& filename, const U& newExt)
	{
		typedef StringBase<C,N> StringT;
		// Nothing to do
		if (filename.empty())
			return StringT();

		const typename StringT::size_type p = filename.find_last_of('.');
		if (p == StringT::npos)
			return filename + newExt;
		const String::size_type s = filename.find_last_of(IO::Constant<C>::AllSeparators);
		if (s != StringT::npos && p < s)
			return filename + newExt;
		return filename.substr(0, p) + newExt;
	}




} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_IO_IO_HXX__
