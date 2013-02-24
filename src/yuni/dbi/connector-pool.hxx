#ifndef __YUNI_DBI_CONNECTOR_HXX__
# define __YUNI_DBI_CONNECTOR_HXX__



namespace Yuni
{
namespace DBI
{

	inline ConnectorPool::ConnectorPool()
	{
		// does nothing
	}


	inline ConnectorPool::~ConnectorPool()
	{
		// does nothing
	}



	inline Transaction  ConnectorPool::begin()
	{
		return  Transaction(pData);
	}




} // namespace DBI
} // namespace Yuni

#endif // __YUNI_DBI_CONNECTOR_HXX__