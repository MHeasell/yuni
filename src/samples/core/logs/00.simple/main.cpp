
#include <yuni/core/logs.h>

int main(void)
{
	// A simple logger, which display only on std::cout
	Yuni::Logs::Logger<>  logs;

	// Hello, world !
	logs.checkpoint() << "Hello, " << "world !";
	logs.notice() << "Hello, " << "world !";
	logs.warning() << "Hello, " << "world !";
	logs.error() << "Hello, " << "world !";
	logs.debug() << "Hello, " << "world !";
	logs.fatal() << "Hello, " << "world !";
	return 0;
}
