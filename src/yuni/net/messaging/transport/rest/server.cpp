
#include "server.h"
#include "../../../../thread/signal.h"
#include <cassert>
#define _MSC_VER 0 // seems to be required with this version
#include "mongoose.h"
#include "data.inc.hxx"
#include "serverequest.inc.hxx"


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
		// stopping mongoose if not alreayd done
		if (pData->ctx)
			mg_stop(pData->ctx);

		// reset all internal states
		pData->thread = nullptr;
		pData->signal.reset();

		// re-create mongoose options
		pData->prepareOptionsForMongoose(port, 4);

		// starting mongoose
		pData->ctx = mg_start(& TransportRESTCallback, pData, pData->options);
		if (not pData->ctx)
			return errStartFailed;

		return errNone;
	}


	void Server::wait()
	{
		if (pData)
		{
			// wait for being stopped
			if (pData->signal.valid())
			{
				pData->signal.wait();
			}
			else
			{
				// the code should never reach this location
				// (unless the signal is invalid)
				pData->waitWithoutSignal();
			}
		}
	}


	Net::Error  Server::run()
	{
		assert(pData && "internal error");

		// Get the attached thread
		pData->thread = pAttachedThread;

		// infinite wait, until we receive a message to stop
		wait();

		// waiting for mongoose to stop
		mg_stop(pData->ctx);

		pData->ctx = nullptr;
		pData->thread = nullptr;
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


	void Server::protocol(const Protocol& protocol)
	{
		DecisionTree* decisionTree = new DecisionTree();
		String url;
		String httpMethod;

		// walking through all schemas
		const Schema::Hash& allSchemas = protocol.allSchemas();
		Schema::Hash::const_iterator end = allSchemas.end();
		for (Schema::Hash::const_iterator i = allSchemas.begin(); i != end; ++i)
		{
			// relative path access
			const String& schemaName = i->first;
			// alias to the current schema
			const Schema& schema = i->second;

			API::Method::Hash::const_iterator jend = schema.methods.all().end();
			for (API::Method::Hash::const_iterator j = schema.methods.all().begin(); j != jend; ++j)
			{
				const API::Method& method = j->second;

				// The method will be ignored is no callback has been provided
				if (not method.invoke())
					continue;

				httpMethod = method.option("http.method");
				// using const char* to avoid assert from Yuni::String
				RequestMethod rqmd = StringToRequestMethod(httpMethod.c_str());
				if (rqmd == rqmdInvalid)
					rqmd = rqmdGET;

				// the full url
				url.clear() << schemaName << method.name();

				// keeping the url somewhere
				// IMPORTANT: read notes about how urls are stored
				std::set<String>& mapset = decisionTree->mapset[rqmd];
				mapset.insert(url);
				// retrieving the real pointer to the string
				std::set<String>::const_iterator mapi = mapset.find(url);
				AnyString urlstr = *mapi;

				// alias to the corresponding method handler
				DecisionTree::MethodHandler& mhandler = decisionTree->requestMethods[rqmd][urlstr];

				mhandler.schema = schemaName;
				mhandler.name = method.name();
				mhandler.httpMethod = httpMethod;
				mhandler.invoke = method.invoke();

				// copying parameters
				const API::Method::Parameter::Hash& parameters = method.params();
				if (not parameters.empty())
				{
					API::Method::Parameter::Hash::const_iterator pend = parameters.end();
					API::Method::Parameter::Hash::const_iterator pi = parameters.begin();
					for (; pi != pend; ++pi)
					{
						const API::Method::Parameter& param = pi->second;
						mhandler.parameters[param.name] = param.defvalue;
					}
				}
				else
					mhandler.parameters.clear();
			}
		}

		// Switching to the new protocol
		pData->decisionTree = decisionTree;
	}





} // namespace REST
} // namespace Transport
} // namespace Messaging
} // namespace Net
} // namespace Yuni


