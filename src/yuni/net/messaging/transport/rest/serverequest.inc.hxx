

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

	template<uint MaxSize, class StringT>
	static inline void AutoShrink(StringT& variable)
	{
		if (variable.capacity() > MaxSize)
		{
			variable.clear();
			variable.shrink();
		}
	}


	static bool DecodeURLQuery(KeyValueStore& params, const AnyString& query, String& key)
	{
		// note: mongoose does not provide the fragment here, so we don't have
		// to check it

		// Some tests are already done before calling this method
		assert(not query.empty());

		uint offset = 0;
		uint start = 0;
		AnyString value;
		do
		{
			offset = query.find_first_of("=&", offset);
			if (offset >= query.size())
			{
				// ignoring fields with empty value (using default)
				break;
			}
			if (query[offset] == '=')
			{
				key.assign(query, offset - start, start);
				if (key.empty()) // malformed url. aborting
					return false;

				++offset;

				// FIXME !!!! &amp; are not properly handled !!!!!!!!!!!!
				uint ampersand = offset;
				ampersand = query.find('&', ampersand);
				if (ampersand >= query.size())
				{
					value.adapt(query, query.size() - offset, offset);
					ampersand = query.size();
				}
				else
					value.adapt(query, ampersand - offset, offset);

				if (not value.empty())
				{
					KeyValueStore::iterator i = params.find(key);
					if (i != params.end())
					{
						// the item has been found !
						params[key] = value;
					}
				}

				offset = ampersand;
			}
			else
			{
				// ignoring fields with empty value (using default)
			}

			// updating offsets
			start = ++offset;
		}
		while (true);
		return true;
	}




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
			// Thread Context
			Net::Messaging::ThreadContext threadcontext;

			// invoking the user's callback according the decision tree
			DecisionTree::UrlDictionary::const_iterator mi = urls.find(reqinfo.uri);
			if (mi != urls.end())
			{
				// alias to the method handler
				const DecisionTree::MethodHandler& mhandler = mi->second;

				// checking for parameters
				if (not mhandler.parameters.empty())
				{
					// copying all default parameters
					message.params = mhandler.parameters;

					// reading parameters from the url query
					if (reqinfo.query_string and reqinfo.query_string[0] != '\0')
					{
						String& tmp = threadcontext.text;
						if (not DecodeURLQuery(message.params, reqinfo.query_string, tmp))
							message.httpStatus = 400;
					}
				}
				else
					message.params.clear();

				if (message.httpStatus == 200) // still ok ?
				{
					message.method = mhandler.name;
					message.schema = mhandler.schema;
					message.httpMethod = mhandler.httpMethod;

					// reset thread context local variables
					threadcontext.clear();

					// Invoke user callback
					mhandler.invoke(threadcontext, message);

					// reduce memory usage
					AutoShrink<6 * 1024>(threadcontext.text);
					AutoShrink<5 * 1024 * 1024>(threadcontext.clob);
				}
			}
			else
			{
				// the url has not been found
				message.httpStatus = 404;
				std::cerr << "method not found: " << reqinfo.uri << std::endl;
			}

			switch (message.httpStatus)
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
				case 400:
					{
						static const char* const message = "HTTP/1.1 400 Error\r\n\r\nBad request";
						mg_write(conn, message, 33);
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

