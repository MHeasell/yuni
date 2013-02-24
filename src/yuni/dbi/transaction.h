#ifndef __YUNI_DBI_TRANSACTION_H__
# define __YUNI_DBI_TRANSACTION_H__

# include <yuni/yuni.h>
# include <yuni/core/noncopyable.h>
# include "fwd.h"
# include "query.h"
# include "error.h"


namespace Yuni
{
namespace DBI
{

	/*!
	** \brief Transaction
	**
	** \code
	**	auto tx = dbconnexion.begin();
	**	tx.query("SELECT * FROM mytable").each([] (const DBI::Cursor& cursor)
	**	{
	**	});
	** \endcode
	*/
	class Transaction final
	{
	public:
		//! \name Constructors & Destructor
		//@{
		//! Destructor
		~Transaction();
		//@}


		//! \name Actions
		//@{
		/*!
		** \brief Try to commit the current transaction
		*/
		DBI::Error commit();

		/*!
		** \brief Rollback the transaction
		*/
		DBI::Error rollback();

		/*!
		** \brief re-start with a new transaction
		**
		** If a transaction was already taking place, it will be rolled back
		*/
		DBI::Error rebegin();
		//@}


		//! \name SQL queries
		//@{
		/*!
		** \brief Create a new query
		*/
		Query prepare(const AnyString& stmt);

		/*!
		** \brief Perform a query and discard the resultset
		*/
		DBI::Error perform(const AnyString& script);
		//@}


		//! \name Connector
		//@{
		//! Retrieve a connector from the current transaction
//		Connector connector() const;
		//@}


		//! \name Operators
		//@{
		//! operator (), equivalent to query()
		Query operator () (const AnyString& stmt);
		//@}


	protected:
		//! Default constructor
		Transaction(Yuni::Private::DBI::ConnectorDataPtr& data);
		//! Copy constructor
		Transaction(const Transaction&) YUNI_NORETURN;
		//! operator =
		Transaction& operator = (const Transaction&) YUNI_NORETURN;


	private:
		//! Communication channel with the remote database
		Yuni::Private::DBI::ChannelPtr pChannel;
		//! Transaction handle
		uint pTxHandle;

		friend class ConnectorPool;
	}; // class Transaction





} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_TRANSACTION_H__
