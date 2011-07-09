
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
	queueService.start();
	make.findAllSourceFiles();
	queueService.wait(60 * 60);
	queueService.stop();
	return 0;
}

