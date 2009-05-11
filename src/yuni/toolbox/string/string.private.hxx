#ifndef __YUNI_TOOLBOX_STRING_STRING_PRIVATE_HXX__
# define __YUNI_TOOLBOX_STRING_STRING_PRIVATE_HXX__



namespace Yuni
{
namespace Private
{
namespace StringImpl
{

	template<typename T>
	inline T Min(const T a, const T b)  {return a < b ? a : b;}




	template<typename C, int K>
	struct Impl
	{

		static inline C ToLower(const C a)
		{
			return tolower(a);
		}


		static int Compare(const C* a, const C* b, const typename StringBase<C,K>::Size maxLen)
		{
			typename StringBase<C,K>::Size p(0);
			for (; p < maxLen && 0 != *a && 0 != *b; ++a, ++b, ++p)
			{
				if (*a != *b)
					return (*a < *b) ? -1 : 1;
			}
			return (*a == *b) ? 0 : ((*a < *b) ? -1 : 1);
		}

		static int CompareInsensitive(const C* a, const C* b, const typename StringBase<C,K>::Size maxLen)
		{
			C s = 0;
			C t = 0;
			for (typename StringBase<C,K>::Size p = 0; p < maxLen && 0 != *a && 0 != *b; ++a, ++b, ++p)
			{
				if ((s = ToLower(*a)) != (t = ToLower(*b)))
					return (int)(s - t);
			}
			return (s == t) ? 0 : ((int)(s - t));
		}


		static bool StrictlyEquals(const C* a, const C* b)
		{
			while (1)
			{
				if (*a != *b)
					return false;
				if ('\0' == *a)
					return true;
				++a;
				++b;
			}
			return true;
		}


		static inline bool StrictlyEquals(const C* a, const C* b, const typename StringBase<C,K>::Size maxLen)
		{
			return !memcmp(a, b, sizeof(C) * maxLen);
		}

		static bool Equals(const C* a, const C* b, const typename StringBase<C,K>::Size maxLen)
		{
			typename StringBase<C,K>::Size pos(0);
			while (pos < maxLen)
			{
				if (*a != *b)
					return false;
				if ('\0' == *a)
					return true;
				++a;
				++b;
			}
			return true;
		}


	};


	template<int K1>
	struct Impl<char,K1>
	{
		static inline int Compare(const char* a, const char* b, const typename StringBase<char,K1>::Size maxLen)
		{
			return strncmp(a, b, maxLen);
		}

		static inline char ToLower(const char a)
		{
			return tolower(a);
		}



		static int CompareInsensitive(const char* a, const char* b, const typename StringBase<char,K1>::Size maxLen)
		{
			char s = 0;
			char t = 0;
			for (typename StringBase<char,K1>::Size p = 0; p < maxLen && 0 != *a && 0 != *b; ++a, ++b, ++p)
			{
				if ((s = ToLower(*a)) != (t = ToLower(*b)))
					return (int)(s - t);
			}
			return (s == t) ? 0 : ((int)(s - t));
		}


		static inline bool StrictlyEquals(const char* a, const char* b)
		{
			while (1)
			{
				if (*a != *b)
					return false;
				if ('\0' == *a)
					return true;
				++a;
				++b;
			}
			return true;
		}

		static inline bool StrictlyEquals(const char* a, const char* b, const typename StringBase<char,K1>::Size maxLen)
		{
			return !memcmp(a, b, sizeof(char) * maxLen);
		}

		static bool Equals(const char* a, const char* b, const typename StringBase<char,K1>::Size maxLen)
		{
			typename StringBase<char,K1>::Size pos(0);
			while (pos < maxLen)
			{
				if (*a != *b)
					return false;
				if ('\0' == *a)
					return true;
				++a;
				++b;
			}
			return true;
		}

	};



	template<class StrBase, class T>
	struct Length
	{
		static typename StrBase::Size Value(const T& t);
	};


	template<class StrBase1>
	struct Length<StrBase1, char*>
	{
		static inline typename StrBase1::Size Value(const char* t)
		{
			return strlen(t);
		}
	};


	template<class StrBase1>
	struct Length<StrBase1, wchar_t*>
	{
		static inline typename StrBase1::Size Value(const wchar_t* t)
		{
			return wcslen(t);
		}
	};


	template<class StrBase1, class C1, int N>
	struct Length<StrBase1, C1[N]>
	{
		static inline typename StrBase1::Size Value(const C1*)
		{
			return N - 1;
		}
	};



