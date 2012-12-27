
#include "server.h"
#include "../../../../thread/signal.h"
#include <cassert>

#define _MSC_VER 0 // seems to be required with this version
#include "mongoose.h"


namespace Yuni
{
namespace Net
{
namespace Messaging
{
namespace Transport
{
namespace REST
{

	class Server::ServerData
	{
	public:
		ServerData() :
			thread(nullptr)
		{
		}

		void waitWithoutSignal();

	public:
		//! Signal for stopping the web server
		Thread::Signal signal;
		//! Attached thread
		Thread::IThread* thread;
	};


	void Server::ServerData::waitWithoutSignal()
	{
		std::cerr << "invalid signal. using active loop\n";
		// signal missing
		while (not thread->suspend(1200)) // milliseconds
		{
			// infinite
		}
	}





	Server::Server() :
		ITransport(tmServer)
	{
		pData = new ServerData();
	}


	Server::~Server()
	{
		delete pData;
	}


	Net::Error  Server::start()
	{
		pData->thread = nullptr;
		pData->signal.reset();
		return errNone;
	}


	Net::Error  Server::run()
	{
		assert(pData && "internal error");
		ServerData& data = *pData;

		// Get the attached thread
		data.thread = pAttachedThread;

		if (data.signal.valid())
		{
			// wait for being stopped
			data.signal.wait();
		}
		else
		{
			// should never happen
			data.waitWithoutSignal();
		}

		data.thread = nullptr;
		return errNone;
	}


	void Server::stop()
	{
		assert(pData && "internal error");
		// notifying that we should stop as soon as possible
		if (pData->signal.valid())
		{
			pData->signal.notify();
		}
		else
		{
			if (pData->thread)
				pData->thread->gracefulStop();
		}
	}





} // namespace REST
} // namespace Transport
} // namespace Messaging
} // namespace Net
} // namespace Yuni


