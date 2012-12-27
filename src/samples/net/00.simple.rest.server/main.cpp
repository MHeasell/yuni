
#include <yuni/yuni.h>
#include <yuni/net/messaging/service.h>
#include <yuni/net/messaging/transport/rest/server.h>
#include <yuni/core/logs.h>

using namespace Yuni;

//! Logging facility
Logs::Logger<> logs;



static void HelloWorld(KeyValueStore& params)
{
	logs.info() << "callback: hello world !";
}



static void PrepareTheAPI(Net::Messaging::Service& service)
{
	logs.debug() << "preparing protocol";
	// note: contrary to the object `service`, `myapi` is not thread-safe
	Net::Messaging::Protocol* myapi = new Net::Messaging::Protocol();
	// retrieving the default schema
	Net::Messaging::Schema& schema = myapi->schema();

	// method: hello_world
	schema.methods.add("hello_world")
		.brief("Always answer 'hello world to any request'")
		.option("http.method", "GET")
		.callback.bind(& HelloWorld);

	// Switching to the new protocol
	//
	// note: The method `protocol()` must be call to make any modification to
	//   the protocol visible, and can be called anytime, even if started
	//   (useful for reloading the service while running)
	// note: this method will take ownership of the pointer, thus you no
	//   longer be used
	service.protocol(myapi);
}


static void PrepareTransports(Net::Messaging::Service& service)
{
	logs.debug() << "preparing transports";
	service.transports.add("*", 54042, new Net::Messaging::Transport::REST::Server());
}


static bool StartService(Net::Messaging::Service& service)
{
	logs.info() << "starting";

	Net::Error error = service.start();

	switch (error)
	{
		case Net::errNone:
			break;
		default:
			logs.fatal() << "impossible to start the service: " << error;
			return false;
	}

	logs.info() << "help: wget 'http://localhost:54042/hello_world'";
	logs.info(); // empty line for beauty
	return true;
}





int main(int, char**)
{
	// Welcome !
	logs.notice() << "Yuni REST Server Example";
	logs.info() << "http://www.libyuni.org";
	logs.info(); // empty line

	// The service itself
	Net::Messaging::Service  service;

	// Prepare the API
	PrepareTheAPI(service);

	// Preparing all transports
	PrepareTransports(service);

	// Starting the new service
	if (not StartService(service))
		return EXIT_FAILURE;

	// Waiting for the end of the server
	service.wait();
	return 0;
}

