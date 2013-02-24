
#include "channel.h"


namespace Yuni
{
namespace Private
{
namespace DBI
{


	Channel::Channel(Yuni::DBI::Settings& settings) :
		nestedTransactionCount(0),
		lastUsed(Yuni::DateTime::Now()),
		settings(settings),
		mutex(true) // recursive
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

