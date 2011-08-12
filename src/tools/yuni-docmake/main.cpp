
#include <yuni/yuni.h>
#include "logs.h"
#include "program.h"
#include "job.h"
#include "job-writer.h"
#include "indexes.h"
#include "tinyxml/tinyxml.h"
#include <yuni/core/system/suspend.h>




int main(int argc, char** argv)
{
	using namespace Yuni::Tool::DocMake;

	logs.applicationName("yuni-docmake");
	Program program;
	if (!program.parseCommandLine(argc, argv))
		return EXIT_FAILURE;

	logs.checkpoint() << "Yuni Documentation Builder";
	if (!DocIndex::Open(program.htdocs))
		return EXIT_FAILURE;

	// The condensed mode of tinyxml may removed all linefeed
	TiXmlBase::SetCondenseWhiteSpace(false);

	// Remove all entries within the database which are no longer
	// available
	DocIndex::RemoveNonExistingEntries();

	// Find all articles
	program.findAllSourceFiles();

	// Extract information from all those articles
	logs.info() << "Extracting SEO data";
	{
		queueService.start();
		while (CompileJob::SomeRemain())
			Yuni::SuspendMilliSeconds(150);
		queueService.wait();
		queueService.stop();
	}

	logs.info() << "Optimizing SEO data";
	DocIndex::UpdateAllSEOWeights();
	JobWriter::SEOBuildAllTermReferences();
	DocIndex::BuildSEOArticlesReference();

	logs.info() << "Generating HTML files into htdocs";
	if (JobWriter::ReadTemplateIndex())
	{
		JobWriter::PushAllInQueue();
		queueService.start();
		while (JobWriter::SomeRemain())
			Yuni::SuspendMilliSeconds(150);

		queueService.wait();
		queueService.stop();

		logs.info() << "Generating sitemap";
		DocIndex::BuildSitemap();
	}

	DocIndex::Vacuum();
	DocIndex::Close();
	logs.info();
	logs.info() << "Done.";
	return 0;
}

