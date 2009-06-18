#ifndef __YUNI_CORE_STRING_STRING_TRAITS_LENGTH_HXX__
# define __YUNI_CORE_STRING_STRING_TRAITS_LENGTH_HXX__


namespace Yuni
{
namespace Private
{
namespace StringImpl
{

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
			return ::strlen(t);
		}
	};


	template<class StrBase1>
	struct Length<StrBase1, wchar_t*>
	{
		static inline typename StrBase1::Size Value(const wchar_t* t)
		{
			return ::wcslen(t);
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



} // namespace StringImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_STRING_STRING_TRAITS_LENGTH_HXX__
