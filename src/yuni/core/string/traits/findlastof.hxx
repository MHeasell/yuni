#ifndef __YUNI_CORE_STRING_STRING_TRAITS_FIND_LAST_OF_HXX__
# define __YUNI_CORE_STRING_STRING_TRAITS_FIND_LAST_OF_HXX__


namespace Yuni
{
namespace Private
{
namespace StringImpl
{


	template<class StrBase1, bool Equals>
	struct FindFirstOf<StrBase1, typename StrBase1::Char, Equals>
	{
		static typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char toFind)
		{
			for (typename StrBase1::Size i = 0; i != s.pSize; ++i)
			{
				if (CheckEquality<Equals>::Value(toFind, s.pPtr[i]))
					return i;
			}
			return StrBase1::npos;
		}

		static typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char toFind, const typename StrBase1::Size offset)
		{
			for (typename StrBase1::Size i = offset; i < s.pSize; ++i)
			{
				if (CheckEquality<Equals>::Value(toFind, s.pPtr[i]))
					return i;
			}
			return StrBase1::npos;
		}
	};


	template<class StrBase1, bool Equals>
	struct FindFirstOf<StrBase1, typename StrBase1::Char*, Equals>
	{
		static typename StrBase1::Size RawValue(const StrBase1& s, const typename StrBase1::Char* toFind,
			typename StrBase1::Size offset, /* offset in `s` */
			typename StrBase1::Size len     /* Length of `toFind` */)
		{
			if (len && toFind && offset < s.pSize)
			{
				typename StrBase1::Size j;
				for (typename StrBase1::Size i = offset; i != s.pSize; ++i)
				{
					for (j = 0; j != len; ++j)
					{
						if (CheckEquality<Equals>::Value(toFind[j], s.pPtr[i]))
							return i;
					}
				}
			}
			return StrBase1::npos;
		}


		static inline typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char* toFind)
		{
			return RawValue(s, toFind, 0, StrBase1::Length(toFind));
		}