	template<class StrBase1, class C1,int Chnk1>
	struct Length<StrBase1, StringBase<C1,Chnk1> >
	{
		static inline typename StrBase1::Size Value(const StringBase<C1,Chnk1>& t)
		{
			return t.pSize;
		}
	};


	template<class StrBase1, class C1,int Chnk1>
	struct Length<StrBase1, StringBase<C1,Chnk1>* >
	{
		static inline typename StrBase1::Size Value(const StringBase<C1,Chnk1>* t)
		{
			return t ? t.pSize : 0;
		}
	};



	template<class StrBase1, class C1>
	struct Length<StrBase1, std::basic_string<C1> >
	{
		static inline typename StrBase1::Size Value(const std::basic_string<C1>& t)
		{
			return t.size();
		}
	};


	template<class StrBase1, class C1>
	struct Length<StrBase1, std::basic_string<C1>* >
	{
		static inline typename StrBase1::Size Value(const std::basic_string<C1>* t)
		{
			return t ? t.size() : 0;
		}
	};



	template<class StrBase1>
	struct Length<StrBase1, char>
	{
		static inline typename StrBase1::Size Value(const char&)
		{
			return 1;
		}
	};


	template<class StrBase1>
	struct Length<StrBase1, wchar_t>
	{
		static inline typename StrBase1::Size Value(const wchar_t&)
		{
			return 1;
		}
	};






	template<class StrBase, class U>
	struct CountChar
	{
		static typename StrBase::Size Value(const U& u);
	};



	template<class StrBase1, typename C1>
	struct CountChar<StrBase1, C1*>
	{
		static typename StrBase1::Size Value(const C1* str, const C1 c)
		{
			if (str)
			{
				typename StrBase1::Size n(0);
				for (const C1* i = str; '\0' != *i; ++i)
				{
					if (c == *i)
						++n;
				}
				return n;
			}
			return 0;
		}
	};


	template<class StrBase1, class C1, int N>
	struct CountChar<StrBase1, C1[N]>
	{
		static typename StrBase1::Size Value(const C1* str, const C1 c)
		{
			typename StrBase1::Size n(0);
			for (const C1* i = str; '\0' != *i; ++i)
			{
				if (c == *i)
					++n;
			}
			return n;
		}
	};



	template<class StrBase1, class C1,int Chnk1>
	struct CountChar<StrBase1, StringBase<C1,Chnk1> >
	{
		static typename StrBase1::Size Value(const StringBase<C1,Chnk1>& str, const C1 c)
		{
			if (str.pSize)
			{
				typename StrBase1::Size n(0);
				for (typename StrBase1::Size pos = 0; pos != str.pSize; ++pos)
				{
					if (c == str.pPtr[pos])
						++n;
				}
				return n;
			}
			return 0;
		}
	};


	template<class StrBase1, class C1,int Chnk1>
	struct CountChar<StrBase1, StringBase<C1,Chnk1>* >
	{
		static typename StrBase1::Size Value(const StringBase<C1,Chnk1>* str, const C1 c)
		{
			return (str && str->pSize)
				? CountChar<StrBase1, StringBase<C1, Chnk1> >::Value(*str, c)
				: 0;
		}
	};



	template<class StrBase1, class C1>
	struct CountChar<StrBase1, std::basic_string<C1> >
	{
		static typename StrBase1::Size Value(const std::basic_string<C1>& str, const C1 c)
		{
			if (!str.empty())
			{
				typename StrBase1::Size n(0);
				typename std::basic_string<C1>::const_iterator end = str.end();
				for (typename std::basic_string<C1>::const_iterator i = str.begin(); i != end; ++i)
				{
					if (c == *i)
						++n;
				}
				return n;
			}
			return 0;
		}
	};


	template<class StrBase1, class C1>
	struct CountChar<StrBase1, std::basic_string<C1>* >
	{
		static inline typename StrBase1::Size Value(const std::basic_string<C1>* str, const C1 c)
		{
			return (str && !str->empty())
				? CountChar<StrBase1, std::basic_string<C1> >::Value(*str, c)
				: 0;
		}
	};



	template<class StrBase1>
	struct CountChar<StrBase1, char>
	{
		static inline typename StrBase1::Size Value(const char str, const char c)
		{
			return (c == str) ? 1 : 0;
		}
	};


	template<class StrBase1>
	struct CountChar<StrBase1, wchar_t>
	{
		static inline typename StrBase1::Size Value(const wchar_t str, const wchar_t c)
		{
			return (c == str) ? 1 : 0;
		}
	};








