#ifndef __YUNI_POLICIES_CHECKS_H__
# define __YUNI_POLICIES_CHECKS_H__


# include "policies.h"


namespace Yuni
{
namespace Policy
{
namespace Checking
{

	/*!
	** \defgroup CheckingPolicy Checking policies
	** \ingroup Policies
	*/


	/*! \class None
	** \brief Do not make any check
	** \ingroup CheckingPolicy
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

	}; // class None


} // namespace Checking
} // namespace Policy
} // namespace Yuni

#endif // __YUNI_POLICIES_CHECKS_H__
