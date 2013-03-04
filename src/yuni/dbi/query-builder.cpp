
#include "query-builder.h"
#include <cassert>


namespace Yuni
{
namespace DBI
{

	QueryBuilder::QueryBuilder(::yn_dbi_adapter& adapter, const AnyString& stmt) :
		pAdapter(adapter),
		pRowCount()
	{
		if (not stmt.empty() and pAdapter.dbh)
		{
			assert(pAdapter.query_new != NULL  and "invalid adapter query_new");
			assert(pAdapter.query_ref_acquire != NULL and "invalid adapter query_ref_acquire");
			assert(pAdapter.query_ref_release != NULL and "invalid adapter query_ref_release");

			pAdapter.query_new(&pHandle, pAdapter.dbh, stmt.c_str(), stmt.size());
			return;
		}

		// failed
		pHandle = nullptr;
	}


	DBI::Error QueryBuilder::execute()
	{
		if (pHandle)
			return (DBI::Error) pAdapter.query_execute(pHandle, &pRowCount);

		pRowCount = 0;
		return DBI::errNoTransaction;
	}


	DBI::Error QueryBuilder::perform()
	{
		if (pHandle)
		{
			DBI::Error error = (DBI::Error) pAdapter.query_execute(pHandle, nullptr);
			pAdapter.query_ref_release(pHandle);
			pHandle = nullptr;
			pRowCount = 0;
			return error;
		}
		pRowCount = 0;
		return errNoTransaction;
	}





} // namespace DBI
} // namespace Yuni
