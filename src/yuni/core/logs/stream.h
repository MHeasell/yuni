#ifndef __YUNI_CORE_LOGS_STREAM_H__
# define __YUNI_CORE_LOGS_STREAM_H__


namespace Yuni
{
namespace Private
{
namespace LogImpl
{

	/*!
	** \brief The buffer for the message
	**
	** \internal This is an intermediate class that handles a temporary buffer where
	** the message can be built. The message will be really handled by the static list
	** of handlers when this class is destroyed. The method `internalFlush()` is called
	** , which ensures thread-safety (if required) while the message is passing through
	** the handlers.
	**
	** \tparam V The verbosity level of the message
	** \tparam E A non-zero value if the message must be managed
	*/
	template<class LogT, class V, int E>
	class Writer
	{
	public:
		//! Type of the calling logger
		typedef LogT LoggerType;

	public:
		//! \name Constructos & Destructor
		//@{
		inline Writer(LoggerType& l)
			:pLogger(l)
		{}

		template<typename U>
		inline Writer(LoggerType& l, U u)
			:pLogger(l)
		{
			pBuffer.append(u);
		}

		~Writer()
		{
			pLogger.template internalFlush<V>(pBuffer);
		}
		//@}

		template<typename U> Writer& operator << (const U& u)
		{
			pBuffer.append(u);
			return *this;
		}

	private:
		//! Reference to the original logger
		LoggerType& pLogger;
		//! Buffer that contains the message
		String pBuffer;

	}; // class Writer




	// Specialization when a verbosty level is disabled
	template<class LogT, class V>
	class Writer<LogT,V,0>
	{
	public:
		//! Type of the calling logger
		typedef LogT LoggerType;

	public:
		Writer(LoggerType&)
		{}
		template<typename U>
		Writer(LoggerType&, U)
		{}

		~Writer()
		{}

		template<typename U> Writer& operator << (const U&)
		{
			// Do nothing - Disabled
			return *this;
		}

	}; // class Writer


} // namespace LogImpl
} // namespace Private
} // namespace Yuni

#endif // __YUNI_CORE_LOGS_STREAM_H__
