#ifndef __YUNI_TOOLBOX_POLICIES_TRACKING_H__
# define __YUNI_TOOLBOX_POLICIES_TRACKING_H__

# include "policies.h"



namespace Yuni
{
namespace Policy
{


/*!
** \brief Tracking policies
** \ingroup Policies
*/
namespace Tracking
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
		None(const None&) {}
		template<class U> None(const None<U>&)  {}

	}; // class None




} // namespace Checking
} // namespace Policy
} // namespace Yuni



#endif // __YUNI_TOOLBOX_POLICIES_TRACKING_H__
