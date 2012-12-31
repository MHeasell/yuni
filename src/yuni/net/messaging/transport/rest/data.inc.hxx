

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





} // namespace REST
} // namespace Transport
} // namespace Messaging
} // namespace Net
} // namespace Yuni

