
#include <yuni/yuni.h>
#include "logs.h"
#include "make.h"
#include "job.h"
#include "job-writer.h"
#include "indexes.h"
#include "tinyxml/tinyxml.h"


using namespace Yuni;



int main(int argc, char** argv)
{
	logs.applicationName("yunidoc-make");
	Make make;
	if (!make.parseCommandLine(argc, argv))
		return EXIT_FAILURE;

	logs.checkpoint() << "Yuni Documentation Builder";
	if (!DocIndex::Open(make.htdocs))
		return EXIT_FAILURE;

	// The condensed mode of tinyxml may removed all linefeed
	TiXmlBase::SetCondenseWhiteSpace(false);

	// Remove all entries within the database which are no longer
	// available
	DocIndex::RemoveNonExistingEntries(make.input);

	// Find all articles
	make.findAllSourceFiles();

	// Extract information from all those articles
	logs.info() << "building search engine data...";
	queueService.start();
	logs.debug() << "waiting...";
	queueService.wait();
	logs.debug() << "stopping...";
	queueService.stop();

	logs.info();
	logs.info() << "writing into htdocs...";
	JobWriter::PushAllInQueue();
	if (JobWriter::ReadTemplateIndex())
	{
		queueService.start();
		logs.debug() << "waiting...";
		queueService.wait();
		logs.debug() << "stopping...";
		queueService.stop();
	}

	DocIndex::Vacuum();
	DocIndex::Close();
	logs.info();
	logs.info() << "Done.";
	return 0;
}

