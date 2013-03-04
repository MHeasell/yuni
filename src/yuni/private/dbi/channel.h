#ifndef __YUNI_PRIVATE_DBI_CHANNEL_H__
# define __YUNI_PRIVATE_DBI_CHANNEL_H__

# include "../../yuni.h"
# include "../../core/dictionary.h"
# include "../../datetime/timestamp.h"
# include "../../core/noncopyable.h"
# include "../../dbi/settings.h"
# include "../../dbi/error.h"
# include "../../dbi/adapter/entries.h"

# ifdef YUNI_OS_32
#	define YUNI_PRIVATE_DBI_ATOMIC_INT  32
# else
#	define YUNI_PRIVATE_DBI_ATOMIC_INT  64
# endif


namespace Yuni
{
namespace Private
{
namespace DBI
{

	/*!
	** \brief Single connection to a remote database
	*/
	class Channel final : private Yuni::NonCopyable<Channel>
	{
	public:
		//! The most suitable smart pointer
		typedef Yuni::SmartPtr<Channel> Ptr;
		//! Channel table, per thread-pseudo id
		typedef Dictionary<uint64, Ptr>::Hash  Table;


	public:
		//! \name Constructor & Destructor
		//@{
		Channel(const Yuni::DBI::Settings& settings, const ::yn_dbi_adapter& adapter);
		//! Destructor
		~Channel();
		//@}


		//! \name Transactions
		//@{
		//! Start a new transaction
		Yuni::DBI::Error begin(uint& handle);

		//! Try to commit the transaction
		Yuni::DBI::Error commit(uint handle);

		//! Rollback a transaction
		Yuni::DBI::Error rollback(uint handle);
		//@}


	public:
		//! Mutex, locked/released by transaction
		Yuni::Mutex mutex;
		//! Adapter
		::yn_dbi_adapter adapter;
		//! Database opaque pointer
		void* dbHandle;
		//! The total number of nested transactions
		uint nestedTransactionCount;
		//! Channel settings
		Yuni::DBI::Settings settings;

		//! Timestamp when the channel was last used
		Atomic::Int<YUNI_PRIVATE_DBI_ATOMIC_INT> lastUsed;

	}; // class Channel





} // namespace DBI
} // namespace Private
} // namespace Yuni

# include "channel.hxx"

#endif // __YUNI_PRIVATE_DBI_CHANNEL_H__
