
#include <yuni/yuni.h>
#include <yuni/core/logs.h>
#include <yuni/dbi/dbi.h>
#include <yuni/dbi/adapter/sqlite.h>

using namespace Yuni;

//! Logging facility
Logs::Logger<> logs;



static bool RunExample()
{
	// our connection pool
	DBI::ConnectorPool connector;

	// database location
	String filename = "dbi-example.db";

	auto error = connector.open(new DBI::Adapter::SQLite, filename);
	if (error)
	{
		logs.error() << "impossible to establish a connection to the database";
		return false;
	}

	// begin a new transaction
	auto tx = connector.begin();

	// create a new table if not already exists
	tx.perform("CREATE TABLE example IF NOT EXISTS (x INTEGER PRIMARY KEY);");

	// fill it with some values
	tx.perform("INSERT INTO example (x) VALUES (42), (3), (-1);");

	auto stmt = tx.prepare("SELECT * FROM example ORDER BY x");
	stmt.execute();

	// iterate through all values
	if (not stmt.each([&] ()
	{
		logs.info() << "row : x = " << 0;
	}))
	{
		logs.error() << "the result set is empty";
	}

	// commit changes
	if (DBI::errNone != (error = tx.commit()))
	{
		logs.error() << "commit failed";
		return false;
	}

	return true;
}



int main(int, char**)
{
	// Welcome !
	logs.notice() << "Yuni DBI Example";
	logs.info() << "using the SQLite default adapter";
	logs.info(); // empty line

	return RunExample() ? 0 : EXIT_FAILURE;
}

