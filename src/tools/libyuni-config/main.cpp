
#define YUNI_NO_THREAD_SAFE // disabling thread-safety
#include "program.h"


int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		Yuni::LibConfigProgram libconfig;
		return libconfig.execute(argc, argv);
	}
	return 0;
}
