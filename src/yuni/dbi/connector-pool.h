#ifndef __YUNI_DBI_CONNECTOR_H__
# define __YUNI_DBI_CONNECTOR_H__

# include "error.h"
# include "fwd.h"
# include "settings.h"



namespace Yuni
{
namespace DBI
{


	class ConnectorPool final
	{
	public:
		//! The most suitable smart pointer for the class
		typedef SmartPtr<ConnectorPool>  Ptr;

	public:
		//! \name Constructor & Destructor
		//@{
		//! Default constructor
		ConnectorPool();
		//! Destructor
		~ConnectorPool();
		//@}


		//! \name Channel
		//@{
		/*!
		** \brief Try to open a connection to a remote database
		**
		** A real connexion attempt to the database will be performed to check
		** input parameters. All connections will be automatically closed at the
		** destruction of the instance.
		*/
		Error open(const Settings& settings);

		/*!
		** \brief Close all connections to the remote database
		*/
		void close();
		//@}


		//! \name Transactions
		//@{
		/*!
		** \brief Start a new transaction
		*/
		Transaction begin();
		//@}


		//! \name Settings
		//@{
		//! Get a copy of the connector settings
		bool retrieveSettings(Settings& out) const;
		//@}


	private:
		//! Constructor from a private connector data
		ConnectorPool(const Yuni::Private::DBI::ConnectorDataPtr& data);

	private:
		//! Specific connector data
		Yuni::Private::DBI::ConnectorDataPtr pData;

		friend class Transaction;

	}; // class ConnectorPool





} // namespace DBI
} // namespace Yuni

# include "transaction.h"
# include "connector-pool.hxx"

#endif // __YUNI_DBI_CONNECTOR_H__
