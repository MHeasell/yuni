#ifndef __YUNI_SYSTEM_WINDOWS_SLEEP_H__
# define __YUNI_SYSTEM_WINDOWS_SLEEP_H__

# include "../../yuni.h"


namespace Yuni
{

	/*!
	** \brief Suspend thread execution for an interval measured in seconds
	** \ingroup Toolbox
	**
	** \param seconds Number of seconds to wait
	**
	** \note You should consider that this method can not be interrupted.
	** You should not use this routine when using the thread facility provided
	** by the Yuni library and you should prefer the method `suspend()` instead.
	**
	** \see Yuni::Threads::AThread::suspend()
	*/
	void Sleep(const uint32 seconds);


	/*!
	** \brief Suspend thread execution for an interval measured in milliseconds
	** \ingroup Toolbox
	**
	** \param milliseconds NUmber of milliseconds to wait
	**
	** \note You should consider that this method can not be interrupted.
	** You should not use this routine when using the thread facility provided
	** by the Yuni library and you should prefer the method `suspend()` instead.
	*/
	void SleepMilliSeconds(const uint32 milliseconds);


} // namespace Yuni

#endif // __YUNI_SYSTEM_WINDOWS_SLEEP_H__
