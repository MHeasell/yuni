
#include "worker.h"


namespace Yuni
{
namespace Private
{
namespace Net
{
namespace Message
{


	Worker::Worker(ITransport::Ptr transport)
	{
		pTransport = transport;
	}


	Worker::~Worker()
	{
	}


	bool Worker::onExecute()
	{
		return true;
	}





} // namespace Message
} // namespace Net
} // namespace Private
} // namespace Yuni

