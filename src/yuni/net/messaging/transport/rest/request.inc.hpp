
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

	enum RequestMethod
	{
		rqmdGET = 0,
		rqmdPOST,
		rqmdPUT,
		rqmdDELETE,
		rqmdInvalid,
		rqmdMax
	};

	template<class StringT>
	static RequestMethod StringToRequestMethod(const StringT& text);


	class DecisionTree final
	{
	public:
		//! The most suitable smart ptr for the class
		typedef SmartPtr<DecisionTree> Ptr;

		class MethodHandler final
		{
		public:
			//! Name of the method invoked
			String name;
			//! Full schema name
			String schema;
			//! Method request (GET, POST, DELETE, PUT)
			String httpMethod;
			//! All parameters, with they default value
			KeyValueStore parameters;
			//!
			API::Method::Callback invoke;

		}; // class DecisionTree

		//! Dictionary for all managed urls
		typedef Dictionary<AnyString, MethodHandler>::Hash  UrlDictionary;


	public:
		//! Dictionary for all managed urls
		UrlDictionary requestMethods[rqmdMax];
		//! Container only used for storing string urls
		std::set<String> mapset[rqmdMax];

	}; // class DecisionTree



	class Server::ServerData
	{
	public:
		ServerData();
		~ServerData();

		void waitWithoutSignal();

		void prepareOptionsForMongoose(uint port, uint threads);

	public:
		//! The decision tree
		DecisionTree::Ptr decisionTree;

		//! Signal for stopping the web server
		Thread::Signal signal;
		//! Attached thread
		Thread::IThread* thread;
		//! Mongoose options, C-Style, see optionsString
		const char** options;
		//! The number of options
		uint optionCount;
		//! Mongoose context
		struct mg_context *ctx;

		//! Options for mongoose
		String::Vector optionsString;

	}; // class ServerData







	inline Server::ServerData::ServerData() :
		thread(nullptr),
		options(nullptr),
		optionCount(),
		ctx(nullptr)
	{
	}


	inline Server::ServerData::~ServerData()
	{
		if (ctx)
			mg_stop(ctx);
		delete[] options;
	}


	inline void Server::ServerData::waitWithoutSignal()
	{
		std::cerr << "invalid signal. using active loop\n";
		// signal missing
		while (not thread->suspend(1200)) // milliseconds
		{
			// infinite
		}
	}


	inline void Server::ServerData::prepareOptionsForMongoose(uint port, uint threads)
	{
		typedef const char* CStr;
		uint count = 4;

		optionsString.resize(count);
		optionsString[0] = "listening_ports";
		optionsString[1] = port;
		optionsString[2] = "num_threads";
		optionsString[3] = threads;

		optionCount = count;
		delete[] options;
		options = new CStr[count + 1];
		for (uint i = 0; i != count; ++i)
			options[i] = optionsString[i].c_str();
		options[count] = nullptr;
	}


	template<class StringT>
	static inline RequestMethod StringToRequestMethod(const StringT& text)
	{
		switch (text[0])
		{
			case 'G':
				{
					if (text[1] == 'E' and text[2] == 'T' and text[3] == '\0')
						return rqmdGET;
					break;
				}
			case 'P':
				{
					if (text[1] == 'O' and text[2] == 'S' and text[3] == 'T' and text[4] == '\0')
						return rqmdPOST;
					if (text[1] == 'U' and text[2] == 'T' and text[3] == '\0')
						return rqmdPUT;
					break;
				}
			case 'D':
				{
					if (text[1] == 'E' and text[2] == 'L' and text[3] == 'E' and text[4] == 'T'
						and text[5] == 'E' and text[6] == '\0')
							return rqmdDELETE;
					break;
				}
		}
		return rqmdInvalid;
	}




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

