#ifndef __YUNI_CORE_DECORATORS_LOGS_TIME_H__
# define __YUNI_CORE_DECORATORS_LOGS_TIME_H__

# include "../null.h"


namespace Yuni
{
namespace Private
{
namespace LogsDecorator
{

    # if defined(YUNI_OS_MINGW)
	char* WriteCurrentTimestampToBufferMinGW(void);
    # else
	void WriteCurrentTimestampToBuffer(char* buffer);
    # endif

} // namespace LogsDecorator
} // namespace Private
} // namespace Yuni




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
            # ifndef YUNI_OS_MINGW
			char asc[26];
			Private::LogsDecorator::WriteCurrentTimestampToBuffer(asc);
            # endif

			out.put('[');
            # ifndef YUNI_OS_MINGW
			out.write(asc, 23);
            # else
			out += Private::LogsDecorator::WriteCurrentTimestampToBufferMinGW();
            # endif
			out.put(']');

			// Transmit the message to the next decorator
			LeftType:: template internalDecoratorAddPrefix<Handler, VerbosityType,O>(out, s);
		}

	}; // class Time




} // namespace Logs
} // namespace Yuni

#endif // __YUNI_CORE_DECORATORS_LOGS_TIME_H__
