#ifndef __YUNI_DBI_FWD_H__
# define __YUNI_DBI_FWD_H__

# include "../core/smartptr/smartptr.h"


namespace Yuni
{
namespace DBI
{

	// Forward declarations
	class Connector;
	class Transaction;
	class Query;


} // namespace DBI
} // namespace Yuni



namespace Yuni
{
namespace Private
{
namespace DBI
{

	// Forward declarations
	class Channel;
	class ConnectorData;

	//! Connector data ptr
	typedef Yuni::SmartPtr<ConnectorData>  ConnectorDataPtr;
	typedef Yuni::SmartPtr<Channel>  ChannelPtr;


} // namespace DBI
} // namespace Private
} // namespace Yuni


#endif // __YUNI_DBI_FWD_H__
