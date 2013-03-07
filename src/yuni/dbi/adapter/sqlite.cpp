
#include "../adapter/sqlite.h"
#include "../../private/dbi/adapter/sqlite/sqlite3.h"
#include <cassert>


namespace Yuni
{
namespace DBI
{
namespace Adapter
{

	static yn_dbierr ynsqlite_open(void** dbh, const char* host, uint /*port*/, const char* /*user*/, const char* /*pass*/, const char* /*dbname*/)
	{
		assert(NULL != dbh);

		enum
		{
			flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_SHAREDCACHE | SQLITE_OPEN_URI,
		};
		::sqlite3* handle = nullptr;

		int error = ::sqlite3_open_v2(host, &handle, flags, nullptr);
		if (SQLITE_OK != error)
		{
			*dbh = nullptr;
			switch (error)
			{
				case SQLITE_PERM:
				case SQLITE_READONLY:
				case SQLITE_CORRUPT:
					break;
			}
			return yerr_dbi_connection_failed;
		}

		*dbh = handle;
		return yerr_dbi_none;
	}


	static void ynsqlite_close(void* dbh)
	{
		if (dbh)
			::sqlite3_close_v2((::sqlite3*) dbh);
	}


	void SQLite::retrieveEntries(::yn_dbi_adapter& entries)
	{
		entries.open  = ynsqlite_open;
		entries.close = ynsqlite_close;
	}




} // namespace Adapter
} // namespace DBI
} // namespace Yuni

