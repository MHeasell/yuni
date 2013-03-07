#ifndef __YUNI_DBI_ADAPTER_ENTRIES_H__
# define __YUNI_DBI_ADAPTER_ENTRIES_H__

# include "../../yuni.h"
# include "../error.h"


/*!
** \brief Adapter entries table
**
** \note All routines must be reentrant
*/
struct yn_dbi_adapter
{
	//! Database handle, provided for convenient uses
	void* dbh;

	//! Start a new transaction
	yn_dbierr (*begin)(void* dbh);
	//! Commit the current transaction
	yn_dbierr (*commit)(void* dbh);
	//! Create a new savepoint in the current transaction
	yn_dbierr (*savepoint)(void* dbh, const char* name, uint length);
	//! Rollback the current transaction
	yn_dbierr (*rollback)(void* dbh);
	//! Rollback a savepoint
	yn_dbierr (*rollback_savepoint)(void* dbh, const char* name, uint length);

	//! Start a new query (and acquire it)
	yn_dbierr (*query_new)(void** qh, void* dbh, const char* stmt, uint length);
	//! Acquire a query pointer
	void (*query_ref_acquire)(void* qh);
	//! Release a query
	void (*query_ref_release)(void* qh);
	//! Bind a string
	yn_dbierr (*bind_str)(void* qh, int index, const char* str, uint length);
	//! Bind a bool
	yn_dbierr (*bind_bool)(void* qh, int index, int value);
	//! Bind a sint32
	yn_dbierr (*bind_int32)(void* qh, int index, yint32 value);
	//! Bind a sint64
	yn_dbierr (*bind_int64)(void* qh, int index, yint64 value);
	//! Bind a double
	yn_dbierr (*bind_double)(void* qh, int index, double value);
	//! Bind a null value
	yn_dbierr (*bind_null)(void* qh, int index);

	//! Execute a query
	yn_dbierr (*query_execute)(void* qh, yuint64* rowcount);
	//! Execute a query, and release the handler
	yn_dbierr (*query_perform)(void* qh);

	//! Go to the next row
	yn_dbierr (*cursor_go_to_next)(void* qh);
	//! Go to the previous row
	yn_dbierr (*cursor_go_to_previous)(void* qh);
	//! Go to the first row
	yn_dbierr (*cursor_go_to_first)(void* qh);
	//! Go to the last row
	yn_dbierr (*cursor_go_to_last)(void* qh);
	//! Go to a specific row
	yn_dbierr (*cursor_go_to)(void* qh, yuint64 rowindex);

	//! garbage-collect and optionally analyze a database
	yn_dbierr (*vacuum)();
	//! truncate a table
	yn_dbierr (*truncate)(const char* tablename, uint length);

	//! Open a connection to the remote database
	yn_dbierr (*open) (void** dbh, const char* host, uint port, const char* user, const char* pass, const char* dbname);
	//! Open a schema
	yn_dbierr (*open_schema) (void* dbh, const char* name, uint length);
	//! Close the connection
	void (*close) (void* dbh);

}; // class Adapter




#endif /* __YUNI_DBI_ADAPTER_ENTRIES_H__ */
