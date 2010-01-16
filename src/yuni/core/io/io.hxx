#ifndef __YUNI_CORE_IO_IO_HXX__
# define __YUNI_CORE_IO_IO_HXX__

# include <assert.h>
# include "private.h"
# include <deque>



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
		static const wchar_t  Separator; // L'/';
		//! The path-separator character according to the platform (stored in a string instead of a char)
		static const wchar_t* SeparatorAsString; // = L"/";
		//! All path-separator characters, for all platforms
		static const wchar_t* AllSeparators; // = L"\\/";
		//! Dot
		static const wchar_t  Dot; // L'.';
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



	/*
	template<class StringT1, class StringT2>
	void ExtractFilePath(StringT1& out, const StringT2& p, const bool systemDependant)
	{
		const typename StringT2::size_type pos = ((systemDependant)
			? p.find_last_of(IO::Constant<char>::Separator)
			: p.find_last_of(IO::Constant<char>::AllSeparators));
		if (String::npos != pos)
		{
			if (!pos)
				out.append(p[pos]);
			else
				out.append(p, 0, pos - 1);
		}
	}
	*/


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



	template<typename C, int N, template<class> class Alloc>
	void ExtractFileName(std::list<StringBase<C,N>, Alloc<StringBase<C, N> > >& p, const bool systemDependant)
	{
		typedef StringBase<C,N> StringT;
		if (!p.empty())
		{
			const typename StringT::List::iterator end = p.end();
			for (typename StringT::List::iterator i = p.begin(); i != end; ++i)
				*i = ExtractFileName(*i, systemDependant);
		}
	}


	template<typename C, int N, template<class> class Alloc>
	void ExtractFileName(std::vector<StringBase<C,N>, Alloc<StringBase<C, N> > >& p, const bool systemDependant)
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



	template<typename C, int N>
	inline StringBase<C,N> ExtractExtension(const StringBase<C,N>& s, String::CharCase option)
	{
		typedef StringBase<C,N> StringT;
		const typename StringT::size_type n = s.find_last_of(StringBase<C,N>(IO::Constant<C>::AllSeparators) << IO::Constant<C>::Dot);
		if (n == StringT::npos || '.' != s[n])
			return StringT();
		return (StringT::soIgnoreCase == option) ? StringT(s, n).toLower() : StringT(s, n);
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


	template<class AnyStringT, class StringT>
	void Normalize(const AnyStringT& in, StringT& out)
	{
		// The given type, with its const identifier
		typedef typename Static::Remove::Const<AnyStringT>::Type UType;
		// Assert, if a C* container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::CString<UType>::valid, Normalize_InvalidTypeForInput);
		// Assert, if the length of the container can not be found at compile time
		YUNI_STATIC_ASSERT(Traits::Length<UType>::valid,  Normalize_InvalidTypeForInputSize);

		// Some static checks
		if (Traits::Length<UType,unsigned int>::isFixed)
		{
			// The value to find is actually empty, nothing to do
			if (0 == Traits::Length<UType,unsigned int>::fixedLength)
			{
				out.clear();
				return;
			}
			// The string is actually a single POD item
			if (1 == Traits::Length<UType,unsigned int>::fixedLength)
			{
				out = in;
				return;
			}
		}

		// The length of the input
		unsigned int inputLength = Traits::Length<UType,unsigned int>::Value(in);
		if (!inputLength)
		{
			out.clear();
			return;
		}
		if (inputLength == 1)
		{
			out = in;
			return;
		}
		// From here, we have at least 2 chars

		// From now on, we will work on a mere CString
		const char* input = Traits::CString<UType>::Buffer(in);

		// Counting slashes
		unsigned int slashes = 0;
		// An index, used at different places
		unsigned int i = 0;
		// We will keep the position of the character after the first slash. It improves
		// a bit performances for relative filenames
		unsigned int start;
		for (; i != inputLength; ++i)
		{
			if (input[i] == '/' || input[i] == '\\')
			{
				slashes = 1;
				start = ++i;
				break;
			}
		}
		if (!slashes)
		{
			// Nothing to normalize
			out = in;
			return;
		}
		for (; i < inputLength; ++i)
		{
			if (input[i] == '/' || input[i] == '\\')
				++slashes;
		}

		// Initializing the output, and reserving the memory to avoid as much as possible calls to realloc
		// In the most cases, the same size than the input is the most appropriate value
		out.reserve(inputLength);
		// Copying the begining of the input
		out.assign(input, start);

		// Detecting absolute paths.
		// We only know that we have at least 2 chars, and we can not assume that the input
		// is zero-terminated.
		// For performance reasons (to reduce the calls to malloc/free when pushing an element),
		// we will skip the begining if the path is absolute.
		bool isAbsolute = false;
		// Performing checks only if the first slash is near by the begining.
		if (start < 4)
		{
			if (input[1] == ':' && inputLength > 2 && (input[2] == '\\' || input[2] == '/'))
			{
				// We have an Windows-style path, and it is absolute
				isAbsolute = true;
			}
			else
			{
				// We have an Unix-style path
				if (input[0] == '/' || input[0] == '\\')
					isAbsolute = true;
			}
		}

		// The last known good position
		unsigned int cursor = start;
		// The number of non-relative folders, used when the path is not absolute
		// This value is used to keep the relative segments at the begining
		unsigned int realFolderCount = 0;

		// The stack
		// PreAllocating the stack, to speed up the algoritm by avoiding numerous
		// calls to malloc/free
		struct Stack
		{
		public:
			void operator () (unsigned int c, unsigned int l)
			{
				cursor = c;
				length = l;
			}
		public:
			unsigned int cursor;
			unsigned int length;
		};
		Stack* stack = new Stack[slashes + 1]; // Ex: path/to/somewhere/on/my/hdd
		// Index on the stack
		unsigned int count = 0;

		for (i = start; i < inputLength; ++i)
		{
			// Detecting the end of a segment
			if (input[i] == '/' || input[i] == '\\')
			{
				switch (i - cursor)
				{
					case 0:
						// A single slash. Nothing to do
						break;
					case 1:
						{
							// not the current folder `./`
							if (input[cursor] != '.')
							{
								stack[count++](cursor, 2);
								++realFolderCount;
							}
							break;
						}
					case 2:
						{
							// double dot segments
							if (input[cursor] == '.' && input[cursor + 1] == '.')
							{
								if (isAbsolute)
								{
									if (count)
										--count;
								}
								else
								{
									if (realFolderCount)
									{
										--count;
										--realFolderCount;
									}
									else
										stack[count++](cursor, 3);
								}
							}
							break;
						}
					default:
						{
							// We have encountered a standard segment
							stack[count++](cursor, i - cursor + 1);
							++realFolderCount;
						}
				}
				// Positioning the cursor to the next character
				cursor = i + 1;
			}
		}

		// Special case : The last segment is a double dot segment
		if (cursor < inputLength && inputLength - cursor == 2)
		{
			if (input[cursor] == '.' && input[cursor + 1] == '.')
			{
				if (isAbsolute)
				{
					if (count)
						--count;
				}
				else
				{
					if (realFolderCount)
						--count;
					else
						stack[count++](cursor, 2);
				}

				cursor = inputLength;
			}
		}

		// Pushing all stored segments
		if (count)
		{
			for (unsigned int j = 0; j != count; ++j)
				out.append(input + stack[j].cursor, stack[j].length);
		}

		// Releasing the memory
		delete[] stack;

		// But it may remain a final segment
		// We know for sure that it can not be a double dot segment
		if (cursor < inputLength)
		{
			if (inputLength - cursor == 1 && input[cursor] == '.')
				return;
			out.append(input + cursor, inputLength - cursor);
		}
	}






} // namespace IO
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_IO_IO_HXX__
