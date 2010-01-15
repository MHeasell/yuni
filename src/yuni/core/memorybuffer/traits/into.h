#ifndef __YUNI_CORE_MEMORYBUFFER_ISTRING_TRAITS_INTO_H__
# define __YUNI_CORE_MEMORYBUFFER_ISTRING_TRAITS_INTO_H__

# include <stdlib.h>


namespace Yuni
{
namespace Core
{
namespace Extension
{
namespace IString
{


	/*!
	** \brief Generic implementation
	*/
	template<class T>
	struct To
	{
		enum { valid = 0, };

		template<class StringT> static bool Perform(const StringT&, T& out)
		{
			out = T();
			return true;
		}

		template<class StringT> static T Perform(const StringT&)
		{
			return T();
		}
	};


	/*!
	** \brief const char*
	*/
	template<>
	struct To<char*>
	{
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, const char*& out)
		{
			out = s.data();
			return true;
		}

		template<class StringT> static const char* Perform(const StringT& s)
		{
			return s.data();
		}
	};



	

	/*!
	** \brief IString<>, with the same POD type
	*/
	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroTerminatedT, class C>
	struct To<Yuni::Core::IString<ChunkSizeT, ExpandableT, ZeroTerminatedT, C> >
	{
		typedef Yuni::Core::IString<ChunkSizeT, ExpandableT, ZeroTerminatedT, C> TargetType;
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, TargetType& out)
		{
			out = s;
			return true;
		}

		template<class StringT> static TargetType Perform(const StringT& s)
		{
			return s;
		}
	};


	/*!
	** \brief std::string
	*/
	template<class CharT, class TraitsT, class AllocT>
	struct To<std::basic_string<CharT,TraitsT, AllocT> >
	{
		typedef std::basic_string<CharT,TraitsT, AllocT> TargetType;
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, TargetType& out)
		{
			out.assign(s.c_str(), s.size());
			return true;
		}

		template<class StringT> static TargetType Perform(const StringT& s)
		{
			return TargetType(s.c_str(), s.size());
		}
	};


	/*!
	** \brief char
	*/
	template<>
	struct To<char>
	{
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, char& out)
		{
			out = (!s) ? '\0' : s[0];
			return true;
		}

		template<class StringT> static char Perform(const StringT& s)
		{
			return (!s) ? '\0' : s[0];
		}
	};


	/*!
	** \brief unsigned char
	*/
	template<>
	struct To<unsigned char>
	{
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, unsigned char& out)
		{
			out = (unsigned char)((!s) ? '\0' : s[0]);
			return true;
		}

		template<class StringT> static unsigned char Perform(const StringT& s)
		{
			return (unsigned char)((!s) ? '\0' : s[0]);
		}
	};


	/*!
	** \brief char[]
	*/
	template<int N>
	struct To<char[N]>
	{
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, char*& out)
		{
			if (StringT::zeroTerminated)
				// We have to copy the final zero in the same time
				memcpy(out, s.data(), (N-1) < s.sizeInBytes() ? N : s.sizeInBytes() + 1);
			else
				// The N char can be used
				memcpy(out, s.data(), (N) < s.sizeInBytes() ? N : s.sizeInBytes());
			return true;
		}

		template<class StringT> static char* Perform(const StringT& s)
		{
			return s.data();
		}
	};



	/*!
	** \brief bool
	*/
	template<>
	struct To<bool>
	{
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, bool& out)
		{
			out = Perform(s);
			return true;
		}

		template<class StringT> static bool Perform(const StringT& s)
		{
			if (s.notEmpty())
			{
				const unsigned int count = s.sizeInBytes();
				if (count < 5)
				{
					if (count == 1)
						return ('1' == s[0] || 'Y' == s[0] || 'y' == s[0] || 'O' == s[0] || 'o' == s[0]);

					char buffer[5] = {0,0,0,0,0};
					for (unsigned int i = 0; i < count; ++i)
						buffer[i] = ::tolower(s[i]);
					return (!strcmp("true", buffer) || !strcmp("on", buffer) || !strcmp("yes", buffer));
				}
			}
			return false;
		}
	};


	template<typename C>
	struct AutoDetectBaseNumber
	{
		template<class U>
		static const C* Value(const U& s, int& base)
		{
			switch (s[0])
			{
				case '#' :
					{
						base = 16;
						return s.data() + 1;
					}
				case '0' :
					{
						if (s.size() > 2 && (s[1] == 'x' || s[1] == 'X'))
						{
							base = 16;
							return s.data() + 2;
						}
					}
			}
			base = 10;
			return s.data();
		}
	};


