

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



	static void* TransportRESTCallback(enum mg_event event, struct mg_connection *conn)
	{
		// Serving a new request
		if (event == MG_NEW_REQUEST)
		{
			// Retrieving information associated to the current connection
			// The method from mongoose directly return a pointer from within
			// the mg_connection struct, thus it can not fail.
			const mg_request_info& reqinfo = *mg_get_request_info(conn);
			assert(reqinfo.user_data != NULL && "invalid user data");

			// retrieving the request method first
			// and directly aborting if invalid
			RequestMethod rqmd = StringToRequestMethod(reqinfo.request_method);
			if (rqmd == rqmdInvalid)
			{
				std::cerr << "invalid method request (GET, POST, DELETE, PUT), got : " << reqinfo.request_method << std::endl;
				return nullptr;
			}

			// Decision Tree
			// For thread safety reasons, we must keep a smart pointer of the decision tree
			// until the request is served.
			DecisionTree::Ptr dectreeptr = ((Server::ServerData*) reqinfo.user_data)->decisionTree;
			assert(!(!dectreeptr));
			const DecisionTree::UrlDictionary& urls = dectreeptr->requestMethods[rqmd];

			// Message provided to the user
			Net::Messaging::Message message;

			// invoking the user's callback according the decision tree
			DecisionTree::UrlDictionary::const_iterator mi = urls.find(reqinfo.uri);
			if (mi != urls.end())
			{
				// alias to the struct information related to the current method invoked
				const DecisionTree::MethodHandler& mhandler = mi->second;
				message.method = mhandler.name;
				message.schema = mhandler.schema;
				message.httpMethod = mhandler.httpMethod;
				// Invoke user callback
				mhandler.callback(message);
			}
			else
			{
				// the url has not been found
				message.httpError = 404;
				std::cerr << "method not found: " << reqinfo.uri << std::endl;
			}

			switch (message.httpError)
			{
				case 200:
					{
						String header;
						header = "HTTP/1.1 200 OK\r\nCache: no-cache\r\nContent-Length: ";
						header += message.body.size();
						header += "\r\n\r\n";
						mg_write(conn, header.c_str(), header.size());
						mg_write(conn, message.body.c_str(), message.body.size());
						return (void*)"ok"; // the request has been managed
					}
				case 404:
					{
						static const char* const message = "HTTP/1.1 404 Error\r\n\r\nNot found";
						mg_write(conn, message, 31);
						return (void*)"ok"; // the request has been managed
					}
			}
		}

		// the request has not been handled
		return nullptr;
	}





} // namespace REST
} // namespace Transport
} // namespace Messaging
} // namespace Net
} // namespace Yuni

