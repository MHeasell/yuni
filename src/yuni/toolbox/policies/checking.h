#ifndef __YUNI_POLICIES_CHECKS_H__
# define __YUNI_POLICIES_CHECKS_H__


# include "policies.h"


namespace Yuni
{
namespace Policy
{
	
	
/*!
** \brief Checking policies
** \ingroup Policies
*/
namespace Checking
{


	/*!
	** \brief Do not make any check
	** \ingroup Policies
	*/
	template<class T>
	class None
	{
	public:
		None() {}
		template<class U> None(const None<U>&) {}

		static void onDefault(const T&) {}

		static void onInit(const T&) {}

		static void onDereference(const T&) {}

		static void swapPointer(None&) {}

	}; // class None


} // namespace Checking
} // namespace Policy
} // namespace Yuni

#endif // __YUNI_POLICIES_CHECKS_H__
