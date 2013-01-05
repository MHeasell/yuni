
#include "return-status-code.inc.hpp"
#include "../../../../core/system/cpu.h"
#include "../../../../thread/id.h"


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
		/*!
		** \brief Default constructor
		*/
		ServerData();
		//! Destructor
		~ServerData();

		/*!
		** \brief Prepare a C-style array for mongoose options
		*/
		void prepareOptionsForMongoose(uint port, uint threads);

		//! Fallback implementation when the signal could not be initialized
		void waitWithoutSignal();

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
		// note: we assume that `text` is zero-terminated
		switch (text[0])
		{
			case 'G':
				{
					// GET
					if (text[1] == 'E' and text[2] == 'T' and text[3] == '\0')
						return rqmdGET;
					break;
				}
			case 'P':
				{
					// POST
					if (text[1] == 'O' and text[2] == 'S' and text[3] == 'T' and text[4] == '\0')
						return rqmdPOST;
					// PUT
					if (text[1] == 'U' and text[2] == 'T' and text[3] == '\0')
						return rqmdPUT;
					break;
				}
			case 'D':
				{
					// DELETE
					if (text[1] == 'E' and text[2] == 'L' and text[3] == 'E' and text[4] == 'T'
						and text[5] == 'E' and text[6] == '\0')
							return rqmdDELETE;
					break;
				}
		}
		return rqmdInvalid;
	}





	static bool DecodeURLQuery(KeyValueStore& params, const AnyString& query)
	{
		// note: mongoose does not provide the fragment here, so we don't have
		// to check it

		// Some tests are already done before calling this method
		assert(not query.empty());

		String key; // temporary string for parameters handling
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




	static void* TransportRESTCallback(enum mg_event event, struct mg_connection* conn)
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
				return HTTPErrorCode<404>(conn);

			// server data
			Server::ServerData* serverdata = (Server::ServerData*) reqinfo.user_data;

			// Decision Tree
			// For thread safety reasons, we must keep a smart pointer of the decision tree
			// until the request is served.
			DecisionTree::Ptr dectreeptr = serverdata->decisionTree;
			assert(!(!dectreeptr));
			const DecisionTree::UrlDictionary& urls = dectreeptr->requestMethods[rqmd];

			// invoking the user's callback according the decision tree
			DecisionTree::UrlDictionary::const_iterator mi = urls.find(reqinfo.uri);
			if (mi == urls.end())
			{
				// the url has not been found
				return HTTPErrorCode<404>(conn);
			}
			// alias to the method handler
			const DecisionTree::MethodHandler& mhandler = mi->second;


			// Message context
			Net::Messaging::Context context;

			// reading / checking for parameters
			if (not mhandler.parameters.empty())
			{
				// copying all default parameters
				context.params = mhandler.parameters;

				// reading parameters from the url query
				// ignoring unknown parameters
				if (reqinfo.query_string and reqinfo.query_string[0] != '\0')
				{
					if (not DecodeURLQuery(context.params, reqinfo.query_string))
						return HTTPErrorCode<400>(conn);
				}
			}

			// resetting context
			context.method = mhandler.name;
			context.schema = mhandler.schema;
			context.httpStatus = 200;
			context.remotePort = reqinfo.remote_port;
			// response
			Marshal::Object response;

			// Invoke user callback
			mhandler.invoke(context, response);


			// sending the response
			if  (200 == context.httpStatus)
			{
				Clob& body = context.clob;
				# ifndef NDEBUG
				response.toJSON(body, true);
				# else
				response.toJSON(body, false); // reduce size output
				# endif

				Clob& out  = context.buffer;
				out.clear();
				out += "HTTP/1.1 200 OK\r\nCache: no-cache\r\nContent-Type: application/json\r\nContent-Length: ";
				out += body.size();
				out += "\r\n\r\n";
				out += body;
				mg_write(conn, out.c_str(), out.size());

				// reducing memory usage for some Memory-hungry apps
				context.autoshrink();
				return (void*)"ok"; // the request has been handled
			}
			else
			{
				// reducing memory usage for some Memory-hungry apps
				context.autoshrink();

				switch (context.httpStatus)
				{
					case 404: // not found
						return HTTPErrorCode<404>(conn);
					case 400: // Bad request
						return HTTPErrorCode<400>(conn);
					case 403: // Forbidden
						return HTTPErrorCode<403>(conn);
					case 401: // Unauthorized
						return HTTPErrorCode<401>(conn);
				}
			}

			// not handled by default
			return HTTPErrorCode<500>(conn);
		}

		return nullptr;
	}





} // namespace REST
} // namespace Transport
} // namespace Messaging
} // namespace Net
} // namespace Yuni