# define YUNI_CORE_EXTENSION_ISTRING_TO_NUMERIC(TYPE,CONVERT)  \
	template<> \
	struct To<TYPE> \
	{ \
		enum { valid = 1 }; \
		\
		template<class StringT> static bool Perform(const StringT& s, TYPE& out) \
		{ \
			if (!s) \
			{ \
				out = TYPE(); \
				return true; \
			} \
			typedef typename StringT::value_type C; \
			C* pend; \
			int base; \
			const C* p = AutoDetectBaseNumber<C>::Value(s, base); \
			out = (TYPE)::CONVERT(p, &pend, base); \
			return (NULL != pend && '\0' == *pend); \
		} \
		\
		template<class StringT> static TYPE Perform(const StringT& s) \
		{ \
			if (!s) \
				return TYPE(); \
			typedef typename StringT::value_type C; \
			C* pend; \
			int base; \
			const C* p = AutoDetectBaseNumber<C>::Value(s, base); \
			return (TYPE)::CONVERT(p, &pend, base); \
		} \
	}



	YUNI_CORE_EXTENSION_ISTRING_TO_NUMERIC(sint16, strtol);
	YUNI_CORE_EXTENSION_ISTRING_TO_NUMERIC(sint32, strtol);
	YUNI_CORE_EXTENSION_ISTRING_TO_NUMERIC(sint64, strtol);

	YUNI_CORE_EXTENSION_ISTRING_TO_NUMERIC(uint16, strtoul);
	YUNI_CORE_EXTENSION_ISTRING_TO_NUMERIC(uint32, strtoul);
	YUNI_CORE_EXTENSION_ISTRING_TO_NUMERIC(uint64, strtoul);


	# ifdef YUNI_HAS_LONG
	YUNI_CORE_EXTENSION_ISTRING_TO_NUMERIC(long, strtol);
	YUNI_CORE_EXTENSION_ISTRING_TO_NUMERIC(unsigned long, strtoul);
	# endif


# undef YUNI_CORE_EXTENSION_ISTRING_TO_NUMERIC




	/*!
	** \brief float
	*/
	template<>
	struct To<float>
	{
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, float& out)
		{
			typedef typename StringT::value_type C;
			if (s.notEmpty())
			{
				C* pend;
				# ifdef YUNI_OS_MSVC
				// Visual Studio does not support strtof
				out = (float)strtod(s.c_str(), &pend);
				# else
				out = (float)strtof(s.c_str(), &pend);
				# endif
				return (NULL != pend && '\0' == *pend);
			}
			out = 0.f;
			return true;
		}

		template<class StringT> static float Perform(const StringT& s)
		{
			typedef typename StringT::value_type C;
			if (s.notEmpty())
			{
				C* pend;
				# ifdef YUNI_OS_MSVC
				// Visual Studio does not support strtof
				return (float)strtod(s.c_str(), &pend);
				# else
				return (float)strtof(s.c_str(), &pend);
				# endif
			}
			return 0.f;
		}
	};


	/*!
	** \brief double
	*/
	template<>
	struct To<double>
	{
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, double& out)
		{
			typedef typename StringT::value_type C;
			if (s.notEmpty())
			{
				C* pend;
				out = (double)strtof(s.c_str(), &pend);
				return (NULL != pend && '\0' == *pend);
			}
			out = 0.;
			return true;
		}

		template<class StringT> static double Perform(const StringT& s)
		{
			typedef typename StringT::value_type C;
			if (s.notEmpty())
			{
				C* pend;
				return (double)strtof(s.c_str(), &pend);
			}
			return 0.;
		}
	};


	/*!
	** \brief const void*
	*/
	template<>
	struct To<void*>
	{
		enum { valid = 1 };

		template<class StringT> static bool Perform(const StringT& s, const void*& out)
		{
			if (sizeof(void*) == 4)
			{
				uint32 p;
				if (To<uint32>::Perform(s, p))
				{
					out = (void*) p;
					return true;
				}
				out = 0x0;
				return false;
			}
			else
			{
				uint64 p;
				if (To<uint64>::Perform(s, p))
				{
					out = (void*) p;
					return true;
				}
				out = 0x0;
				return false;
			}
		}

		template<class StringT> static void* Perform(const StringT& s)
		{
			return (void*)((sizeof(void*) == 4)
				? To<uint32>::Perform(s) : To<uint64>::Perform(s));
		}
	};





} // namespace IString
} // namespace Extension
} // namespace Core
} // namespace Yuni

#endif // __YUNI_CORE_MEMORYBUFFER_ISTRING_TRAITS_INTO_H__
