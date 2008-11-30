#ifndef __YUNI_MISC_STATIC_H__
# define __YUNI_MISC_STATIC_H__



namespace Yuni
{
namespace Static
{




	namespace Remove
	{
		template <typename T> struct Reference { typedef T t; };
		template <typename T> struct Reference<T&> { typedef T t; };
		template <typename T> struct Reference<const T&> { typedef const T t; };


		template <typename T> struct Const { typedef T t; };
		template <typename T> struct Const<const T> { typedef T t; };

	} // namespace Remove






	template <bool b, typename IfTrue, typename IfFalse>
	struct If
	{
		typedef IfTrue t;
		typedef typename Remove::Const<typename Remove::Reference<IfTrue>::t>::t  RetTrue;
		typedef typename Remove::Const<typename Remove::Reference<IfFalse>::t>::t RetFalse;

		static RetTrue& choose (RetTrue& tr, RetFalse&)
		{return tr;}
		
		static const RetTrue& choose (const RetTrue& tr, const RetFalse&)
		{ return tr; }
	};




	template <typename IfTrue, typename IfFalse>
	struct If<false, IfTrue, IfFalse>
	{
		typedef IfFalse t;
		typedef typename Remove::Const<typename Remove::Reference<IfTrue>::t>::t  RetTrue;
		typedef typename Remove::Const<typename Remove::Reference<IfFalse>::t>::t RetFalse;

		static RetFalse& choose (RetTrue&, RetFalse& fa)
		{ return fa; }
		
		static const RetFalse& choose (const RetTrue&, const RetFalse& fa)
		{ return fa; }
	};



	/*!
	** \brief Compile time Error Definition
	**
	** \attention This class should not be used directly. Consieder the
	** macro `YUNI_STATIC_ASSERT` instead.
	** \see YUNI_STATIC_ASSERT()
	*/
	template<bool X, typename T> struct CompileTimeError;
	template<typename T> struct CompileTimeError<true, T> { enum { Error = 1}; };


} // namespace Static
} // namespaec Yuni


/*!
** \brief String concatenation
*/
# define YUNI_JOIN(X,Y)  X##Y


/*!
** \def YUNI_STATIC_ASSERT(X,ID)
** \brief Assert at compile time
**
** YUNI_STATIC_ASSERT is like assert for C++, except that the test is done at compile time.
** (only when the test is possible at compile time).
**
** Here is an example to produce an error when a code is
** instancied by the compiler:
** \code
** class CanNotBeInstancied
** {
**		YUNI_STATIC_ASSERT(false, ThisClassMustNotBeInstancied);
** };
** // Will produce something like this :
** // error: incomplete type ‘CompileTimeError<false, YuniStaticAssert_ThisClassMustNotBeInstancied::Failed>’ used in nested name specifier
** \endcode
**
** This macro might be used anywhere.
** This tool is used by the ownership policy `NoCopy`.
**
** \param X An expression
** \param ID An unique ID for the current scope
*/
# define YUNI_STATIC_ASSERT(X,ID)  \
		struct YUNI_JOIN(YuniStaticAssert_,ID) \
		{ struct Failed; enum { value = Yuni::Static::CompileTimeError<(0 != (X)), Failed>::Error }; }




#endif // __YUNI_MISC_STATIC_H__
