#ifndef __YUNI_POLICIES_CONVERSIONS_H__
# define __YUNI_POLICIES_CONVERSIONS_H__



namespace Yuni
{
namespace Policy
{
namespace Conversion
{

	/*!
	** \defgroup ConversionPolicies Conversion policies
	** \ingroup Policies
	*/


	/*! \class Allow
	** \ingroup ConversionPolicies
	*/
	struct Allow
	{
		enum { allow = true };
	};


	/*! \class Disallow
	** \ingroup ConversionPolicies
	*/
	struct Disallow
	{
		//! Default constructor
		Disallow() {}
		/*!
		** \brief Copy constructor
		**
		** It is possible to initialize a `Disallow` policy with an `Allow` policy 
		*/
		Disallow(const Allow&) {}

		enum { allow = false };
	};


} // namespace Conversion
} // namespace Policy
} // namespace Yuni

#endif // __YUNI_POLICIES_CONVERSIONS_H__
