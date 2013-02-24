
#include "connector-pool.h"
#include "../private/dbi/connector-data.h"



namespace Yuni
{
namespace DBI
{

	ConnectorPool::ConnectorPool(const Yuni::Private::DBI::ConnectorDataPtr& data) :
		pData(data)
	{
	}


	Error ConnectorPool::open(const Settings& settings)
	{
		return errNone;
	}


	void ConnectorPool::close()
	{
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


