
#include <yuni/core/logs.h>

int main(void)
{
	Yuni::Logs::Logger<>  logs;

	//for (int i = 0; i < 800000; ++i)
	//	logs.notice() << " Value : " << i;

	logs.checkpoint() << "TA3D, a remake of Total Annhilation";
	logs.checkpoint() << "Version 0.6-WIP";
	logs.checkpoint() << "-";
	logs.notice() << "Loading data";
	logs.checkpoint() << "Welcome and Good luck Commander !";
	logs.notice() << "Sample !";
	logs.warning() << "Sample !";
	logs.error("[3do] ") << "Sample !";
	logs.fatal() << "Sample !";
	logs.debug() << "Sample !";
	return 0;
}
