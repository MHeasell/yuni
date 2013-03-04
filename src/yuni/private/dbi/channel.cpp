
#include "channel.h"


namespace Yuni
{
namespace Private
{
namespace DBI
{


	Channel::Channel(const Yuni::DBI::Settings& settings, const ::yn_dbi_adapter& adapter) :
		mutex(true), // recursive
		adapter(adapter),
		nestedTransactionCount(0),
		settings(settings),
		lastUsed(Yuni::DateTime::Now())
	{
	}


	Channel::~Channel()
	{
		if (nestedTransactionCount > 0)
		{
			std::cerr << "closing database channel but " << nestedTransactionCount
				<< "transaction(s) remain" << std::endl;
			assert(false and "closing database channel but some transactions remain");
		}
	}






} // namespace DBI
} // namespace Private
} // namespace Yuni

