#ifndef __YUNI_TOOLBOX_GETOPT_CONVERTIONS_H__
# define __YUNI_TOOLBOX_GETOPT_CONVERTIONS_H__

# include "../string.h"


namespace Yuni
{
namespace Toolbox
{
namespace GetOpt
{

	/*!
	** \brief Converter for GetOpt options
	**
	** This class is used to convert an input (string) to the appropriate
	** type of the option.
	** The namespace GetOpt already provides standard convertions for basic
	** types (int, string...).
	*/
	template<typename T>
	class DefaultConverterTo
	{
	public:
		static const T FromString(const String& s) {return s.to<T>();}
	};





} // namespace GetOpt
} // namespace Toolbox
} // namespace Yuni

#endif // __YUNI_TOOLBOX_GETOPT_CONVERTIONS_H__
