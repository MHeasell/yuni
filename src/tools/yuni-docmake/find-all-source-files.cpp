
#include "make.h"
#include <yuni/core/io/directory/info.h>
#include "job.h"
#include "logs.h"


using namespace Yuni;


# define SEP Core::IO::Separator


void Make::findAllSourceFiles()
{
	logs.notice() << "Looking for articles...";

	std::vector<CompileJob*> jobs;
	jobs.resize(nbJobs);
	for (unsigned int i = 0; i != jobs.size(); ++i)
		jobs[i] = new CompileJob(input, htdocs);

	Core::IO::Directory::Info info(input);
	String tmp;
	unsigned int slotIndex = 0;
	unsigned int count = 0;
	for (Core::IO::Directory::Info::recursive_iterator i = info.recursive_begin(); i != info.recursive_end(); ++i)
	{
		// assert
		assert(!(!(*i)));
		// alias
		const String& name = *i;
		const String& filename = i.filename();

		if (i.isFolder())
		{
			if (filename.contains(".svn"))
				continue;
			tmp.clear() << filename << SEP << "article.xml";
			if (!Core::IO::File::Exists(tmp))
			{
				logs.warning() << "missing article.xml in " << filename;
			}
			continue;
		}
		if (!i.isFile() || name != "article.xml")
			continue;
		assert(filename.size() > input.size());
		assert(slotIndex < jobs.size());

		jobs[slotIndex]->add(filename);
		if (++slotIndex >= jobs.size())
			slotIndex = 0;
		++count;
	}

	if (count)
	{
		logs.info() << count << (count > 1 ? " articles to build, " : "article to build, ") << nbJobs
			<< (nbJobs > 1 ? " threads" : " thread");
		logs.info();
		for (unsigned int i = 0; i != jobs.size(); ++i)
			queueService += jobs[i];
	}
	else
	{
		for (unsigned int i = 0; i != jobs.size(); ++i)
			delete jobs[i];
	}
}

