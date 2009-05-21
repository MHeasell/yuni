#ifndef __YUNI_CORE_GETOPT_PARSER_HXX__
# define __YUNI_CORE_GETOPT_PARSER_HXX__

namespace Yuni
{
namespace Core
{
namespace GetOpt
{


	template<typename T>
	inline Option<T>*
	Parser::add(const char sOpt, const String& lOpt, const String& oComments, const bool ndValue,
		const T& defValue)
	{
		Option<T>* opt = new Option<T>(sOpt, lOpt, oComments, ndValue, defValue);
		this->add(opt);
		return opt;
	}



} // namespace GetOpt
} // namespace Core
} // namespace Yuni


#endif // __YUNI_CORE_GETOPT_PARSER_HXX__
