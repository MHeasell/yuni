#ifndef __GETOPT_HXX__
# define __GETOPT_HXX__

namespace Yuni
{
namespace ToolBox
{
namespace GetOpt
{


	template<typename T, class ConvTO>
	Option<T, ConvTO>::Option(const char sOpt, const String& lOpt,
		const String& oComments, const bool ndValue, const T& defValue)
	/**/
		:AOption(sOpt, lOpt, ndValue, oComments),
		pDefaultValue(defValue), pValues()
	{}

	template<typename T, class ConvTO>
	Option<T, ConvTO>::Option(const Option<T, ConvTO>& c)
		:AOption(c),
		pDefaultValue(c.pDefaultValue), pValues(c.pValues)
	{}


	template<typename T, class ConvTO>
	Option<T, ConvTO>::~Option()
	{}
	

	template<typename T, class ConvTO>
	inline T Option<T, ConvTO>::value() const
	{
		return pValues.empty() ? pDefaultValue : pValues.back();
	}
	
	template<typename T, class ConvTO>
	inline T Option<T, ConvTO>::operator() () const
	{
		return pValues.empty() ? pDefaultValue : pValues.back();
	}

	template<typename T, class ConvTO>
	inline void Option<T, ConvTO>::addValue(const String& v)
	{
		this->pModified = true;
		if (!v.empty() && this->pNeedValue)
			this->pValues.push_back(ConvTO::FromString(v));
	}
	
	
	template<typename T, class ConvTO>
	inline void Option<T, ConvTO>::reset()
	{
		AOption::reset();
		pValues.clear();
	}


} // namespace GetOpt
} // namespace ToolBox
} // namespace GetOpt




#endif // __GETOPT_HXX__
