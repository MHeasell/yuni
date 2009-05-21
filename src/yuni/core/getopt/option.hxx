#ifndef __GETOPT_HXX__
# define __GETOPT_HXX__

namespace Yuni
{
namespace Core
{
namespace GetOpt
{


	template<typename T>
	Option<T>::Option(const char sOpt, const String& lOpt,
		const String& oComments, const bool ndValue, const T& defValue)
	/**/
		:AOption(sOpt, lOpt, ndValue, oComments),
		pDefaultValue(defValue), pValues()
	{}

	template<typename T>
	Option<T>::Option(const Option<T>& c)
		:AOption(c),
		pDefaultValue(c.pDefaultValue), pValues(c.pValues)
	{}


	template<typename T>
	Option<T>::~Option()
	{}


	template<typename T>
	inline T Option<T>::value() const
	{
		return pValues.empty() ? pDefaultValue : pValues.back();
	}

	template<typename T>
	inline T Option<T>::operator() () const
	{
		return pValues.empty() ? pDefaultValue : pValues.back();
	}

	template<typename T>
	inline void Option<T>::addValue(const String& v)
	{
		this->pModified = true;
		if (v.notEmpty() && this->pNeedValue)
			this->pValues.push_back(v.to<T>());
	}


	template<typename T>
	inline void Option<T>::reset()
	{
		AOption::reset();
		pValues.clear();
	}


} // namespace GetOpt
} // namespace Core
} // namespace GetOpt




#endif // __GETOPT_HXX__
