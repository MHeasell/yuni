#ifndef __YUNI_TOOLBOX_STATIC_ASSERT_H__
# define __YUNI_TOOLBOX_STATIC_ASSERT_H__

# include "../defines.h"



namespace Yuni
{
namespace Static
{


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




#endif // __YUNI_TOOLBOX_STATIC_ASSERT_H__
