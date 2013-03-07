
#include "query-builder.h"
#include <cassert>


namespace Yuni
{
namespace DBI
{


	DBI::Error PreparedStatement::execute()
	{
		if (pHandle)
		{
			assert(pAdapter.query_execute and "invalid query_perform");
			return (DBI::Error) pAdapter.query_execute(pHandle, &pRowCount);
		}

		pRowCount = 0;
		return DBI::errNoTransaction;
	}


	DBI::Error PreparedStatement::perform()
	{
		// reset the total number of rows
		pRowCount = 0;

		if (pHandle)
		{
			assert(pAdapter.query_perform and "invalid query_perform");

			// execute the query
			DBI::Error error = (DBI::Error) pAdapter.query_perform(pHandle);
			pHandle = nullptr;
			return error;
		}
		return errNoQuery;
	}





} // namespace DBI
} // namespace Yuni
