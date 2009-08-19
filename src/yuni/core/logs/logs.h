#ifndef __YUNI_CORE_LOGS_LOGS_H__
# define __YUNI_CORE_LOGS_LOGS_H__

# include "../../yuni.h"
# include "../../threads/policy.h"

# include "null.h"
# include "verbosity.h"

// Default Handler
# include "handlers/stdcout.h"
// Default decorators
# include "decorators/verbositylevel.h"
# include "decorators/time.h"
# include "decorators/message.h"
# include "../static/assert.h"
# include "stream.h"


# ifdef NDEBUG
#	define YUNI_LOGS_DEFAULT_VERBOSITY  Verbosity::Notice::level
# else
#	define YUNI_LOGS_DEFAULT_VERBOSITY  Verbosity::Debug::level
# endif



namespace Yuni
{
namespace Logs
{


	/*!
	** \brief A customizable log facility
	**
	** A simple hello world :
	** \code
	** #include <yuni/core/logs.h>
	**
	** int main()
	** {
	** 		// The logger
	** 		Yuni::Logs::Logger<>  logs;
	** 		// Hello world !
	** 		logs.notice() << "Hello world !";
	** 	return 0;
	** }
	** \endcode
	**
	** This class uses a static decorator pattern to modify its behavior. By default,
	** the output has the following format :
	** \code
	** [date][color][verbosity level][/color] <msg>
	** \endcode
	** The color is only available on Unixes.
	**
	**
	** \tparam TP The Threading Policy
	** \tapram Handler The first handler in the list
	** \tparam Decorator The first decorator in the list
	*/
	template<
		template<class> class TP = Policy::ObjectLevelLockable, // The Threading Policy
		class Handler = StdCout<>,
		class Decorator = Time< VerbosityLevel<Message<> > >
		>
	class Logger
		:public TP<Logger<TP,Handler,Decorator> >,  // inherits from the Threading Policy
		public Decorator,                           // inherits from all decorators
		public Handler                              // inherits from all handlers
	{
	public:
		//! The full prototype of the logger
		typedef Logger<TP, Handler, Decorator>  LoggerType;
		//! The Threading Policy
		typedef TP<LoggerType>  ThreadingPolicy;

		/*!
		** \brief Settings for the logger
		*/
		enum Settings
		{
			//! The default verbose level
			defaultVerbosityLevel = YUNI_LOGS_DEFAULT_VERBOSITY,
		};

	public:
		// Aliases (for code clarity)
		//! Alias for the CheckpointWriter
		typedef Private::LogImpl::Writer<LoggerType, Verbosity::Checkpoint, Verbosity::Checkpoint::enabled> CheckpointWriter;
		//! Alias for the NoticeWriter
		typedef Private::LogImpl::Writer<LoggerType, Verbosity::Notice, Verbosity::Notice::enabled> NoticeWriter;
		//! Alias for the NoticeWriter
		typedef Private::LogImpl::Writer<LoggerType, Verbosity::Info, Verbosity::Info::enabled> InfoWriter;
		//! Alias for the WarningWriter
		typedef Private::LogImpl::Writer<LoggerType, Verbosity::Warning, Verbosity::Warning::enabled> WarningWriter;
		//! Alias for the ErrorWriter
		typedef Private::LogImpl::Writer<LoggerType, Verbosity::Error, Verbosity::Error::enabled> ErrorWriter;
		//! Alias for the FatalWriter
		typedef Private::LogImpl::Writer<LoggerType, Verbosity::Fatal, Verbosity::Fatal::enabled> FatalWriter;
		//! Alias for the DebugWriter
		typedef Private::LogImpl::Writer<LoggerType, Verbosity::Debug, Verbosity::Debug::enabled> DebugWriter;
		//! Alias for the UnknownWriter
		typedef Private::LogImpl::Writer<LoggerType, Verbosity::Unknown, Verbosity::Unknown::enabled> UnknownWriter;

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		Logger();
		/*!
		** \brief Copy constructor
		*/
		Logger(const Logger& rhs);
		/*!
		** \brief Destructor
		*/
		~Logger();
		//@}


		//! \name Checkpoint
		//@{
		CheckpointWriter checkpoint();
		template<typename U> CheckpointWriter checkpoint(const U& u);
		//@}

		//! \name Notice
		//@{
		NoticeWriter notice();
		template<typename U> NoticeWriter notice(const U& u);
		//@}

		//! \name Info
		//@{
		InfoWriter info();
		template<typename U> InfoWriter info(const U& u);
		//@}

		//! \name Warning
		//@{
		WarningWriter warning();
		template<typename U> WarningWriter warning(const U& u);
		//@}

		//! \name Error
		//@{
		ErrorWriter error();
		template<typename U> ErrorWriter error(const U& u);
		//@}

		//! \name Fatal
		//@{
		FatalWriter fatal();
		template<typename U> FatalWriter fatal(const U& u);
		//@}

		//! \name Debug (disabled if NDEBUG defined)
		//@{
		DebugWriter debug();
		template<typename U> DebugWriter debug(const U& u);
		//@}


		//! Start a custom verbosity level message
		template<class C> Private::LogImpl::Writer<LoggerType,C,C::enabled> custom();

		//! Start a message with no verbosity level (always displayed)
		template<typename U> UnknownWriter operator << (const U& u);
		//@}

	private:
		/*!
		** \brief Transmit a message to all handlers
		*/
		template<class VerbosityType> void internalFlush(const String& s);

	private:
		//! The maximum verbosity level allowed
		int pMaxLevel;

		// A friend !
		template<class, class, int> friend class Private::LogImpl::Writer;

	}; // class Logger




} // namespace Logs
} // namespace Yuni

# include "logs.hxx"

#endif // __YUNI_CORE_LOGS_LOGS_H__