		static inline typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char* toFind, const typename StrBase1::Size offset)
		{
			return RawValue(s, toFind, offset, StrBase1::Length(toFind));
		}
	};


	template<class StrBase1, bool Equals, int N>
	struct FindFirstOf<StrBase1, typename StrBase1::Char[N], Equals>
	{
		static typename StrBase1::Size RawNValue(const StrBase1& s, const typename StrBase1::Char* toFind,
			typename StrBase1::Size offset /* offset in `s` */)
		{
			if ((N - 1) && toFind && offset < s.pSize)
			{
				typename StrBase1::Size j;
				for (typename StrBase1::Size i = offset; i != s.pSize; ++i)
				{
					for (j = 0; j != (N - 1); ++j)
					{
						if (CheckEquality<Equals>::Value(toFind[j], s.pPtr[i]))
							return i;
					}
				}
			}
			return StrBase1::npos;
		}


		static inline typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char* toFind)
		{
			return RawNValue(s, toFind, 0);
		}

		static inline typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char* toFind, const typename StrBase1::Size offset)
		{
			return RawNValue(s, toFind, offset);
		}
	};


	template<class StrBase1, bool Equals, int Cnk1>
	struct FindFirstOf<StrBase1, StringBase<typename StrBase1::Char, Cnk1>, Equals>
	{
		static inline typename StrBase1::Size Value(const StrBase1& s, const StringBase<typename StrBase1::Char, Cnk1>& toFind)
		{
			return FindFirstOf<StrBase1, typename StrBase1::Char*, Equals>::RawValue(s, toFind.pPtr, 0, toFind.pSize);
		}

		static inline typename StrBase1::Size Value(const StrBase1& s, const StringBase<typename StrBase1::Char, Cnk1>& toFind, const typename StrBase1::Size offset)
		{
			return FindFirstOf<StrBase1, typename StrBase1::Char*, Equals>::RawValue(s, toFind.pPtr, offset, toFind.pSize);
		}
	};



	template<class StrBase1, bool Equals>
	struct FindLastOf<StrBase1, typename StrBase1::Char, Equals>
	{
		static typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char toFind)
		{
			if (s.pSize)
			{
				typename StrBase1::Size i = s.pSize;
				--i;
				do
				{
					if (CheckEquality<Equals>::Value(toFind, s.pPtr[i]))
						return i;
				}
				while (--i);
			}
			return StrBase1::npos;
		}

		static typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char toFind, const typename StrBase1::Size offset)
		{
			if (offset < s.pSize)
			{
				typename StrBase1::Size i = offset;
				do
				{
					if (CheckEquality<Equals>::Value(toFind, s.pPtr[i]))
						return i;
				}
				while (--i);
			}
			return StrBase1::npos;
		}

	};

	template<class StrBase1, bool Equals>
	struct FindLastOf<StrBase1, typename StrBase1::Char*, Equals>
	{
		static typename StrBase1::Size RawValue(const StrBase1& s, const typename StrBase1::Char* toFind,
			typename StrBase1::Size offset, /* offset in `s` */
			typename StrBase1::Size len     /* Length of `toFind` */)
		{
			if (len && toFind && offset < s.pSize)
			{
				typename StrBase1::Size j;
				typename StrBase1::Size i = offset;
				do
				{
					for (j = 0; j != len; ++j)
					{
						if (CheckEquality<Equals>::Value(toFind[j], s.pPtr[i]))
							return i;
					}
				}
				while (--i);
			}
			return StrBase1::npos;
		}


		static inline typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char* toFind)
		{
			return s.pSize
				? RawValue(s, toFind, s.pSize - 1, StrBase1::Length(toFind))
				: StrBase1::npos;
		}

		static typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char toFind, const typename StrBase1::Size offset)
		{
			return RawValue(s, toFind, offset, StrBase1::Length(toFind));
		}

	};

	template<class StrBase1, typename C, bool Equals, int N>
	struct FindLastOf<StrBase1, C[N], Equals>
	{
		static typename StrBase1::Size RawNValue(const StrBase1& s, const C* toFind,
			typename StrBase1::Size offset /* offset in `s` */)
		{
			if ((N - 1) && toFind && offset < s.pSize)
			{
				typename StrBase1::Size j;
				typename StrBase1::Size i = offset;
				do
				{
					for (j = 0; j != (N - 1); ++j)
					{
						if (CheckEquality<Equals>::Value(toFind[j], s.pPtr[i]))
							return i;
					}
				}
				while (--i);
			}
			return StrBase1::npos;
		}


		static inline typename StrBase1::Size Value(const StrBase1& s, const C* toFind)
		{
			return s.pSize ? RawNValue(s, toFind, s.pSize - 1) : StrBase1::npos;
		}

		static inline typename StrBase1::Size Value(const StrBase1& s, const C* toFind, const typename StrBase1::Size offset)
		{
			return RawNValue(s, toFind, offset);
		}
	};


	template<class StrBase1, bool Equals, int Cnk1>
	struct FindLastOf<StrBase1, StringBase<typename StrBase1::Char, Cnk1>, Equals>
	{
		static inline typename StrBase1::Size Value(const StrBase1& s, const StringBase<typename StrBase1::Char, Cnk1>& toFind)
		{
			return s.pSize
				? FindLastOf<StrBase1, typename StrBase1::Char*, Equals>::RawValue(s, toFind.pPtr, s.pSize - 1, toFind.pSize)
				: StrBase1::npos;
		}

		static typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char toFind, const typename StrBase1::Size offset)
		{
			return FindLastOf<StrBase1, typename StrBase1::Char*, Equals>::RawValue(s, toFind.pPtr, offset, toFind.pSize);
		}
	};

	template<class StrBase1, bool Equals>
	struct FindLastOf<StrBase1, std::basic_string<typename StrBase1::Char>, Equals>
	{
		static inline typename StrBase1::Size Value(const StrBase1& s, const std::basic_string<typename StrBase1::Char>& toFind)
		{
			return s.pSize
				? FindLastOf<StrBase1, typename StrBase1::Char*, Equals>::RawValue(s, toFind.c_str(), s.pSize - 1, toFind.size())
				: StrBase1::npos;
		}

		static typename StrBase1::Size Value(const StrBase1& s, const typename StrBase1::Char toFind, const typename StrBase1::Size offset)
		{
			return FindLastOf<StrBase1, typename StrBase1::Char*, Equals>::RawValue(s, toFind.c_str(), offset, toFind.size());
		}
	};




} // namespace StringImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_STRING_STRING_TRAITS_FIND_LAST_OF_HXX__
