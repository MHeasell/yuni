
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

	logs.applicationName("edln-make");
	Program program;
	if (!program.parseCommandLine(argc, argv))
		return EXIT_FAILURE;

	logs.checkpoint() << "Edalene Make";
	if (!DocIndex::Open(program.htdocs))
		return EXIT_FAILURE;

	// The condensed mode of tinyxml may removed all linefeed
	TiXmlBase::SetCondenseWhiteSpace(false);

	// Preload all terms from the index db
	Dictionary::PreloadFromIndexDB();

	// Remove all entries within the database which are no longer
	// available
	DocIndex::RemoveNonExistingEntries();

	// Find all articles
	program.findAllSourceFiles();

	// Extract information from all those articles
	logs.info() << "reading articles...";
	{
		queueService.start();
		queueService.wait();
		queueService.stop();
	}

	logs.info() << "building SEO data";
	DocIndex::UpdateAllSEOWeights();
	JobWriter::SEOBuildAllTermReferences();
	DocIndex::BuildSEOArticlesReference();

	logs.info() << "generating HTML files into htdocs";
	if (JobWriter::ReadTemplateIndex())
	{
		JobWriter::PushAllInQueue();
		queueService.start();
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

