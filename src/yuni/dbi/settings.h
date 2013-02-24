#ifndef __YUNI_DBI_SETTINGS_H__
# define __YUNI_DBI_SETTINGS_H__

# include "../yuni.h"
# include "../core/string.h"


namespace Yuni
{
namespace DBI
{

	class Default
	{
	public:
		enum
		{
			maxReconnectionAttempts = 60,
			delayBetweenReconnection = 1000, // ms
			idleTime = 60 // seconds
		};
	};


	class Settings
	{
	public:
		//! Default constructor
		Settings();

		//! Clear all settings
		void clear();

	public:
		/*!
		** \brief Adapter name (or driver filename)
		**
		** Example : sqlite, postgresql, ...
		*/
		String adapter;
		//! host (empty means localhost)
		String host;
		//! username
		String username;
		//! password
		String password;
		//! Database name
		String database;
		//! schema to open (only if the database supports it)
		String schema;

		//! Maximum number of Attempts of reconnection before declaring the connexion dead (-1 infinite)
		uint maxReconnectionAttempts;
		//! Delay (in milliseconds) to wait before each attempt
		uint delayBetweenReconnectionAttempt;

		//! Minimum time (in seconds) to wait before closing an idle connection
		uint idleTime;

	}; // class Settings





} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_SETTINGS_H__
