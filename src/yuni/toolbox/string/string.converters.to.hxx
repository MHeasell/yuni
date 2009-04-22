#ifndef __YUNI_TOOLBOX_STRING_STD_CONVERTERS_TO_HXX__
# define __YUNI_TOOLBOX_STRING_STD_CONVERTERS_TO_HXX__



namespace Yuni
{
namespace Private
{
namespace StringImpl
{


	template<>
	struct To<char>
	{
		template<typename C, int Chnk>
		static inline char Value(const StringBase<C,Chnk>& s)  {return s.pSize ? *(s.pPtr) : '\0';}

		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s, C& v)
		{
			if (s.pSize)
			{
				v = (*s.pPtr);
				return true;
			}
			return false;
		}
	};

	template<>
	struct To<char*>
	{
		template<typename C, int Chnk>
		static inline const char* Value(const StringBase<C,Chnk>& s)
		{
			return StringBase<C,Chnk>(s).c_str();
		}

		template<typename C, int Chnk>
		static inline const char* Value(StringBase<C,Chnk>& s)
		{
			return s.c_str();
		}
	};

	template<int N>
	struct To<char[N]>
	{
		template<typename C, int Chnk>
		static inline const char* Value(const StringBase<C,Chnk>& s)
		{
			return StringBase<C,Chnk>(s).c_str();
		}

		template<typename C, int Chnk>
		static inline const char* Value(StringBase<C,Chnk>& s)
		{
			return s.c_str();
		}

	};


	template<>
	struct To<bool>
	{
		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s)
		{
			switch (s.pSize)
			{
				case 0:
					return false;
				case 1:
					return ('1' == *(s.pPtr) || 'Y' == *(s.pPtr) || 'y' == *(s.pPtr)
							|| 'O' == *(s.pPtr) || 'o' == *(s.pPtr));
				default:
					{
						if (s.pSize > 4)
							return false;
						char buffer[5] = {0,0,0,0,0};
						strncpy(buffer, s.pPtr, Private::StringImpl::Min((typename StringBase<C,Chnk>::Size)4, s.pSize));
						buffer[0] = (C) tolower(buffer[0]);
						buffer[1] = (C) tolower(buffer[1]);
						buffer[2] = (C) tolower(buffer[2]);
						buffer[3] = (C) tolower(buffer[3]);
						return (!strcmp("true", buffer) || !strcmp("on", buffer) || !strcmp("yes", buffer));
					}
			}
			return false;
		}

		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s, bool& v)
		{
			v = Value(s);
			return true;
		}

	}; // bool


	template<typename U, int N>
	struct To<StringBase<U,N> >
	{
		template<typename C, int Chnk>
		static inline const StringBase<U,N>& Value(const StringBase<C,Chnk>& s)
		{
			return s;
		}

		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s, StringBase<U,N>& v)
		{
			v = s;
			return true;
		}

	}; // std::string


	template<typename U>
	struct To<std::basic_string<U> >
	{
		template<typename C, int Chnk>
		static inline std::basic_string<U> Value(const StringBase<C,Chnk>& s)
		{
			return s.pSize
				? std::basic_string<U>(s.pPtr, s.pSize)
				: std::basic_string<U>();
		}

		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s, std::basic_string<U>& v)
		{
			v.clear();
			if (s.pSize)
				v.append(s.pPtr, s.pSize);
			return true;
		}

	}; // std::string


	template<>
	struct To<sint16>
	{
		template<typename C, int Chnk>
		static inline sint16 Value(const StringBase<C,Chnk>& s)
		{
			char* pend;
			return (sint16)strtol(s.pPtr, &pend, 10);
		}

		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s, sint16& v)
		{
			char* pend;
			v = (sint16)strtol(s.pPtr, &pend, 10);
			return (NULL != pend && '\0' == *pend);
		}

	}; // sint16


	template<>
	struct To<sint32>
	{
		template<typename C, int Chnk>
		static inline sint32 Value(const StringBase<C,Chnk>& s)
		{
			char* pend;
			return (sint32)strtol(s.pPtr, &pend, 10);
		}

		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s, sint32& v)
		{
			char* pend;
			v = (sint32)strtol(s.pPtr, &pend, 10);
			return (NULL != pend && '\0' == *pend);
		}

	}; // sint32



	template<>
	struct To<uint16>
	{
		template<typename C, int Chnk>
		static inline uint16 Value(const StringBase<C,Chnk>& s)
		{
			char* pend;
			return (uint16)strtoul(s.pPtr, &pend, 10);
		}

		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s, uint16& v)
		{
			char* pend;
			v = (uint16)strtoul(s.pPtr, &pend, 10);
			return (NULL != pend && '\0' == *pend);
		}

	}; // uint16


	template<>
	struct To<uint32>
	{
		template<typename C, int Chnk>
		static inline uint32 Value(const StringBase<C,Chnk>& s)
		{
			char* pend;
			return (uint32)strtoul(s.pPtr, &pend, 10);
		}

		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s, uint32& v)
		{
			char* pend;
			v = (uint32)strtoul(s.pPtr, &pend, 10);
			return (NULL != pend && '\0' == *pend);
		}

	}; // uint16

	template<>
	struct To<float>
	{
		template<typename C, int Chnk>
		static inline float Value(const StringBase<C,Chnk>& s)
		{
			char* pend;
			return (float)strtof(s.pPtr, &pend);
		}

		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s, float& v)
		{
			char* pend;
			v = (float)strtof(s.pPtr, &pend);
			return (NULL != pend && '\0' == *pend);
		}

	}; // float



	template<>
	struct To<double>
	{
		template<typename C, int Chnk>
		static inline double Value(const StringBase<C,Chnk>& s)
		{
			char* pend;
			return (float)strtod(s.pPtr, &pend);
		}

		template<typename C, int Chnk>
		static inline bool Value(const StringBase<C,Chnk>& s, double& v)
		{
			char* pend;
			v = (double)strtod(s.pPtr, &pend);
			return (NULL != pend && '\0' == *pend);
		}

	}; // float



} // namespace StringImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_TOOLBOX_STRING_STD_CONVERTERS_TO_HXX__

