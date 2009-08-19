#ifndef __YUNI_CORE_LOGS_LOGS_HXX__
# define __YUNI_CORE_LOGS_LOGS_HXX__


namespace Yuni
{
namespace Logs
{


	template<template<class> class TP, class Handler, class Decorator>
	inline Logger<TP,Handler,Decorator>::Logger()
		:pMaxLevel(Logger<TP,Handler,Decorator>::defaultVerbosityLevel)
	{}


	template<template<class> class TP, class Handler, class Decorator>
	inline Logger<TP,Handler,Decorator>::Logger(const Logger&)
	{
		YUNI_STATIC_ASSERT(false, ThisClassCannotBeCopied);
	}



	template<template<class> class TP, class Handler, class Decorator>
	inline Logger<TP,Handler,Decorator>::~Logger()
	{}



	template<template<class> class TP, class Handler, class Decorator>
	template<class VerbosityType>
	void
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
	inline typename Logger<TP,Handler,Decorator>::NoticeWriter
	Logger<TP,Handler,Decorator>::notice()
	{
		return NoticeWriter(*this);
	}

	template<template<class> class TP, class Handler, class Decorator>
	inline typename Logger<TP,Handler,Decorator>::InfoWriter
	Logger<TP,Handler,Decorator>::info()
	{
		return InfoWriter(*this);
	}



	template<template<class> class TP, class Handler, class Decorator>
	inline typename Logger<TP,Handler,Decorator>::CheckpointWriter
	Logger<TP,Handler,Decorator>::checkpoint()
	{
		return typename Logger<TP,Handler,Decorator>::CheckpointWriter(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	inline typename Logger<TP,Handler,Decorator>::WarningWriter
	Logger<TP,Handler,Decorator>::warning()
	{
		return WarningWriter(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	inline typename Logger<TP,Handler,Decorator>::ErrorWriter
	Logger<TP,Handler,Decorator>::error()
	{
		return ErrorWriter(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	inline typename Logger<TP,Handler,Decorator>::FatalWriter
	Logger<TP,Handler,Decorator>::fatal()
	{
		return FatalWriter(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	inline typename Logger<TP,Handler,Decorator>::DebugWriter
	Logger<TP,Handler,Decorator>::debug()
	{
		return DebugWriter(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	inline typename Logger<TP,Handler,Decorator>::NoticeWriter
	Logger<TP,Handler,Decorator>::notice(const U& u)
	{
		return NoticeWriter(*this, u);
	}

	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	inline typename Logger<TP,Handler,Decorator>::InfoWriter
	Logger<TP,Handler,Decorator>::info(const U& u)
	{
		return InfoWriter(*this, u);
	}



	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	inline typename Logger<TP,Handler,Decorator>::CheckpointWriter
	Logger<TP,Handler,Decorator>::checkpoint(const U& u)
	{
		return CheckpointWriter(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	inline typename Logger<TP,Handler,Decorator>::WarningWriter
	Logger<TP,Handler,Decorator>::warning(const U& u)
	{
		return WarningWriter(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	inline typename Logger<TP,Handler,Decorator>::ErrorWriter
	Logger<TP,Handler,Decorator>::error(const U& u)
	{
		return ErrorWriter(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	inline typename Logger<TP,Handler,Decorator>::FatalWriter
	Logger<TP,Handler,Decorator>::fatal(const U& u)
	{
		return FatalWriter(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	inline typename Logger<TP,Handler,Decorator>::DebugWriter
	Logger<TP,Handler,Decorator>::debug(const U& u)
	{
		return DebugWriter(*this, u);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<class C>
	inline Private::LogImpl::Writer<Logger<TP,Handler,Decorator>, C, C::enabled>
	Logger<TP,Handler,Decorator>::custom()
	{
		return Private::LogImpl::Writer<LoggerType, C, C::enabled>(*this);
	}


	template<template<class> class TP, class Handler, class Decorator>
	template<typename U>
	inline typename Logger<TP,Handler,Decorator>::UnknownWriter
	Logger<TP,Handler,Decorator>::operator << (const U& u)
	{
		return UnknownWriter(*this, u);
	}





} // namespace Logs
} // namespace Yuni


#endif // __YUNI_CORE_LOGS_LOGS_HXX__
