#ifndef __YUNI_DBI_ERROR_H__
# define __YUNI_DBI_ERROR_H__


// yn_dbi_error and Yuni::DBI::Error must match


extern "C" enum yn_dbierr
{
	//! No error
	yerr_dbi_none,
	//! The database connection was lost, even after automatic reconnection
	yerr_dbi_connection_failed,
	//! No transaction
	yerr_dbi_no_transaction,
	//! Invalid nested transaction,
	yerr_dbi_invalid_nested_transaction,
	//! Invalid identifier
	yerr_dbi_invalid_identifier,
	//! No row
	yerr_dbi_no_row,
};


# ifdef __cplusplus

namespace Yuni
{
namespace DBI
{

	enum Error
	{
		//! No error
		errNone,
		//! The database connection was lost, even after automatic reconnection
		errConnectionFailed,
		//! No transaction
		errNoTransaction,
		//! Invalid nested transaction,
		errInvalidNestedTransaction,
		//! Invalid identifier
		errInvalidIdentifier,
		//! No row
		errNoRow,
	};



} // namespace DBI
} // namespace Yuni

# endif // __cplusplus

#endif /* __YUNI_DBI_ERROR_H__ */
