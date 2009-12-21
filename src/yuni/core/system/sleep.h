#ifndef __YUNI_CORE_SYSTEM_WINDOWS_SLEEP_H__
# define __YUNI_CORE_SYSTEM_WINDOWS_SLEEP_H__

# include "../../yuni.h"


namespace Yuni
{

	/*!
	** \brief Suspend thread execution for an interval measured in seconds
	** \ingroup Core
	**
	** \param seconds Number of seconds to wait
	**
	** \note You should consider that this method can not be interrupted.
	** You should not use this routine when using the thread facility provided
	** by the Yuni library and you should prefer the method `suspend()` instead.
	**
	** \see Yuni::Threads::AThread::suspend()
	*/
	void Sleep(const unsigned int seconds);


	/*!
	** \brief Suspend thread execution for an interval measured in milliseconds
	** \ingroup Core
	**
	** \param milliseconds NUmber of milliseconds to wait
	**
	** \note You should consider that this method can not be interrupted.
	** You should not use this routine when using the thread facility provided
	** by the Yuni library and you should prefer the method `suspend()` instead.
	*/
	void SleepMilliSeconds(const unsigned int milliseconds);



} // namespace Yuni

#endif // __YUNI_CORE_SYSTEM_WINDOWS_SLEEP_H__