	template<class StrBase, class U>
	struct HasChar
	{
		static bool Value(const U& u);
	};


	template<class StrBase1, typename C1>
	struct HasChar<StrBase1, C1*>
	{
		static bool Value(const C1* str, const C1 c)
		{
			if (str)
			{
				for (const C1* i = str; '\0' != *i; ++i)
				{
					if (c == *i)
						return true;
				}
			}
			return false;
		}
	};


	template<class StrBase1, class C1, int N>
	struct HasChar<StrBase1, C1[N]>
	{
		static bool Value(const C1* str, const C1 c)
		{
			for (const C1* i = str; '\0' != *i; ++i)
			{
				if (c == *i)
					return true;
			}
			return false;
		}
	};


	template<class StrBase1, class C1,int Chnk1>
	struct HasChar<StrBase1, StringBase<C1,Chnk1> >
	{
		static inline bool Value(const StringBase<C1,Chnk1>& str, const C1 c)
		{
			return str.hasChar(c);
		}
	};


	template<class StrBase1, class C1,int Chnk1>
	struct HasChar<StrBase1, StringBase<C1,Chnk1>* >
	{
		static inline bool Value(const StringBase<C1,Chnk1>* str, const C1 c)
		{
			return str && str->hasChar(c);
		}
	};



	template<class StrBase1, class C1>
	struct HasChar<StrBase1, std::basic_string<C1> >
	{
		static inline bool Value(const std::basic_string<C1>& str, const C1 c)
		{
			return std::basic_string<C1>::npos != str.find(c);
		}
	};


	template<class StrBase1, class C1>
	struct HasChar<StrBase1, std::basic_string<C1>* >
	{
		static inline bool Value(const std::basic_string<C1>* str, const C1 c)
		{
			return str && std::basic_string<C1>::npos != str->find(c);
		}
	};




	template<class StrBase1>
	struct HasChar<StrBase1, char>
	{
		static inline bool Value(const char str, const char c)
		{
			return (c == str);
		}
	};


	template<class StrBase1>
	struct HasChar<StrBase1, wchar_t>
	{
		static inline bool Value(const wchar_t str, const wchar_t c)
		{
			return (c == str);
		}
	};





	template<class StrBase, class T>
	struct Find
	{
		static typename StrBase::Size Value(const StrBase& str, const T& t);
		static typename StrBase::Size Value(const StrBase& str, const T& t, const typename StrBase::Size offset);
		static typename StrBase::Size ReverseValue(const StrBase& str, const T& t);
		static typename StrBase::Size ReverseValue(const StrBase& str, const T& t, const typename StrBase::Size offset);
		static typename StrBase::Size ValueOf(const StrBase& str, const T& t);
		static typename StrBase::Size ValueOf(const StrBase& str, const T& t, const typename StrBase::Size offset);
		static typename StrBase::Size ReverseValueOf(const StrBase& str, const T& t);
		static typename StrBase::Size ReverseValueOf(const StrBase& str, const T& t, const typename StrBase::Size offset);
		static typename StrBase::Size ValueNotOf(const StrBase& str, const T& t);
		static typename StrBase::Size ValueNotOf(const StrBase& str, const T& t, const typename StrBase::Size offset);
		static typename StrBase::Size ReverseValueNotOf(const StrBase& str, const T& t);
		static typename StrBase::Size ReverseValueNotOf(const StrBase& str, const T& t, const typename StrBase::Size offset);

	};

