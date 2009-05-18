#ifndef __YUNI_TOOLBOX_LOGS_LOGS_H__
# define __YUNI_TOOLBOX_LOGS_LOGS_H__

# include "../../yuni.h"
# include "../policies/threading.h"

# include "null.h"
# include "verbosity.h"

// Default Handler
# include "handlers/stdcout.h"
// Default decorators
# include "decorators/verbositylevel.h"
# include "decorators/time.h"
# include "decorators/message.h"


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
	**
	**
	** \tparam TP The Threading Policy
	** \tapram Handler The first handler in the list
	** \tparam Decorator The first decorator in the list
	*/
	template<
		template<class> class TP = Policy::ObjectLevelLockable, // The Threading Policy
		class Handler = StdCout<>,
		class Decorator = Time< VerbosityLevel<Message<> > >    // Decorators
		>
	class Logger
		:public TP<Logger<TP,Handler,Decorator> >,   // inherits from the Threading Policy
		public Decorator,                    // inherits from all decorators
		public Handler                       // inherits from all handlers
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

	private:
		/*!
		** \brief The buffer for the message
		**
		** \internal This is an intermediate class that handles a temporary buffer where
		** the message can be built. The message will be really handled by the static list
		** of handlers when this class is destroyed. The method `internalFlush()` is called
		** , which ensures thread-safety (if required) while the message is passing through
		** the handlers.
		** \tparam V The verbosity level of the message
		** \tparam E A non-zero value if the message must be managed
		*/
		template<class V, int E> class StreamWriter;
		# include "stream.h"

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


		//! \name Messages
		//@{
		//! Start a `checkpoint` message
		StreamWriter<Verbosity::Checkpoint, Verbosity::Checkpoint::enabled> checkpoint();
		template<typename U> StreamWriter<Verbosity::Checkpoint, Verbosity::Checkpoint::enabled> checkpoint(const U& u);

		//! Start a notice message
		StreamWriter<Verbosity::Notice, Verbosity::Notice::enabled> notice();
		template<typename U> StreamWriter<Verbosity::Notice, Verbosity::Notice::enabled> notice(const U& u);

		//! Start a warning message
		StreamWriter<Verbosity::Warning, Verbosity::Warning::enabled> warning();
		template<typename U> StreamWriter<Verbosity::Warning, Verbosity::Warning::enabled> warning(const U& u);

		//! Start an error message
		StreamWriter<Verbosity::Error, Verbosity::Error::enabled> error();
		template<typename U> StreamWriter<Verbosity::Error, Verbosity::Error::enabled> error(const U& u);

		//! Start a fatal message
		StreamWriter<Verbosity::Fatal, Verbosity::Fatal::enabled> fatal();
		template<typename U> StreamWriter<Verbosity::Fatal, Verbosity::Fatal::enabled> fatal(const U& u);

		//! Start a debug message (disabled if NDEBUG defined)
		StreamWriter<Verbosity::Debug, Verbosity::Debug::enabled> debug();
		template<typename U> StreamWriter<Verbosity::Debug, Verbosity::Debug::enabled> debug(const U& u);


		//! Start a custom verbosity level message
		template<class C> StreamWriter<C,C::enabled> custom();

		//! Start a message with no verbosity level (always displayed)
		template<typename U> StreamWriter<Verbosity::Unknown, Verbosity::Unknown::enabled> operator << (const U& u);
		//@}

	private:
		/*!
		** \brief Transmit a message to all handlers
		*/
		template<class VerbosityType> void internalFlush(const String& s);

	private:
		//! The maximum verbosity level allowed
		int pMaxLevel;

		template<class, int> friend class StreamWriter;

	}; // class Logger




} // namespace Logs
} // namespace Yuni

# include "logs.hxx"

#endif // __YUNI_TOOLBOX_LOGS_LOGS_H__
