
#include <yuni/core/logs.h>

int main(void)
{
	Yuni::Logs::Logger<>  logs;

	//for (int i = 0; i < 800000; ++i)
	//	logs.notice() << " Value : " << i;

	logs.checkpoint() << "Yuni, a complete framework for your kill app";
	logs.checkpoint() << "Version " << YUNI_VERSION_HI << "." << YUNI_VERSION_LO;
	logs.checkpoint() << "-";
	logs.notice() << "Loading data";
	logs.notice() << "Sample !";
	logs.checkpoint() << "You have just passed a checkpoint";
	logs.warning() << "Sample !";
	logs.error("[my section] ") << "Sample !";
	logs.fatal() << "Sample !";
	logs.debug() << "Sample !";
	return 0;
}
