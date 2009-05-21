#ifndef __YUNI_CORE_DECORATORS_LOGS_TIME_H__
# define __YUNI_CORE_DECORATORS_LOGS_TIME_H__

# include "../null.h"
# include <time.h>


namespace Yuni
{
namespace Logs
{



	template<class LeftType = NullDecorator>
	class Time : public LeftType
	{
	public:
		template<class Handler, class VerbosityType, class O>
		void internalDecoratorAddPrefix(O& out, const String& s)
		{
			// Write the verbosity to the output
			time_t rawtime;
			char asc[26];
			time (&rawtime);

			# ifdef YUNI_OS_WINDOWS
			struct tm timeinfo;
			localtime_s(&timeinfo, &rawtime);
			asctime_s(asc, &timeinfo);
			# else
			struct tm timeinfo;
			localtime_r(&rawtime, &timeinfo);
			asctime_r(&timeinfo, asc);
			# endif
			out.put('[');
			out.write(asc, 23);
			out.put(']');

			// Transmit the message to the next decorator
			LeftType:: template internalDecoratorAddPrefix<Handler, VerbosityType,O>(out, s);
		}

	}; // class Time




} // namespace Logs
} // namespace Yuni

#endif // __YUNI_CORE_DECORATORS_LOGS_TIME_H__
