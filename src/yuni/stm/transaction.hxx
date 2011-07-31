#ifndef __YUNI_STM_TRANSACTION_HXX__
# define __YUNI_STM_TRANSACTION_HXX__


namespace Yuni
{
namespace STM
{
namespace Transaction
{


	template<class ReadOnlyT>
	inline ITransaction<ReadOnlyT>::ITransaction() :
		pState(stIdle)
	{
	}


	template<class ReadOnlyT>
	inline ITransaction<ReadOnlyT>::~ITransaction()
	{
		assert(pState != stActive && "invalid transaction state");
	}


	template<class ReadOnlyT>
	void ITransaction<ReadOnlyT>::begin()
	{
		assert(pState != stActive && "invalid transaction state");

		//! New transaction state
		pState = stActive;
	}


	template<class ReadOnlyT>
	bool ITransaction<ReadOnlyT>::commit()
	{
		assert(pState == stActive && "invalid transaction state");
		if (readonly)
		{
			pState = stIdle;
			return true;
		}
		else
		{
			return false;
		}
	}


	template<class ReadOnlyT>
	inline void ITransaction<ReadOnlyT>::rollback()
	{
		assert(pState != stActive && "invalid transaction state");
		pState = stAborted;
	}




} // namespace Transaction
} // namespace STM
} // namespace Yuni

#endif // __YUNI_STM_TRANSACTION_HXX__
