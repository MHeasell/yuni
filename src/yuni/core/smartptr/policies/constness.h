#ifndef __YUNI_CORE_SMARTPTR_POLICIES_CONSTNESS_H__
# define __YUNI_CORE_SMARTPTR_POLICIES_CONSTNESS_H__


namespace Yuni
{
namespace Policy
{

/*!
** \brief Constness policies
** \ingroup Policies
*/
namespace Constness
{


	/*!
	** \brief Don't Propagate constness of pointed or referred object
	** \ingroup Policies
	*/
	template<typename T>
	struct DontPropagateConst final
	{
		typedef T Type;
	};


	/*!
	** \brief Propagate constness of pointed or referred object
	** \ingroup Policies
	*/
	template<typename T>
	struct PropagateConst final
	{
		typedef const T Type;
	};



} // namespace Constness
} // namespace Policy
} // namespace Yuni

#endif // __YUNI_CORE_SMARTPTR_POLICIES_CONSTNESS_H__
