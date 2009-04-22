#ifndef __YUNI_TOOLBOX_STRING_PREFLIGHT_H__
# define __YUNI_TOOLBOX_STRING_PREFLIGHT_H__



// By default, the class Yuni::String can not be inherited
// for performance reasons.
// It is possible to change this behavior in defining `YUNI_STRING_USE_VIRTUAL_DESTRUCTOR`
# ifdef YUNI_STRING_USE_VIRTUAL_DESTRUCTOR
#	define YUNI_STRING_VIRTUAL_DESTRUCTOR  virtual
# else
#	define YUNI_STRING_VIRTUAL_DESTRUCTOR
# endif



namespace Yuni
{

	// Forward declaration
	template<typename C1, int Chunk> class StringBase;


namespace Private
{
namespace StringImpl
{

	// Forward declaration
	template<class StrBase1, class T1> struct Length;
	template<class StrBase1, class T1> struct CountChar;
	template<class StrBase1, class T1> struct HasChar;
	template<class StrBase1, class T1> struct Find;
	template<class StrBase1, class T1> struct Remove;



	/*!
	** \brief Proxy to convert a type to a string
	*/
	template<typename T>
	struct From
	{
		template<typename C1,int Chnk1> friend class StringBase;

		template<typename C, int Chnk>
		static void Append(StringBase<C,Chnk>& s, const T& value);

		template<typename C, int Chnk>
		static void Append(StringBase<C,Chnk>& s, const T& value,
			const typename StringBase<C,Chnk>::Size len);

		template<typename C, int Chnk>
		static void Insert(StringBase<C,Chnk>& s, const T& value,
			const typename StringBase<C,Chnk>::Size offset);

		template<typename C, int Chnk>
		static void Insert(StringBase<C,Chnk>& s, const T& value,
			const typename StringBase<C,Chnk>::Size offset,
			const typename StringBase<C,Chnk>::Size len);

	}; // class From



	/*!
	** \brief Proxy to convert a string to another type
	*/
	template<typename T>
	struct To
	{
		template<typename C, int Chnk>
		static T Value(StringBase<C,Chnk>& s);

		template<typename C, int Chnk>
		static bool Value(StringBase<C,Chnk>& s, T& t);

	}; // class To



	/*!
	** \brief Standard C++ converter from a string to another type
	*/
	template<class T, typename C, int Chnk>
	inline bool StdStringConverter(T& t, const StringBase<C,Chnk>& s, std::ios_base& (*f)(std::ios_base&))
	{
		std::istringstream iss(s);
		return !(iss >> f >> t).fail();
	}



} // namespace StringImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_TOOLBOX_STRING_PREFLIGHT_H__
