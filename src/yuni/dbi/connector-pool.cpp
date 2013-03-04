
#include "connector-pool.h"
#include "../private/dbi/connector-data.h"



namespace Yuni
{
namespace DBI
{

	ConnectorPool::ConnectorPool()
	{
		// does nothing
	}


	ConnectorPool::ConnectorPool(const Yuni::Private::DBI::ConnectorDataPtr& data) :
		pData(data)
	{
	}


	ConnectorPool::~ConnectorPool()
	{
		// does nothing
	}


	Error ConnectorPool::open(const Settings& settings)
	{
		return errNone;
	}


	void ConnectorPool::close()
	{
		// release pdata
		pData = nullptr;
	}


	bool ConnectorPool::retrieveSettings(Settings& out) const
	{
		Yuni::Private::DBI::ConnectorDataPtr data = pData;
		if (!(!data))
		{
			out = data->settings;
			return true;
		}
		else
		{
			out.clear();
			return false;
		}
	}





} // namespace DBI
} // namespace Yuni


