#ifndef __YUNI_STM_TRANSACTION_H__
# define __YUNI_STM_TRANSACTION_H__

# include "../yuni.h"
# include "fwd.h"
# include <cassert>


namespace Yuni
{
namespace STM
{
namespace Transaction
{


	/*!
	** \brief Transaction (abtract)
	*/
	template<class ReadOnlyT>
	class ITransaction
	{
	public:
		enum
		{
			//! Readonly mode
			readonly = (ReadOnlyT ? 1 : 0),
		};

		//! Transaction state
		enum State
		{
			//! The transaction is idle
			stIdle,
			//! The transaction is active
			stActive,
			//! The transaction has been aborted
			stAborted,
		};

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		ITransaction();
		//! Destructor
		~ITransaction();
		//@}

		void begin();

		bool commit();

		void rollback();


	private:
		//! Transaction state
		State pState;

	}; // class ITransaction<ReadOnlyT>





} // namespace Transaction
} // namespace STM
} // namespace Yuni

# include "transaction.hxx"

#endif // __YUNI_STM_TRANSACTION_H__
