#ifndef __YUNI_DBI_ADAPTER_H__
# define __YUNI_DBI_ADAPTER_H__

# include "../yuni.h"
# include "error.h"


struct yn_dbi_adapter
{
	//! Open a connection to the remote database
	yn_dbierr (*open) (void** dbh, const char* host, const char* user, const char* pass, const char* dbname);
	//! Open a schema
	yn_dbierr (*open_schema) (void* dbh, const char* name, uint length);
	//! Close the connection
	void (*close) (void* dbh);

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

	//! Start a new query
	yn_dbierr (*query_new)(void** qh, void* dbh, const char* stmt, uint length);
	//! Release a query
	yn_dbierr (*query_free)(void* qh);
	//! Bind a string
	yn_dbierr (*bind_str)(void* qh, int index, const char* str, uint length);
	//! Execute a query
	yn_dbierr (*query_exec)(void* qh);

}; // class Adapter




#endif /* __YUNI_DBI_ADAPTER_H__ */
