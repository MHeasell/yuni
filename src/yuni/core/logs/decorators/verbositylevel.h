#ifndef __YUNI_CORE_LOGS_DECORATORS_VERBOSITY_LEVEL_H__
# define __YUNI_CORE_LOGS_DECORATORS_VERBOSITY_LEVEL_H__

# include "../null.h"


namespace Yuni
{
namespace Logs
{


	template<class LeftType = NullDecorator>
	class VerbosityLevel : public LeftType
	{
	public:
		template<class Handler, class VerbosityType, class O>
		void internalDecoratorAddPrefix(O& out, const String& s)
		{
			// Write the verbosity to the output
			if (VerbosityType::hasName)
			{
				// Unix Color
				if (Handler::unixColorsAllowed)
					VerbosityType::AppendUnixColor(out);
				// The verbosity
				out.put('[');
				VerbosityType::AppendName(out);
				out.put(']');
				// Resetting the color
				if (Handler::unixColorsAllowed)
					out << "[0m";
			}
			// Transmit the message to the next decorator
			LeftType:: template internalDecoratorAddPrefix<Handler, VerbosityType,O>(out, s);
		}

	}; // class VerbosityLevel





} // namespace Logs
} // namespace Yuni

#endif // __YUNI_CORE_LOGS_DECORATORS_VERBOSITY_LEVEL_H__
