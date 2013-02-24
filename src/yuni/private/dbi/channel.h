#ifndef __YUNI_PRIVATE_DBI_CHANNEL_H__
# define __YUNI_PRIVATE_DBI_CHANNEL_H__

# include "../../yuni.h"
# include "../../core/dictionary.h"
# include "../../datetime/timestamp.h"
# include "../../core/noncopyable.h"
# include "../../dbi/settings.h"
# include "../../dbi/error.h"



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
		Channel(Yuni::DBI::Settings& settings);
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
		//! The total number of nested transactions
		uint nestedTransactionCount;
		//! Timestamp when the channel was last used
		sint64 lastUsed;
		//! Channel settings
		Yuni::DBI::Settings& settings;
		//! Mutex
		Yuni::Mutex mutex;

	}; // class Channel





} // namespace DBI
} // namespace Private
} // namespace Yuni

# include "channel.hxx"

#endif // __YUNI_PRIVATE_DBI_CHANNEL_H__
