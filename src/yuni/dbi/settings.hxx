#ifndef __YUNI_DBI_SETTINGS_HXX__
# define __YUNI_DBI_SETTINGS_HXX__


namespace Yuni
{
namespace DBI
{

	inline Settings::Settings() :
		reconnectionAttemps(Default::maxReconnectionAttempt),
		delayBetweenReconnectionAttempt(Default::delayBetweenReconnection),
		idleTime(Default::idleTime)
	{}


	inline void Settings::clear()
	{
		host.clear();
		username.clear();
		password.clear();
		database.clear();
		schema.clear();

		maxReconnectionAttempts = Default::maxReconnectionAttempts;
		delayBetweenReconnectionAttempt = Default::delayBetweenReconnextion;
		idleTime = Default::idleTime;
	}





} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_SETTINGS_H__