	template<class StrBase1>
	struct Find<StrBase1, char>
	{
		static typename StrBase1::Size Value(const StrBase1& str, const char t)
		{
			for (typename StrBase1::Size i = 0; i != str.pSize; ++i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size Value(const StrBase1& str, const char t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = offset; i < str.pSize; ++i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValue(const StrBase1& str, const char t)
		{
			for (typename StrBase1::Size i = str.pSize - 1; i != StrBase1::npos; --i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValue(const StrBase1& str, const char t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = ((offset != StrBase1::npos) ? offset : str.pSize - 1);
				i != StrBase1::npos; --i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}

		static typename StrBase1::Size ValueOf(const StrBase1& str, const char t)
		{
			for (typename StrBase1::Size i = 0; i != str.pSize; ++i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ValueOf(const StrBase1& str, const char t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = offset; i < str.pSize; ++i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueOf(const StrBase1& str, const char t)
		{
			for (typename StrBase1::Size i = str.pSize - 1; i != StrBase1::npos; --i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueOf(const StrBase1& str, const char t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = ((offset != StrBase1::npos) ? offset : str.pSize - 1);
				i != StrBase1::npos; --i)
			{
				if (t != str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}


		static typename StrBase1::Size ValueNotOf(const StrBase1& str, const char t)
		{
			for (typename StrBase1::Size i = 0; i != str.pSize; ++i)
			{
				if (t != str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ValueNotOf(const StrBase1& str, const char t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = offset; i < str.pSize; ++i)
			{
				if (t != str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueNotOf(const StrBase1& str, const char t)
		{
			for (typename StrBase1::Size i = str.pSize - 1; i != StrBase1::npos; --i)
			{
				if (t != str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueNotOf(const StrBase1& str, const char t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = ((offset != StrBase1::npos) ? offset : str.pSize - 1);
				i != StrBase1::npos; --i)
			{
				if (t != str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}


	};


	template<class StrBase1>
	struct Find<StrBase1, wchar_t>
	{
		static typename StrBase1::Size Value(const StrBase1& str, const wchar_t t)
		{
			for (typename StrBase1::Size i = 0; i != str.pSize; ++i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size Value(const StrBase1& str, const wchar_t t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = offset; i < str.pSize; ++i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValue(const StrBase1& str, const wchar_t t)
		{
			for (typename StrBase1::Size i = str.pSize - 1; i != StrBase1::npos; --i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValue(const StrBase1& str, const wchar_t t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = ((offset != StrBase1::npos) ? offset : str.pSize - 1);
				i != StrBase1::npos; --i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}

		static typename StrBase1::Size ValueOf(const StrBase1& str, const wchar_t t)
		{
			for (typename StrBase1::Size i = 0; i != str.pSize; ++i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ValueOf(const StrBase1& str, const wchar_t t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = offset; i < str.pSize; ++i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueOf(const StrBase1& str, const wchar_t t)
		{
			for (typename StrBase1::Size i = str.pSize - 1; i != StrBase1::npos; --i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueOf(const StrBase1& str, const wchar_t t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = ((offset != StrBase1::npos) ? offset : str.pSize - 1);
				i != StrBase1::npos; --i)
			{
				if (t == str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}


		static typename StrBase1::Size ValueNotOf(const StrBase1& str, const wchar_t t)
		{
			for (typename StrBase1::Size i = 0; i != str.pSize; ++i)
			{
				if (t != str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ValueNotOf(const StrBase1& str, const wchar_t t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = offset; i < str.pSize; ++i)
			{
				if (t != str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueNotOf(const StrBase1& str, const wchar_t t)
		{
			for (typename StrBase1::Size i = str.pSize - 1; i != StrBase1::npos; --i)
			{
				if (t != str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueNotOf(const StrBase1& str, const wchar_t t, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = ((offset != StrBase1::npos) ? offset : str.pSize - 1);
				i != StrBase1::npos; --i)
			{
				if (t != str.pPtr[i])
					return i;
			}
			return StrBase1::npos;
		}


	};

	template<class StrBase1, typename W, int N>
	struct Find<StrBase1, W[N]>
	{
		static typename StrBase1::Size Value(const StrBase1& str, const W* t, typename StrBase1::Size offset = 0)
		{
			if (t && '\0' != *t && offset < str.pSize)
			{
				while (1)
				{
					// Trying to find the next occurenceof the first char
					offset = Find<StrBase1,W>::Value(str, *t, offset);
					if (StrBase1::npos == offset || offset + N - 1 > str.pSize)
						return StrBase1::npos;
					if (!memcmp(str.pPtr + offset, t, (N - 1) * sizeof(W)))
						return offset;
					++offset;
				}
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValue(const StrBase1& str, const W* t, typename StrBase1::Size offset = StrBase1::npos)
		{
			if (t && '\0' != *t && str.notEmpty())
			{
				if (offset == StrBase1::npos)
					offset = str.pSize - 1;
				while (StrBase1::npos != offset)
				{
					// Trying to find the next occurenceof the first char
					offset = str.find_last_of(*t, offset);
					if (StrBase1::npos == offset || offset + N - 1 > str.pSize)
						return StrBase1::npos;
					if (!memcmp(str.pPtr + offset, t, (N - 1) * sizeof(W)))
						return offset;
					--offset;
				}
			}
			return StrBase1::npos;
		}

		static typename StrBase1::Size ValueOf(const StrBase1& str, const W* t, typename StrBase1::Size offset = 0)
		{
			for (typename StrBase1::Size i = offset; i < str.pSize; ++i)
			{
				if (StrBase1::HasChar(str.pPtr[i], t))
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueOf(const StrBase1& str, const W* t, typename StrBase1::Size offset = StrBase1::npos)
		{
			if (offset < str.pSize)
			{
				typename StrBase1::Size i = str.pSize;
				do
				{
					--i;
					if (StrBase1::HasChar(str.pPtr[i], t))
						return i;
				} while (i != 0);
			}
			return StrBase1::npos;
		}

		static typename StrBase1::Size ValueNotOf(const StrBase1& str, const W* t, typename StrBase1::Size offset = 0)
		{
			for (typename StrBase1::Size i = offset; i < str.pSize; ++i)
			{
				if (!StrBase1::HasChar(str.pPtr[i], t))
					return i;
			}
			return StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueNotOf(const StrBase1& str, const W* t, typename StrBase1::Size offset = StrBase1::npos)
		{
			if (offset < str.pSize)
			{
				typename StrBase1::Size i = str.pSize;
				do
				{
					--i;
					if (!StrBase1::HasChar(str.pPtr[i], t))
						return i;
				} while (i != 0);
			}
			return StrBase1::npos;
		}


	};

	template<class StrBase1, typename W>
	struct Find<StrBase1, W*>
	{
		static typename StrBase1::Size RawValue(const StrBase1& str, const W* t,
			const typename StrBase1::Size length, typename StrBase1::Size offset)
		{
			while (1)
			{
				// Trying to find the next occurenceof the first char
				offset = str.find(*t, offset);
				if (StrBase1::npos == offset || offset + length > str.pSize)
					return StrBase1::npos;
				if (!memcmp(str.pPtr + offset, t, length * sizeof(W)))
					return offset;
				++offset;
			}
			return StrBase1::npos;
		}

		static typename StrBase1::Size RawValueOf(const StrBase1& str, const W* t,
			const typename StrBase1::Size length, typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = offset; i < length; ++i)
			{
				if (StrBase1::HasChar(str.pPtr[i], t))
					return i;
			}
			return StrBase1::npos;
		}


		static typename StrBase1::Size RawValueNotOf(const StrBase1& str, const W* t,
			const typename StrBase1::Size length, typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = offset; i < length; ++i)
			{
				if (!StrBase1::HasChar(str.pPtr[i], t))
					return i;
			}
			return StrBase1::npos;
		}


		static typename StrBase1::Size Value(const StrBase1& str, const W* t, typename StrBase1::Size offset = 0)
		{
			return (t && '\0' != *t && offset < str.pSize)
				? RawValue(str, t, Length<StrBase1,W*>::Value(t), offset)
				: StrBase1::npos;
		}
		static typename StrBase1::Size ReverseRawValue(const StrBase1& str, const W* t,
			const typename StrBase1::Size length, typename StrBase1::Size offset)
		{
			if (offset >= str.pSize)
				offset = str.pSize - 1;
			while (1)
			{
				// Trying to find the next occurenceof the first char
				offset = str.find(*t, offset);
				if (StrBase1::npos == offset || offset + length > str.pSize)
					return StrBase1::npos;
				if (!memcmp(str.pPtr + offset, t, length * sizeof(W)))
					return offset;
				++offset;
			}
			return StrBase1::npos;
		}

		static typename StrBase1::Size ReverseValue(const StrBase1& str, const W* t, typename StrBase1::Size offset = StrBase1::npos)
		{
			return (t && '\0' != *t && str.pSize)
				? ReverseRawValue(str, t, Length<StrBase1,W*>::Value(t), offset)
				: StrBase1::npos;
		}

		static typename StrBase1::Size ValueOf(const StrBase1& str, const W* t, typename StrBase1::Size offset = 0)
		{
			return (t && '\0' != *t && offset < str.pSize)
				? RawValueOf(str, t, Length<StrBase1,W*>::Value(t), offset)
				: StrBase1::npos;
		}

		static typename StrBase1::Size ValueNotOf(const StrBase1& str, const W* t, typename StrBase1::Size offset = 0)
		{
			return (t && '\0' != *t && offset < str.pSize)
				? RawValueNotOf(str, t, Length<StrBase1,W*>::Value(t), offset)
				: StrBase1::npos;
		}
		static typename StrBase1::Size ReverseRawValueNotOf(const StrBase1& str, const W* t,
			const typename StrBase1::Size length, typename StrBase1::Size offset)
		{
			if (offset >= str.pSize)
				offset = str.pSize - 1;
			while (1)
			{
				// Trying to find the next occurenceof the first char
				offset = str.find(*t, offset);
				if (StrBase1::npos == offset || offset + length > str.pSize)
					return StrBase1::npos;
				if (memcmp(str.pPtr + offset, t, length * sizeof(W)))
					return offset;
				++offset;
			}
			return StrBase1::npos;
		}

		static typename StrBase1::Size ReverseValueNotOf(const StrBase1& str, const W* t, typename StrBase1::Size offset = StrBase1::npos)
		{
			return (t && '\0' != *t && str.pSize)
				? ReverseRawValueNotOf(str, t, Length<StrBase1,W*>::Value(t), offset)
				: StrBase1::npos;
		}

	};

	template<class StrBase1, typename W>
	struct Find<StrBase1, std::basic_string<W> >
	{
		static typename StrBase1::Size Value(const StrBase1& str, const std::basic_string<W>& t, typename StrBase1::Size offset = 0)
		{
			return (!t.empty() && offset < str.pSize)
				? Find<StrBase1, W*>::RawValue(str, t.c_str(), t.size(), offset)
				: StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValue(const StrBase1& str, const std::basic_string<W>& t, typename StrBase1::Size offset = StrBase1::npos)
		{
			return (!t.empty() && str.pSize)
				? Find<StrBase1, W*>::ReverseRawValue(str, t.c_str(), t.size(), offset)
				: StrBase1::npos;
		}

		static typename StrBase1::Size ValueNotOf(const StrBase1& str, const std::basic_string<W>& t, typename StrBase1::Size offset = 0)
		{
			return (!t.empty() && offset < str.pSize)
				? Find<StrBase1, W*>::RawValueNotOf(str, t.c_str(), t.size(), offset)
				: StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueNotOf(const StrBase1& str, const std::basic_string<W>& t, typename StrBase1::Size offset = StrBase1::npos)
		{
			return (!t.empty() && str.pSize)
				? Find<StrBase1, W*>::ReverseRawValueNotOf(str, t.c_str(), t.size(), offset)
				: StrBase1::npos;
		}


	};

	template<class StrBase1, typename W>
	struct Find<StrBase1, std::basic_string<W>* >
	{
		static typename StrBase1::Size Value(const StrBase1& str, const std::basic_string<W>* t, typename StrBase1::Size offset = 0)
		{
			return (t && !t->empty() && offset < str.pSize)
				? Find<StrBase1, W*>::RawValue(str, t->c_str(), t->size(), offset)
				: StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValue(const StrBase1& str, const std::basic_string<W>* t, typename StrBase1::Size offset = StrBase1::npos)
		{
			return (t && !t->empty() && str.pSize)
				? Find<StrBase1, W*>::ReverseRawValue(str, t->c_str(), t->size(), offset)
				: StrBase1::npos;
		}

		static typename StrBase1::Size ValueNotOf(const StrBase1& str, const std::basic_string<W>* t, typename StrBase1::Size offset = 0)
		{
			return (t && !t->empty() && offset < str.pSize)
				? Find<StrBase1, W*>::RawValueNotOf(str, t->c_str(), t->size(), offset)
				: StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueNotOf(const StrBase1& str, const std::basic_string<W>* t, typename StrBase1::Size offset = StrBase1::npos)
		{
			return (t && !t->empty() && str.pSize)
				? Find<StrBase1, W*>::ReverseRawValueNotOf(str, t->c_str(), t->size(), offset)
				: StrBase1::npos;
		}


	};


	template<class StrBase1, typename W, int N>
	struct Find<StrBase1, Yuni::StringBase<W,N> >
	{
		static typename StrBase1::Size Value(const StrBase1& str, const Yuni::StringBase<W,N>& t, typename StrBase1::Size offset = 0)
		{
			return (t.pSize && offset < str.pSize)
				? Find<StrBase1, W*>::RawValue(str, t.pPtr, t.pSize, offset)
				: StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValue(const StrBase1& str, const Yuni::StringBase<W,N>& t, typename StrBase1::Size offset = StrBase1::npos)
		{
			return (t.pSize && str.pSize)
				? Find<StrBase1, W*>::ReverseRawValue(str, t.pPtr, t.pSize, offset)
				: StrBase1::npos;
		}

		static typename StrBase1::Size ValueNotOf(const StrBase1& str, const Yuni::StringBase<W,N>& t, typename StrBase1::Size offset = 0)
		{
			return (t.pSize && offset < str.pSize)
				? Find<StrBase1, W*>::RawValueNotOf(str, t.pPtr, t.pSize, offset)
				: StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueNotOf(const StrBase1& str, const Yuni::StringBase<W,N>& t, typename StrBase1::Size offset = StrBase1::npos)
		{
			return (t.pSize && str.pSize)
				? Find<StrBase1, W*>::ReverseRawValueNotOf(str, t.pPtr, t.pSize, offset)
				: StrBase1::npos;
		}


	};

	template<class StrBase1, typename W, int N>
	struct Find<StrBase1, Yuni::StringBase<W,N>* >
	{
		static typename StrBase1::Size Value(const StrBase1& str, const Yuni::StringBase<W,N>* t, typename StrBase1::Size offset = 0)
		{
			return (t && t->pSize && offset < str.pSize)
				? Find<StrBase1, W*>::RawValue(str, t->pPtr, t->pSize, offset)
				: StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValue(const StrBase1& str, const Yuni::StringBase<W,N>* t, typename StrBase1::Size offset = StrBase1::npos)
		{
			return (t && t->pSize && str.pSize)
				? Find<StrBase1, W*>::ReverseRawValue(str, t->pPtr, t->pSize, offset)
				: StrBase1::npos;
		}

		static typename StrBase1::Size ValueNotOf(const StrBase1& str, const Yuni::StringBase<W,N>* t, typename StrBase1::Size offset = 0)
		{
			return (t && t->pSize && offset < str.pSize)
				? Find<StrBase1, W*>::RawValueNotOf(str, t->pPtr, t->pSize, offset)
				: StrBase1::npos;
		}
		static typename StrBase1::Size ReverseValueNotOf(const StrBase1& str, const Yuni::StringBase<W,N>* t, typename StrBase1::Size offset = StrBase1::npos)
		{
			return (t && t->pSize && str.pSize)
				? Find<StrBase1, W*>::ReverseRawValueNotOf(str, t->pPtr, t->pSize, offset)
				: StrBase1::npos;
		}


	};





	template<class StrBase, typename U>
	struct Remove
	{
		static typename StrBase::Size
		Run(StrBase& str, const U& u, typename StrBase::Size offset,
			const typename StrBase::Size maxOccurences)
		{
			// The length of the substring to find
			const typename StrBase::Size len(StrBase::Length(u));

			if (len)
			{
				// The number of occurences
				typename StrBase::Size n(0);

				// Loop
				while (offset < str.pSize && n != maxOccurences)
				{
					// Looking for the next substring
					offset = str.find(u, offset);

					// Nothing, go away
					if (offset == StrBase::npos)
						return n;

					// There is a substring to remove
					str.erase(offset, len);
					// An occurence has been found
					++n;
				}
				return n;
			}
			return 0;
		}
	};


	template<class StrBase, typename W, int N>
	struct Remove<StrBase, W[N]>
	{
		static typename StrBase::Size
		Run(StrBase& str, const W* u, typename StrBase::Size offset,
			const typename StrBase::Size maxOccurences)
		{
			// The number of occurences
			typename StrBase::Size n(0);

			// Loop
			while (offset < str.pSize && n != maxOccurences)
			{
				// Looking for the next substring
				offset = Find<StrBase, W*>::RawValue(str, u, N - 1, offset);

				// Nothing, go away
				if (offset == StrBase::npos)
					return n;

				// There is a substring to remove
				str.erase(offset, N - 1);
				// An occurence has been found
				++n;
			}
			return n;
		}
	};

	template<class StrBase, typename W>
	struct Remove<StrBase, std::basic_string<W> >
	{
		static typename StrBase::Size
		Run(StrBase& str, const std::basic_string<W>& u, typename StrBase::Size offset,
			const typename StrBase::Size maxOccurences)
		{
			if (!u.empty())
			{
				// The number of occurences
				typename StrBase::Size n(0);

				// Loop
				while (offset < str.pSize && n != maxOccurences)
				{
					// Looking for the next substring
					offset = Find<StrBase, W*>::RawValue(str, u.c_str(), u.size(), offset);

					// Nothing, go away
					if (offset == StrBase::npos)
						return n;

					// There is a substring to remove
					str.erase(offset, u.size());
					// An occurence has been found
					++n;
				}
				return n;
			}
			return 0;
		}
	};


	template<class StrBase, typename W, int Chnk1>
	struct Remove<StrBase, StringBase<W,Chnk1> >
	{
		static typename StrBase::Size
		Run(StrBase& str, const StringBase<W,Chnk1>& u, typename StrBase::Size offset,
			const typename StrBase::Size maxOccurences)
		{
			if (u.pSize)
			{
				// The number of occurences
				typename StrBase::Size n(0);

				// Loop
				while (offset < str.pSize && n != maxOccurences)
				{
					// Looking for the next substring
					offset = Find<StrBase, W*>::RawValue(str, u.pPtr, u.pSize, offset);

					// Nothing, go away
					if (offset == StrBase::npos)
						return n;

					// There is a substring to remove
					str.erase(offset, u.pSize);
					// An occurence has been found
					++n;
				}
				return n;
			}
			return 0;
		}
	};


	template<class StrBase, typename W>
	struct Remove<StrBase, std::basic_string<W>* >
	{
		static typename StrBase::Size
		Run(StrBase& str, const std::basic_string<W>* u, typename StrBase::Size offset,
			const typename StrBase::Size maxOccurences)
		{
			if (u && !u->empty())
			{
				// The number of occurences
				typename StrBase::Size n(0);

				// Loop
				while (offset < str.pSize && n != maxOccurences)
				{
					// Looking for the next substring
					offset = Find<StrBase, W*>::RawValue(str, u->c_str(), u->size(), offset);

					// Nothing, go away
					if (offset == StrBase::npos)
						return n;

					// There is a substring to remove
					str.erase(offset, u->size());
					// An occurence has been found
					++n;
				}
				return n;
			}
			return 0;
		}
	};



	template<class StrBase, typename W, int Chnk1>
	struct Remove<StrBase, StringBase<W,Chnk1>* >
	{
		static typename StrBase::Size
		Run(StrBase& str, const StringBase<W,Chnk1>* u, typename StrBase::Size offset,
			const typename StrBase::Size maxOccurences)
		{
			if (u && u->pSize)
			{
				// The number of occurences
				typename StrBase::Size n(0);

				// Loop
				while (offset < str.pSize && n != maxOccurences)
				{
					// Looking for the next substring
					offset = Find<StrBase, W*>::RawValue(str, u->pPtr, u->pSize, offset);

					// Nothing, go away
					if (offset == StrBase::npos)
						return n;

					// There is a substring to remove
					str.erase(offset, u->pSize);
					// An occurence has been found
					++n;
				}
				return n;
			}
			return 0;
		}
	};




	/*!
	** \brief Generic implementation of vsnprintf
	*/
	template<class C>
	int vnsprintf(C* buffer, size_t bufferSize, const C* format, va_list argptr);


	template<>
	inline int
	vnsprintf<char>(char* buffer, size_t bufferSize, const char* format, va_list argptr)
	{
		# if defined YUNI_OS_MSVC
		#	ifdef YUNI_MSVC_SECURE_VSPRINTF
			return _vsnprintf_s(buffer, bufferSize-1, _TRUNCATE, format, argptr);
		#	else
			return _vsnprintf(buffer, bufferSize-1, format, argptr);
		#	endif
		# else
			return vsnprintf(buffer, bufferSize-1, format, argptr);
		# endif
	}

	# ifdef YUNI_OS_WINDOWS
	template<>
	inline int
	vnsprintf<wchar_t>(wchar_t* buffer, size_t bufferSize, const wchar_t* format, va_list argptr)
	{
		# if defined YUNI_OS_MSVC
		#	ifdef YUNI_MSVC_SECURE_VSPRINTF
			return _vsnwprintf_s(buffer, bufferSize-1, _TRUNCATE, format, argptr);
		#	else
			return _vsnwprintf(buffer, bufferSize-1, format, argptr);
		#	endif
		# else
			return vsnwprintf(buffer, bufferSize-1, format, argptr);
		# endif
	}
	# endif



	template<class C, int Chunk>
	static int
	vsprintf(StringBase<C,Chunk>& out, const C* format, va_list args)
	{
		if (!format || '\0' == *format)
			return 0;

		static const size_t ChunkSize = 1024;
		size_t curBufSize(0);

		// keep trying to write the string to an ever-increasing buffer until
		// either we get the string written or we run out of memory
		while (1)
		{
			// allocate a local buffer
			curBufSize += ChunkSize;
			C* buffer = new C[curBufSize];

			// format output to local buffer
			const int i = Private::StringImpl::vnsprintf<C>(buffer, curBufSize * sizeof(C), format, args);
			if (-1 == i)
			{
				delete[] buffer;
				continue;
			}
			else
			{
				if (i < 0)
				{
					delete[] buffer;
					return i;
				}
			}

			out.append(buffer, i);
			delete[] buffer;
			return i;
		}
		return -1;
	}





} // namespace StringImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_TOOLBOX_STRING_STRING_PRIVATE_HXX__
