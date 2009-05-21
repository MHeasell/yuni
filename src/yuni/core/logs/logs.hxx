#ifndef __YUNI_CORE_LOGS_LOGS_HXX__
# define __YUNI_CORE_LOGS_LOGS_HXX__

# include "../static/assert.h"


namespace Yuni
{
namespace Logs
{


	template<template<class> class TP, class Handler, class Decorator>
	Logger<TP,Handler,Decorator>::Logger()
		:pMaxLevel(Logger<TP,Handler,Decorator>::defaultVerbosityLevel)
	{}


	template<template<class> class TP, class Handler, class Decorator>
	Logger<TP,Handler,Decorator>::Logger(const Logger&)
	{
		YUNI_STATIC_ASSERT(false, ThisClassCannotBeCopied);
	}



	template<template<class> class TP, class Handler, class Decorator>
	Logger<TP,Handler,Decorator>::~Logger()
	{}



	template<template<class> class TP, class Handler, class Decorator>
	template<class VerbosityType>
	inline void
	Logger<TP,Handler,Decorator>::internalFlush(const String& s)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (VerbosityType::level <= pMaxLevel)
		{
			// Ask to all handlers to internalDecoratorWriteWL the message
			Handler:: template internalDecoratorWriteWL<Decorator,VerbosityType>(s);
		}
	}


	template<template<class> class TP, class Handler, class Decorator>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Notice, Verbosity::Notice::enabled>
	Logger<TP,Handler,Decorator>::notice()
	{
		return StreamWriter<Verbosity::Notice, Verbosity::Notice::enabled>(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Checkpoint, Verbosity::Checkpoint::enabled>
	Logger<TP,Handler,Decorator>::checkpoint()
	{
		return StreamWriter<Verbosity::Checkpoint, Verbosity::Checkpoint::enabled>(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Warning, Verbosity::Warning::enabled>
	Logger<TP,Handler,Decorator>::warning()
	{
		return StreamWriter<Verbosity::Warning, Verbosity::Warning::enabled>(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Error, Verbosity::Error::enabled>
	Logger<TP,Handler,Decorator>::error()
	{
		return StreamWriter<Verbosity::Error, Verbosity::Error::enabled>(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Fatal, Verbosity::Fatal::enabled>
	Logger<TP,Handler,Decorator>::fatal()
	{
		return StreamWriter<Verbosity::Fatal, Verbosity::Fatal::enabled>(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Debug, Verbosity::Debug::enabled>
	Logger<TP,Handler,Decorator>::debug()
	{
		return StreamWriter<Verbosity::Debug, Verbosity::Debug::enabled>(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	typename Logger<TP,Handler,Decorator>::template StreamWriter<Verbosity::Notice, Verbosity::Notice::enabled>
	Logger<TP,Handler,Decorator>::notice(const U& u)
	{
		return StreamWriter<Verbosity::Notice, Verbosity::Notice::enabled>(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Checkpoint, Verbosity::Checkpoint::enabled>
	Logger<TP,Handler,Decorator>::checkpoint(const U& u)
	{
		return StreamWriter<Verbosity::Checkpoint, Verbosity::Checkpoint::enabled>(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Warning, Verbosity::Warning::enabled>
	Logger<TP,Handler,Decorator>::warning(const U& u)
	{
		return StreamWriter<Verbosity::Warning, Verbosity::Warning::enabled>(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Error, Verbosity::Error::enabled>
	Logger<TP,Handler,Decorator>::error(const U& u)
	{
		return StreamWriter<Verbosity::Error, Verbosity::Error::enabled>(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Fatal, Verbosity::Fatal::enabled>
	Logger<TP,Handler,Decorator>::fatal(const U& u)
	{
		return StreamWriter<Verbosity::Fatal, Verbosity::Fatal::enabled>(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Debug, Verbosity::Debug::enabled>
	Logger<TP,Handler,Decorator>::debug(const U& u)
	{
		return StreamWriter<Verbosity::Debug, Verbosity::Debug::enabled>(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<class C>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<C, C::enabled>
	Logger<TP,Handler,Decorator>::custom()
	{
		return StreamWriter<C, C::enabled>(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	typename Logger<TP,Handler,Decorator>:: template StreamWriter<Verbosity::Unknown, Verbosity::Unknown::enabled>
	Logger<TP,Handler,Decorator>::operator << (const U& u)
	{
		return StreamWriter<Verbosity::Unknown, Verbosity::Unknown::enabled>(*this, u);
	}





} // namespace Logs
} // namespace Yuni


#endif // __YUNI_CORE_LOGS_LOGS_HXX__
