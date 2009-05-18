#ifndef __YUNI_TOOLBOX_LOGS_DECORATORS_MESSAGE_H__
# define __YUNI_TOOLBOX_LOGS_DECORATORS_MESSAGE_H__

# include "../null.h"


namespace Yuni
{
namespace Logs
{


	template<class LeftType = NullDecorator>
	class Message : public LeftType
	{
	public:
		template<class Handler, class VerbosityType, class O>
		void internalDecoratorAddPrefix(O& out, const String& s)
		{
			// Write the message itself
			out.put(' ');

			// Color
			if (VerbosityType::checkpoint && Handler::unixColorsAllowed)
				out << "[1m"; // bold
			// The message
			out.write(s.c_str(), s.length());
			// Resetting the color
			if (VerbosityType::checkpoint && Handler::unixColorsAllowed)
				out << "[0m";

			// Transmit the message to the next handler
			LeftType:: template internalDecoratorAddPrefix<Handler, VerbosityType,O>(out, s);
		}

	}; // class VerbosityLevel





} // namespace Logs
} // namespace Yuni

#endif // __YUNI_TOOLBOX_LOGS_DECORATORS_MESSAGE_H__
