
#include <yuni/yuni.h>
#include "logs.h"
#include "make.h"
#include "job.h"


using namespace Yuni;



int main(int argc, char** argv)
{
	logs.applicationName("yunidoc-make");
	Make make;
	if (!make.parseCommandLine(argc, argv))
		return EXIT_FAILURE;

	logs.checkpoint() << "Yuni Documentation Builder";
	queueService.start();
	make.findAllSourceFiles();
	queueService.wait(60 * 60);
	queueService.stop();

	logs.info();
	logs.info() << "Done.";
	return 0;
}

