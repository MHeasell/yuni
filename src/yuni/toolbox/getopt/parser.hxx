#ifndef __YUNI_TOOLBOX_GETOPT_PARSER_HXX__
# define __YUNI_TOOLBOX_GETOPT_PARSER_HXX__

namespace Yuni
{
namespace ToolBox
{
namespace GetOpt
{


	template<typename T, class ConvTO>
	Option<T, ConvTO>* Parser::add(const char sOpt,
		const String& lOpt, const String& oComments, const bool ndValue,
		const T& defValue)
	{
		typedef Option<T, ConvTO> NewOption;
		NewOption* opt = new NewOption(sOpt, lOpt, oComments, ndValue, defValue);
		this->add(opt);
		return opt;
	}



} // namespace GetOpt
} // namespace ToolBox
} // namespace Yuni


#endif // __YUNI_TOOLBOX_GETOPT_PARSER_HXX__
