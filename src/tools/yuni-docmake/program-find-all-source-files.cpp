
#include "program.h"
#include <yuni/core/io/directory/info.h>
#include "job.h"
#include "logs.h"




# define SEP Core::IO::Separator



namespace Yuni
{
namespace Tool
{
namespace DocMake
{


	void Program::findAllSourceFiles()
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
			// aliases
			const String& name = *i;
			const String& filename = i.filename();

			// The current element is either a folder, either a file
			if (i.isFolder())
			{
				// Detecting pseudo folders from source controls tools, such as
				// subversion or git
				if (filename.contains(".svn") || filename.contains(".git"))
					continue;

				// Ok, the folder interrests us
				// checking if th default article file is present
				tmp.clear() << filename << SEP << "article.xml";
				if (!Core::IO::File::Exists(tmp))
					logs.warning() << "missing article.xml in " << filename;
			}
			else
			{
				// This should be a file
				// In this phase, the only files which interrest us are all
				// named 'article.xml'
				if (!i.isFile() || name != "article.xml")
					continue;
				// A few asserts...
				assert(filename.size() > input.size());
				assert(slotIndex < jobs.size());

				// Creating a new job for generating this article
				jobs[slotIndex]->add(filename);
				if (++slotIndex >= jobs.size())
					slotIndex = 0;
				++count;
			}
		} // for, all files and folders, recursively


		// Statistics about the articles to generate
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
			// Actually there is nothing to do (??). Destroying all
			// useless jobs
			for (unsigned int i = 0; i != jobs.size(); ++i)
				delete jobs[i];
		}
	}





} // namespace DocMake
} // namespace Tool
} // namespace Yuni


