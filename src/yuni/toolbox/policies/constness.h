#ifndef __YUNI_TOOLBOX_POLICIES_CONSTNESS_H__
# define __YUNI_TOOLBOX_POLICIES_CONSTNESS_H__

# include "policies.h"

namespace Yuni
{
namespace Policy
{
namespace Constness
{


	/*!
	** \defgroup ConstnessPolicy Constness policies
	** \ingroup Policies
	*/


	/*!
	** \brief Don't Propagate constness of pointed or referred object
	*/
	template<typename T>
	struct DontPropagateConst
	{
		typedef T Type;
	};


	/*!
	** \brief Propagate constness of pointed or referred object
	*/
	template<typename T>
	struct PropagateConst
	{
		typedef const T Type;
	};



} // namespace Constness
} // namespace Policy
} // namespace Yuni

#endif // __YUNI_TOOLBOX_POLICIES_CONSTNESS_H__
